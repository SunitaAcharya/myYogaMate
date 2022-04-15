/**
*@file image_processor.cpp
*@brief helper functions about each analyzing images steps
*
*MIT License
*
*Copyright (c) 2022 SunitaAcharya
*
*/

#include <iostream>
#include <string>
#include <chrono> 
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include "image_helper.h"
#include "image_processor.h"

#define DEFAULT_IMAGE_PATH_IMAGEHELPER            RESOURCE_DIR

extern int BOOL[8];
/***** static variables from image_helper class *****/
std::string key::image_input_name = DEFAULT_IMAGE_PATH_IMAGEHELPER "yogapose1.jpg";
double image_helper::zoomsize = 1.0;


int image_check::source_check(const std::string& input_name,cv::VideoCapture& cap)
{
    /*** read image, check the image type and read image ("string::npos" means not found) ***/
	if (input_name.find(".jpg") != std::string::npos || input_name.find(".png") != std::string::npos) 
    {
    	img = cv::imread(input_name);
    	if(img.empty()) // check if image read corrctly
    	{
    		std::cout << "Input source NOT found !!";
    		return -1;
    	}
        else
        {
            return 0;
        }
    }
    else
    {
        cam_id = stoi(input_name); // stoi : Convert string to integer, directly check the number in this string
        
        if(cam_id >= 0)
        {
            cap=cv::VideoCapture(cam_id);
            if (!cap.isOpened()) // Check if the camera is open successfully
            {
                std::cout<<" Open camera FAIL !! ";
                return -1;
            }
            else
            {
                return 0;
            }  
        }
        else if ((input_name.find(".jpg") == std::string::npos) && (input_name.find(".png") == std::string::npos) && (cam_id < 0))
        {
            return -1;
        }
               
    }
}

/***** check the users command(key) for changing the image or stop the application ****/
bool key::key_check(cv::VideoCapture& cap)
{
    int32_t key=cv::waitKey(1)&0xff;
    bool ret_to_quit = false;
        switch (key) 
        {
        case 'q': // stop the application
            cap.release();
            ret_to_quit = true;
            break;

        case '1': // refer to image 1
            cap.release();
            image_input_name = DEFAULT_IMAGE_PATH_IMAGEHELPER "yogapose1.jpg";
            ret_to_quit = false;
            break;
        
        case '2': // refer to image 2
            cap.release();
            image_input_name = DEFAULT_IMAGE_PATH_IMAGEHELPER "yogapose2.jpg";
            ret_to_quit = false;
            break;
        
        case '3':
            cap.release();
            image_input_name = DEFAULT_IMAGE_PATH_IMAGEHELPER "yogapose3.jpg";
            ret_to_quit = false;
            break;
        
        case '4':
            cap.release();
            image_input_name = DEFAULT_IMAGE_PATH_IMAGEHELPER "yogapose4.jpg";
            ret_to_quit = false;
            break;
        
        case '5':
            cap.release();
            image_input_name = DEFAULT_IMAGE_PATH_IMAGEHELPER "yogapose5.jpg";
            ret_to_quit = false;
            break;
        case '6':
            cap.release();
            image_input_name = DEFAULT_IMAGE_PATH_IMAGEHELPER "yogapose6.jpg";
            ret_to_quit = false;
            break;
        case ',': // resize the window size
            if(image_helper::zoomsize > 0.21) image_helper::zoomsize = image_helper::zoomsize - 0.2;
            else std::cout << "The size is too small" << std::endl;
            ret_to_quit = false;
            break;
        case '.':
            if(image_helper::zoomsize < 5) image_helper::zoomsize = image_helper::zoomsize + 0.2;
            else std::cout << "The size is too large" << std::endl;
            ret_to_quit = false;
            break;
        }
    
    return ret_to_quit;
}

std::string key::get_img_name(void)
{  
    return image_input_name; // return image source path when users change the image
}

/***** function cv_FPS, show FPS in images *****/
void image_helper::cv_FPS(cv::Mat& mat) 
{
    /***** initialise *****/
    if (mat.empty() == 1)
    {
        std::cout << "The input image is empty" << std::endl;
    }  
    else m_mat = mat;
    
    /***** calculate FPS *****/
    static auto time1 = std::chrono::steady_clock::now();
    auto time2 = std::chrono::steady_clock::now();
    fps = 1e9 / (time2 - time1).count();
    time1 = time2;
    fps_result = "FPS: " + std::to_string(fps);

    /***** process image *****/
    /***** show FPS result on the camera window  *****/
    cv::putText(m_mat, fps_result, cv::Point(2,15), cv::FONT_HERSHEY_SIMPLEX,0.5, cv::Scalar (0,0,0), 2, 8); 
    
}

/***** function pose_alert, show pose information such as pose correct or pose incorrect in images *****/
void image_helper::pose_alert(cv::Mat& mat)
{
    int posecorrect[8] = {0,0,0,0,0,0,0,0}; // initialize the variables
    int count = 0;
    bool arraysEqual = true;
    while (arraysEqual && count < 8)
    {
        if (ImageProcessor_Process::angle_check[count] != posecorrect[count])
            arraysEqual = false;
        count++;
    }

    /***** show correct or incorrect information *****/
    if (arraysEqual)
        cv::putText(mat, "Your pose is correct, keep it!", cv::Point(105,35), cv::FONT_HERSHEY_SIMPLEX,1, cv::Scalar (0,128,128), 2, 12);
    else
        cv::putText(mat, "    Your pose is incorrect    ", cv::Point(105,35), cv::FONT_HERSHEY_SIMPLEX,1, cv::Scalar (0,0,255), 2, 12);
    
}

/***** function cv_resize, resize window (overload) *****/
/***** change size of the window by pressing "," (<) or "." (>) *****/
void image_helper::cv_resize(cv::Mat& mat)
{
    /***** set window size *****/
    if (mat.empty() == 1)
    {
        std::cout << "The input image is empty" << std::endl; // check image
    }  
    else m_mat = mat;
    cv::resize(mat, mat, cv::Size(), zoomsize, zoomsize); // resize the window
}

/***** function cv_resize, resize window (overload) *****/
/***** fixed size *****/
void image_helper::cv_resize(cv::Mat& mat, double ratio)
{
    if (mat.empty() == 1)
    {
        std::cout << "The input image is empty" << std::endl;
    }  
    else m_mat = mat;
    cv::resize(mat, mat, cv::Size(), ratio, ratio);

}

/***** function cv_flip, flip the images *****/
void image_helper::cv_flip(cv::Mat& mat)
{
    if (mat.empty() == 1)
    {
        std::cout << "The input image is empty" << std::endl;
    }  
    else m_mat = mat;
    cv::flip(m_mat, m_mat, 1);
}

