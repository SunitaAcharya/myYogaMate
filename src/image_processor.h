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
    typedef struct Result
    {
    double time_pre_process;   // [msec]
    double time_inference;    // [msec]
    double time_post_process;  // [msec]
    } Result;

    static int32_t Process(cv::Mat& mat, Result& result);
    
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
