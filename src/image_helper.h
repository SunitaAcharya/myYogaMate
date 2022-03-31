//#pragma once
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

class image_helper
{
protected:


private:

    int cam_id = -1;


public:
    image_helper() 
    {

    }

    void source_check(const std::string& input_name,cv::VideoCapture& cap);

    ~image_helper()
    {

    }

};
