#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <mutex>
#include <opencv2/highgui.hpp>

#include "image_processor.h"
#include "common_helper_cv.h"
#include "image_show.h"

#define WORK_DIR                      RESOURCE_DIR
#define LOOP_NUM_FOR_TIME_MEASUREMENT 10
std::mutex mtx;

/***** global variables *****/
int Thread_num = 0;
int BOOL[8]={0,0,0,0,0,0,0,0};
double angle0[8]={0,0,0,0,0,0,0,0};

/***** static variables from image_show class *****/
bool camera_show::key_status = 0;
std::string camera_show::m_input_name_cam;
std::string image_show::m_input_name_img;

/*
int32_t image_show::cam_process ()
{
    mtx.lock();
    Thread_num = 1;
    std::string input_name = _Webcam_id;
    //double angle0[8]={2,2,0,0,0,0,0,0};
    
    cv::VideoCapture cap;   
     if (!CommonHelper::FindSourceImage(input_name, cap)) {
         return -1;
     }

    cv::VideoWriter writer;
    
     ImageProcessor::InputParam input_param = { WORK_DIR, 4 };
      if (ImageProcessor::Initialize(input_param) != 0) {
          printf("Initialization Error\n");
          return -1;
      }

    int32_t frame_cnt = 0;
    for (frame_cnt = 0; cap.isOpened() || frame_cnt < LOOP_NUM_FOR_TIME_MEASUREMENT; frame_cnt++) {

        cv::Mat image;
        if (cap.isOpened()) {
            cap.read(image);
        } else {
            image = cv::imread(input_name);
        }
        if (image.empty()) break;

        flip(image, image, 1);
        cv::resize(image, image, cv::Size(), 2.5, 2.5);

        ImageProcessor::Result result;
        ImageProcessor::Process(image, result);



        if (writer.isOpened()) writer.write(image);
        cv::imshow("Webcam", image);

        if (cap.isOpened()) {
            if (CommonHelper::InputKeyCommand(cap)) break;
        };

        //double angle0[8]={2,2,0,0,0,0,0,0};
        //printf("Angle ===== %f, \n", angle0[1]);

        // printf("=== Finished %d frame ===\n\n", frame_cnt);
   
    }

    ImageProcessor::Finalize();
    if (writer.isOpened()) writer.release();
    
    cv::waitKey(-1);
    mtx.unlock();
    return 0;
    

}
*/

/***** img_process function aims to process images from picture *****/
int32_t image_show::img_process (std::string Source_path)
{
    mtx.lock(); // lock
    Thread_num = 2; // 2 is webcam thread

    /***** change image source *****/
    key img;
    if (m_input_name_img.empty())
    {
        m_input_name_img = Source_path;
    }
    else m_input_name_img = img.get_img_name();
   
    /***** create image instance, check image format *****/
    cv::VideoCapture cap;
    image_check source_check_img;
    source_check_img.source_check(m_input_name_img,cap);

    /***** create writer *****/
    cv::VideoWriter writer;
    ImageProcessor_Initialize::InputParam input_param = { WORK_DIR, 4 };
    if (ImageProcessor_Initialize::Initialize(input_param) != 0) 
    {
        std::cout<< "Initialization Error" << std::endl;
        return -1;
    }

    /***** add lines in images *****/
    cv::Mat image;
    if (cap.isOpened()) 
    {
        cap.read(image);
    } 
    else 
    {
        image = cv::imread(m_input_name_img);
    }
    ImageProcessor_Process::Result result;
    ImageProcessor_Process::Process(image, result);

    /***** set image cv parameters, resize and flip *****/
    image_helper img_cv_set;
    img_cv_set.cv_setparam(image, 2, 1, 0);
        
    /***** show images *****/
    if (writer.isOpened()) writer.write(image);
    cv::imshow("Image show", image);

    /***** finalize image process *****/
    ImageProcessor_Finalize::Finalize();
    if (writer.isOpened()) writer.release();
    Thread_num = 0; 
    mtx.unlock(); // before return 0;
    return 0;   
}

/***** img_process function aims to process images from picture *****/
int32_t image_show::img_process (std::string Source_path)
{
    mtx.lock(); // lock
    Thread_num = 2; // 2 is webcam thread

    /***** change image source *****/
    key img;
    if (m_input_name_img.empty())
    {
        m_input_name_img = Source_path;
    }
    else m_input_name_img = img.get_img_name();
   
    /***** create image instance, check image format *****/
    cv::VideoCapture cap;
    image_check source_check_img;
    source_check_img.source_check(m_input_name_img,cap);

    /***** create writer *****/
    cv::VideoWriter writer;
    ImageProcessor_Initialize::InputParam input_param = { WORK_DIR, 4 };
    if (ImageProcessor_Initialize::Initialize(input_param) != 0) 
    {
        std::cout<< "Initialization Error" << std::endl;
        return -1;
    }

    /***** add lines in images *****/
    cv::Mat image;
    if (cap.isOpened()) 
    {
        cap.read(image);
    } 
    else 
    {
        image = cv::imread(m_input_name_img);
    }
    ImageProcessor_Process::Result result;
    ImageProcessor_Process::Process(image, result);

    /***** set image cv parameters, resize and flip *****/
    image_helper img_cv_set;
    img_cv_set.cv_setparam(image, 2, 1, 0);
        
    /***** show images *****/
    if (writer.isOpened()) writer.write(image);
    cv::imshow("Image show", image);

    /***** finalize image process *****/
    ImageProcessor_Finalize::Finalize();
    if (writer.isOpened()) writer.release();
    Thread_num = 0; 
    mtx.unlock(); // before return 0;
    return 0;   
}

