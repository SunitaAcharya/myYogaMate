/*** Include ***/
/* for general */
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <memory>
#include <unistd.h>
#include <iostream>
/* for OpenCV */
#include <opencv2/opencv.hpp>
/* for My modules */
#include "pose_engine.h"
#include "image_processor.h"
#include "image_show.h"

std::unique_ptr<PoseEngine> s_engine;
int ImageProcessor_Process::angle_check[8];

int32_t ImageProcessor_Initialize::Initialize(const ImageProcessor_Initialize::InputParam& input_param)
{

    s_engine.reset(new PoseEngine());
    if (s_engine->Initialize(input_param.work_dir, input_param.num_threads) != PoseEngine::kRetOk) 
    {
        s_engine->Finalize();
        s_engine.reset();
        return -1;
    }
    return 0;
}

int32_t ImageProcessor_Finalize::Finalize()
{
    if (!s_engine) 
    {
        
        std::cout<<"Not initialized\n"<<std::endl;
        return -1;
    }

    if (s_engine->Finalize() != PoseEngine::kRetOk) 
    {
        return -1;
    }

    return 0;
}


int32_t ImageProcessor_Command::Command(int32_t cmd)
{
    if (!s_engine) 
    {
        std::cout<<"Not initialized\n"<<std::endl;
        return -1;
    }

    switch (cmd) 
    {
    case 0:
    default:
        std::cout<<"command "<<cmd<<" is not supported\n"<<std::endl;
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

int32_t ImageProcessor_Process::Process(cv::Mat& mat)
{
    if (!s_engine)
    {
        std::cout<<"Not initialized\n"<<std::endl;
        return -1;
    }
    
    PoseEngine::Result pose_result;
    if (s_engine->Process(mat, pose_result) != PoseEngine::kRetOk) 
    {
        return -1;
    }

    /* Display target area  */
    cv::rectangle(mat, cv::Rect(pose_result.crop.x, pose_result.crop.y, pose_result.crop.w, pose_result.crop.h), cv::Scalar(0, 0, 0), 2);

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
        
        double* prt=new double[8];

        for(int k =0; k<2; k++)
        {
            *(prt+k)=Learner[k][0];
            *(prt+k+2)=Learner[k+4][0];
            *(prt+k+4)=Learner[k][1];
            *(prt+k+6)=Learner[k+4][1];
        }

        for(int k=0;k<2;k++)
        {
            Learner[k][0]=*(prt+k+2);
            Learner[k+4][0]=*(prt+k);
            Learner[k][1]=*(prt+k+6);
            Learner[k+4][1]=*(prt+k+4);
        }
        

        for (int k = 0; k < 8; k++)
        {
            double line1=sqrt((Learner[k][0]-Learner[k+2][0])*(Learner[k][0]-Learner[k+2][0])+(Learner[k][1]-Learner[k+2][1])*(Learner[k][1]-Learner[k+2][1]));
            double line2=sqrt((Learner[k+2][0]-Learner[k+4][0])*(Learner[k+2][0]-Learner[k+4][0])+(Learner[k+2][1]-Learner[k+4][1])*(Learner[k+2][1]-Learner[k+4][1]));
            double line3=sqrt((Learner[k][0]-Learner[k+4][0])*(Learner[k][0]-Learner[k+4][0])+(Learner[k][1]-Learner[k+4][1])*(Learner[k][1]-Learner[k+4][1]));
            *(prt+k)=acos((line1*line1+line2*line2-line3*line3)/(2*line1*line2))*180.0/3.14;
            if (camera_show::Thread_num==1)
            {
                angle_camera[k]=*(prt+k);
            }
            else if (camera_show::Thread_num==2)
            {
                angle_image[k]=*(prt+k);  
            }
        }
       
      
        for (int n = 0; n < 8; n++)
        {                
            if ((angle_camera[n]<(angle_image[n]-20)) || (angle_camera[n]>(angle_image[n]+20)))
            {
                angle_check[n]=n+1;
            }
            else{
                angle_check[n] = 0;
            }   
        }

        for (const auto& jointLine : kJointLineList) 
        {
            if (keypoint_score[jointLine.first] >= kThresholdScoreKeyPoint && keypoint_score[jointLine.second] >= kThresholdScoreKeyPoint) {
                int32_t x0 = keypoint[jointLine.first].first;
                int32_t y0 = keypoint[jointLine.first].second;
                int32_t x1 = keypoint[jointLine.second].first;
                int32_t y1 = keypoint[jointLine.second].second;
                cv::line(mat, cv::Point(x0, y0), cv::Point(x1, y1), cv::Scalar(0, 255, 0), 6);
            }
            
            /*mark wrong joint lines*/
            if (camera_show::Thread_num==1)
            {
                for (int k = 0; k <8; k++)
                {
                    if(angle_check[k]!=0)
                    {
                    cv::line(mat, cv::Point(Learner[k+2][0], Learner[k+2][1]), cv::Point(Learner[k][0], Learner[k][1]), cv::Scalar(0, 0, 255), 6);
                    cv::line(mat, cv::Point(Learner[k+2][0], Learner[k+2][1]), cv::Point(Learner[k+4][0], Learner[k+4][1]), cv::Scalar(0, 0, 255), 6);
                    }
                }
            }
            
            
        }

        /* Display joints */
        for (size_t j = 0; j < keypoint.size(); j++) {
            if (keypoint_score[j] >= kThresholdScoreKeyPoint) {
                const auto& p = keypoint[j];
                cv::circle(mat, cv::Point(p.first, p.second), 5, cv::Scalar(0, 255, 0),2);
            }
            /*mark wrong joints*/
            if (camera_show::Thread_num==1)
            {
                for(int k=0; k<8; k++)
                {
                    if(angle_check[k] !=0)
                    {
                    cv::circle(mat, cv::Point(Learner[k+2][0], Learner[k+2][1]), 5, cv::Scalar(0, 0, 255),2);
                    }
                }
            }
            
            
        }
        delete []prt;
    }
    
    return 0;
}
