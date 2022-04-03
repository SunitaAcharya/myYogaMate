
/*** Include ***/
/* for general */
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <memory>
#include <unistd.h>
#include <string.h>
#include <iostream>

/* for OpenCV */
#include <opencv2/opencv.hpp>

/* for My modules */
#include "pose_engine.h"
#include "image_processor.h"

/*** Global variable ***/
std::unique_ptr<PoseEngine> s_engine;
extern int Thread_num;
extern double angle0[8];
    double angle[8];
    //double angle0[8];
    int Learner[12][2]; 

int32_t ImageProcessor_Initialize::Initialize(const ImageProcessor_Initialize::InputParam& input_param)
{

    s_engine.reset(new PoseEngine());
    if (s_engine->Initialize(input_param.work_dir, input_param.num_threads) != PoseEngine::kRetOk) 
    {
        s_engine->Finalize();
        s_engine.reset();
        return -1;
    }
    return 0;
}

int32_t ImageProcessor_Finalize::Finalize()
{
    if (!s_engine) 
    {
        
        std::cout<<"Not initialized\n"<<std::endl;
        return -1;
    }

    if (s_engine->Finalize() != PoseEngine::kRetOk) 
    {
        return -1;
    }

    return 0;
}

int32_t ImageProcessor_Command::Command(int32_t cmd)
{
    if (!s_engine) 
    {
        std::cout<<"Not initialized\n"<<std::endl;
        return -1;
    }

    switch (cmd) 
    {
    case 0:
    default:
        std::cout<<"command "<<cmd<<" is not supported\n"<<std::endl;
        return -1;
    }
}
