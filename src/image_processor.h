/**
*@file image_processor.h
*@brief classes about analysing images  
*
*@copyright Copytight (C) 2022
*
*
*/

#ifndef IMAGE_PROCESSOR_H_
#define IMAGE_PROCESSOR_H_

/* for general */
#include <string>
#include <vector>
#include <array>
#include <iostream>


namespace cv 
{
    class Mat;
};

/**
 * @brief This file is about analyzing the images from the specific source and camera.
 * This file includes all the steps of analyzing the image.
 * Before analyzing the image, initialize the image.
 * Then check if the image is initialized successfully by using the function 'Finalize'.
 * Next begin to analyze the images.
 * 
*/

class ImageProcessor_Initialize
{   
public:

typedef struct InputParam // define new InputParam type struct with parameters work_dir and num_threads
{
    char work_dir[256];
    std::int32_t  num_threads;
} InputParam;

    static int32_t Initialize(const InputParam& input_param);
};

class ImageProcessor_Process
{   
private:
double angle_camera[8]; // angle check for users' pose from camera
int Learner[12][2];

public:
    static int angle_check[8]; // comparing the angles of image pose and user's pose
    int32_t Process(cv::Mat& mat);
};

class ImageProcessor_Finalize
{
public:
    static int32_t Finalize(void);
};

class ImageProcessor_Command
{
public:
    static int32_t Command(int32_t cmd);
};


#endif
