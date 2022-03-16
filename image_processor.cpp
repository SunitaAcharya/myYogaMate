
/*** Include ***/
/* for general */
#include <cstdint>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <memory>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <signal.h>
#include <string.h>

/* for OpenCV */
#include <opencv2/opencv.hpp>

/* for My modules */
#include "common_helper.h"
#include "common_helper_cv.h"
#include "pose_engine.h"
#include "image_processor.h"

/*** Macro ***/
#define TAG "ImageProcessor"
#define PRINT(...)   COMMON_HELPER_PRINT(TAG, __VA_ARGS__)
#define PRINT_E(...) COMMON_HELPER_PRINT_E(TAG, __VA_ARGS__)

/*** Global variable ***/
std::unique_ptr<PoseEngine> s_engine;
int BOOL[8]={0,0,0,0,0,0,0,0};
double angle0[8]={0,0,0,0,0,0,0,0};//Angle of cam
/*** Function ***/
static void DrawFps(cv::Mat& mat, double time_inference, cv::Point pos, double font_scale, int32_t thickness, cv::Scalar color_front, cv::Scalar color_back, bool is_text_on_rect = true)
{
    char text[64];
    static auto time_previous = std::chrono::steady_clock::now();
    auto time_now = std::chrono::steady_clock::now();
    double fps = 1e9 / (time_now - time_previous).count();
    time_previous = time_now;
    snprintf(text, sizeof(text), "FPS: %.1f, Inference: %.1f [ms]", fps, time_inference);
    CommonHelper::DrawText(mat, text, cv::Point(0, 0), 0.5, 2, CommonHelper::CreateCvColor(0, 0, 0), CommonHelper::CreateCvColor(180, 180, 180), true);
}


int32_t ImageProcessor::Initialize(const ImageProcessor::InputParam& input_param)
{
    if (s_engine) 
    {
        PRINT_E("Already initialized\n");
        return -1;
    }

    s_engine.reset(new PoseEngine());
    if (s_engine->Initialize(input_param.work_dir, input_param.num_threads) != PoseEngine::kRetOk) 
    {
        s_engine->Finalize();
        s_engine.reset();
        return -1;
    }
    return 0;
}

int32_t ImageProcessor::Finalize(void)
{
    if (!s_engine) 
    {
        PRINT_E("Not initialized\n");
        return -1;
    }

    if (s_engine->Finalize() != PoseEngine::kRetOk) 
    {
        return -1;
    }

    return 0;
}


int32_t ImageProcessor::Command(int32_t cmd)
{
    if (!s_engine) 
    {
        PRINT_E("Not initialized\n");
        return -1;
    }

    switch (cmd) 
    {
    case 0:
    default:
        PRINT_E("command(%d) is not supported\n", cmd);
        return -1;
    }
}

static const std::vector<std::pair<int32_t, int32_t>> kJointLineList {
    /* face */
    {0, 2},
    {2, 4},
    {0, 1},
    {1, 3},
    /* body */
    {6, 5},
    {5, 11},
    {11, 12},
    {12, 6},
    /* arm */
    {6, 8},
    {8, 10},
    {5, 7},
    {7, 9},
    /* leg */
    {12, 14},
    {14, 16},
    {11, 13},
    {13, 15},
};

static constexpr float kThresholdScoreKeyPoint = 0.2f;

