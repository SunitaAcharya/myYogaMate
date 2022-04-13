#include <iostream>
#include <string>
#include <chrono> //
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
        case '6':
            cap.release();
            image_input_name = DEFAULT_IMAGE_PATH_IMAGEHELPER "yogapose6.jpg";
            ret_to_quit = false;
            break;
        case ',':
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
    return image_input_name;
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
    /***** show FPS *****/
    cv::putText(m_mat, fps_result, cv::Point(2,15), cv::FONT_HERSHEY_SIMPLEX,0.5, cv::Scalar (0,0,0), 2, 8); 
    
}

/***** function pose_alert, show pose information such as pose correct or pose incorrect in images *****/
void image_helper::pose_alert(cv::Mat& mat)
{
    int posecorrect[8] = {0,0,0,0,0,0,0,0};
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
        std::cout << "The input image is empty" << std::endl;
    }  
    else m_mat = mat;
    cv::resize(mat, mat, cv::Size(), zoomsize, zoomsize);
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

