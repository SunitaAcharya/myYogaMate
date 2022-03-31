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

public:
    image_helper() 
    {

    }

    void source_check(const std::string& input_name,cv::VideoCapture& cap);
    bool key_check(cv::VideoCapture& cap);
    std::string getimgname();

    ~image_helper()
    {

    }

};
