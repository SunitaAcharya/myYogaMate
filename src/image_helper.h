//#pragma once
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#define DEFAULT_IMAGE_PATH            RESOURCE_DIR

class image_helper
{
protected:


private:

    cv::Mat img;
    int cam_id = -1;

    std::string image_input_name = DEFAULT_IMAGE_PATH;
    
    cv::Mat m_mat;
    double m_zoom;
    bool m_flip;
    double fps;
    std::string fps_result;

public:
    image_helper() 
    {

    }

    void source_check(const std::string& input_name,cv::VideoCapture& cap);
    bool key_check(cv::VideoCapture& cap);
    std::string getimgname();
    void cv_setparam(cv::Mat& mat, double zoom, bool flip);

    ~image_helper()
    {

    }

};
