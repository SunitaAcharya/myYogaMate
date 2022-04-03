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


class ImageProcessor_Finalize
{
    public:
    static int32_t Finalize(void);
};


#endif
