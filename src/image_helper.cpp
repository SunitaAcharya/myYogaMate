#include <iostream>
#include <string>
#include <chrono> 
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include "image_helper.h"

#define DEFAULT_IMAGE_PATH_IMAGEHELPER            RESOURCE_DIR

/***** static variables from image_helper class *****/
std::string key::image_input_name = DEFAULT_IMAGE_PATH_IMAGEHELPER "yogapose1.jpg";


int image_check::source_check(const std::string& input_name,cv::VideoCapture& cap)
{
	if (input_name.find(".jpg") != std::string::npos || input_name.find(".png") != std::string::npos) // read image ("string::npos" means not found)
    {
    	//cv::Mat img;
    	img = cv::imread(input_name);
    	if(img.empty())
    	{
    		std::cout << "Input source NOT found !!";
    		return 0;
    	}
    }   
    else // read from camera
    {
        //int cam_id = -1;       
        cam_id = stoi(input_name); // stoi : Convert string to integer, directly check the number in this string
        
        if(cam_id>=0)
        {
            cap=cv::VideoCapture(cam_id);
        }
        else
        {
            cap=cv::VideoCapture(input_name);
        } 
        
        if (!cap.isOpened()) // Check if the camera is open successfully
        {
            std::cout<<"Open camera FAIL !! ";
            return 0;
        }
    }
    return 0;
}

bool key::key_check(cv::VideoCapture& cap)
{
    int32_t key=cv::waitKey(1)&0xff;
    bool ret_to_quit = false;
        switch (key) 
        {
        case 'q':
            cap.release();
            ret_to_quit = true;
            break;

        case '1':
            cap.release();
            image_input_name = DEFAULT_IMAGE_PATH_IMAGEHELPER "yogapose1.jpg";
            ret_to_quit = false;
            break;
        
        case '2':
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
        }
    
    return ret_to_quit;
}

std::string key::get_img_name(void)
{  
    return image_input_name;
}


/***** function cv_showparam  //mat: input frame; // zoom: ratio of the windows; //flip: 0 no flip, 1 flip *****/
void image_helper::cv_setparam(cv::Mat& mat, double zoom, bool flip, bool showFPS) 
{
    /***** initialise and zoom *****/
    m_flip = flip;
    if (mat.empty() == 1)
    {
        std::cout << "The input image is empty" << std::endl;
    }  
    else m_mat = mat;
    if(zoom > 0 && zoom < 10) m_zoom = zoom;
    else std::cout << "The value should be between 0 and 10" << std::endl;

    /***** calculate FPS *****/
    static auto time1 = std::chrono::steady_clock::now();
    auto time2 = std::chrono::steady_clock::now();
    fps = 1e9 / (time2 - time1).count();
    time1 = time2;
    fps_result = "FPS: " + std::to_string(fps);

    /***** process image *****/
    // flip image, 0 original, 1 flip
    cv::flip(m_mat, m_mat, m_flip); 
    /***** show FPS *****/
    if (showFPS)
    cv::putText(m_mat, fps_result, cv::Point(10,50), cv::FONT_HERSHEY_SIMPLEX,1, cv::Scalar (0,0,0), 2, 8); 
    /***** set window size *****/
    cv::resize(m_mat, mat, cv::Size(), m_zoom, m_zoom); 
    
}