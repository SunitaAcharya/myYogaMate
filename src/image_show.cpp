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

/***** cam_process function aims to process images from webcam *****/
int32_t camera_show::cam_process (std::string Webcam_id)
{
    mtx.lock(); // lock
    Thread_num = 1; // 1 is webcam thread
    m_input_name_cam = Webcam_id;

    cv::VideoCapture cap; 

    /***** create image_helper instance and check webcam id *****/
    image_check check_source;
    check_source.source_check(m_input_name_cam,cap);

    /***** create writer *****/
    cv::VideoWriter writer;   
    ImageProcessor_Initialize::InputParam input_param = { WORK_DIR, 2 };
    if (ImageProcessor_Initialize::Initialize(input_param) != 0) 
    {
        std::cout<< "Initialization Error" << std::endl;
        return -1;
    }

    /***** output each frame *****/
    /***** add lines in each frame *****/
    int32_t frame_cnt = 0;
    for (frame_cnt = 0; cap.isOpened() || frame_cnt < LOOP_NUM_FOR_TIME_MEASUREMENT; frame_cnt++) 
    {
        cv::Mat image;
        if (cap.isOpened()) 
        {
            cap.read(image);
        } 
        else 
        {
            image = cv::imread(m_input_name_cam);
        }

        if (image.empty()) break;
        ImageProcessor_Process::Result result;
        ImageProcessor_Process::Process(image, result);

        /***** set webcam cv parameters, resize and flip *****/
        image_helper cam_cv_set;
        cam_cv_set.cv_setparam(image, 3, 1, 1);

        /***** show images *****/
        if (writer.isOpened()) writer.write(image);
        cv::imshow("Webcam", image);

        /***** create image_helper instance and check the pressed key *****/
        if (cap.isOpened()) 
        {
            key Keycheck;
            if(Keycheck.key_check(cap)) 
            {
                key_status = 1;
                return -1;
            }
        };  
    }

    /***** finalize image process *****/
    ImageProcessor_Finalize::Finalize();
    if (writer.isOpened()) writer.release();  
    mtx.unlock(); // unlock
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


