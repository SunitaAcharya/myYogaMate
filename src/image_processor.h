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

class ImageProcessor_Initialize
{   
public:

typedef struct InputParam
{
    char work_dir[256];
    std::int32_t  num_threads;
} InputParam;

    static int32_t Initialize(const InputParam& input_param);
};

class ImageProcessor_Process
{   
private:
    double angle_image[8]={0,0,0,0,0,0,0,0};
    double angle_camera[8];
    int Learner[12][2];

public:
    static int angle_check[8];
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
