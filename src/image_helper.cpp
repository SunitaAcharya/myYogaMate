#include <iostream>
#include <string>
#include <chrono> //
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include "image_helper.h"

#define DEFAULT_IMAGE_PATH_IMAGEHELPER            RESOURCE_DIR

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


