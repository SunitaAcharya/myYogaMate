#pragma once
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#define DEFAULT_IMAGE_PATH1            RESOURCE_DIR //"Yoga1.jpg"

/* an interface for image_check function */
class ImageSourceInterface 
{
public:
    virtual ~ImageSourceInterface() {}
    virtual int source_check(const std::string& input_name,cv::VideoCapture& cap)=0;
};

/*This class is about checking the image source*/
class image_check : public ImageSourceInterface
{
private:
    cv::Mat img;
    int cam_id = 0;
public:
    image_check() {}
    ~image_check() {}

    virtual int source_check(const std::string& input_name,cv::VideoCapture& cap);

};