int32_t ImageProcessor::Process(cv::Mat& mat, ImageProcessor::Result& result)
{
    if (!s_engine)
    {
        PRINT_E("Not initialized\n");
        return -1;
    }
    double angle[8]; //Angle of user
	double angle0[8];//Angle of cam
    int Learner[12][2]; //joint of uesr
    //int BOOL[8]={0,0,0,0,0,0,0,0}; 
    PoseEngine::Result pose_result;
    if (s_engine->Process(mat, pose_result) != PoseEngine::kRetOk) 
    {
        return -1;
    }

    /* Display target area  */
    cv::rectangle(mat, cv::Rect(pose_result.crop.x, pose_result.crop.y, pose_result.crop.w, pose_result.crop.h), CommonHelper::CreateCvColor(0, 0, 0), 2);

    /* Display detection result and keypoint */
    for (size_t i = 0; i < 1; i++) 
    {

        /* Display joint lines */
        const auto& keypoint = pose_result.keypoint_list[i];
        const auto& keypoint_score = pose_result.keypoint_score_list[i];

        /* Angle calculation */
        for (int k = 0; k < 12; k++)
        {
            Learner[k][0]=keypoint[k+5].first;
            Learner[k][1]=keypoint[k+5].second;
        }
        
        for(int k =0; k<2; k++)
        {
            int a =Learner[k][0];
            Learner[k][0]=Learner[k+4][0];
            Learner[k+4][0]=a;
            a =Learner[k][1];
            Learner[k][1]=Learner[k+4][1];
            Learner[k+4][1]=a;
        }

        for (int k = 0; k < 8; k++)
        {
            double line1=sqrt((Learner[k][0]-Learner[k+2][0])*(Learner[k][0]-Learner[k+2][0])+(Learner[k][1]-Learner[k+2][1])*(Learner[k][1]-Learner[k+2][1]));
            double line2=sqrt((Learner[k+2][0]-Learner[k+4][0])*(Learner[k+2][0]-Learner[k+4][0])+(Learner[k+2][1]-Learner[k+4][1])*(Learner[k+2][1]-Learner[k+4][1]));
            double line3=sqrt((Learner[k][0]-Learner[k+4][0])*(Learner[k][0]-Learner[k+4][0])+(Learner[k][1]-Learner[k+4][1])*(Learner[k][1]-Learner[k+4][1]));
            double angleP=acos((line1*line1+line2*line2-line3*line3)/(2*line1*line2))*180.0/3.14;
            if (Thread_num==1)
            {
                angle[k]=angleP;
                printf("vid ");
                
            }
            else
            {
                angle0[k]=angleP;
                printf("pic ");
                
            }
            
            printf("Angle0 %d", k);
            printf(": %f,\n", angle0[k]);
            printf("Angle %d", k);
            printf(": %f,\n", angle[k]);
            
        }

        for (int n = 0; n < 8; n++)
        {                
            if ((angle[n]<(angle0[n]-5)) || (angle[n]>(angle0[n]+5)))
            {
                BOOL[n]=n+1;
            }   
            printf("BOOL %d, \n", BOOL[n]);
        }
        for (const auto& jointLine : kJointLineList) 
        {
            if (keypoint_score[jointLine.first] >= kThresholdScoreKeyPoint && keypoint_score[jointLine.second] >= kThresholdScoreKeyPoint) {
                int32_t x0 = keypoint[jointLine.first].first;
                int32_t y0 = keypoint[jointLine.first].second;
                int32_t x1 = keypoint[jointLine.second].first;
                int32_t y1 = keypoint[jointLine.second].second;
                cv::line(mat, cv::Point(x0, y0), cv::Point(x1, y1), CommonHelper::CreateCvColor(0, 255, 0), 2);
            }
            
            if (Thread_num==1)
            {
                for (int k = 0; k <8; k++)//mark wrong joint lines
                {
                    if(BOOL[k]!=0)
                    {
                    cv::line(mat, cv::Point(Learner[k+2][0], Learner[k+2][1]), cv::Point(Learner[k][0], Learner[k][1]), CommonHelper::CreateCvColor(0, 0, 255), 2);
                    cv::line(mat, cv::Point(Learner[k+2][0], Learner[k+2][1]), cv::Point(Learner[k+4][0], Learner[k+4][1]), CommonHelper::CreateCvColor(0, 0, 255), 2);
                    }
                }
            }
            
            
        }

        /* Display joints */
        for (size_t j = 0; j < keypoint.size(); j++) {
            if (keypoint_score[j] >= kThresholdScoreKeyPoint) {
                const auto& p = keypoint[j];
                cv::circle(mat, cv::Point(p.first, p.second), 5, CommonHelper::CreateCvColor(0, 255, 0),2);
            }
            if (Thread_num==1)
            {
                for(int k=0; k<8; k++)//mark wrong joints
                {
                    if(BOOL[k] !=0)
                    {
                    cv::circle(mat, cv::Point(Learner[k+2][0], Learner[k+2][1]), 5, CommonHelper::CreateCvColor(0, 0, 255),2);
                    }
                }
            }
            
            
        }
    }


    DrawFps(mat, pose_result.time_inference, cv::Point(0, 0), 0.5, 2, CommonHelper::CreateCvColor(0, 0, 0), CommonHelper::CreateCvColor(180, 180, 180), true);

    result.time_pre_process = pose_result.time_pre_process;
    result.time_inference = pose_result.time_inference;
    result.time_post_process = pose_result.time_post_process;
    
    return 0;
}
