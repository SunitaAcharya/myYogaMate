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

/* an interface for key function */
class KeyInterface 
{
public:
    virtual ~KeyInterface() {}
    virtual bool key_check(cv::VideoCapture& cap)=0;
    virtual std::string get_img_name(void)=0;
};


class image_helper
{
private:
    
    cv::Mat m_mat;
    double m_zoom;
    bool m_flip;
    double fps;
    std::string fps_result;

public:
    
    image_helper() {}
    ~image_helper() {}

    //std::string set_img_name();
    void cv_setparam(cv::Mat& mat, double zoom, bool flip, bool showFPS);  

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

/*This class is about image change processes */
class key : public KeyInterface
{
private:
    //std::string input_name1 = DEFAULT_IMAGE_PATH;
public:
    key() {}
    ~key() {}
    static std::string image_input_name;
    virtual bool key_check(cv::VideoCapture& cap);
    virtual std::string get_img_name(void);

};

