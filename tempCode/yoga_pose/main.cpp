/*** Include ***/
/* for general */
#include <cstdint>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <chrono>

/* for OpenCV */
#include <opencv2/opencv.hpp>

/* for My modules */
#include "image_processor.h"
#include "common_helper_cv.h"
#include <thread>
#include <mutex> 

using namespace std;
using namespace cv;
mutex mtx;  

/*** Macro ***/
#define WORK_DIR                      RESOURCE_DIR
//#define DEFAULT_INPUT_IMAGE           RESOURCE_DIR"/body_00.jpg"
#define LOOP_NUM_FOR_TIME_MEASUREMENT 10


/*** Function ***/
// open camera function
int open_cam()
{
    
    VideoCapture cap(0);   /* if cap is not opened, src is still image */ //open the camera    

    // Create video writer to save output video 
    VideoWriter writer;
    //writer = cv::VideoWriter("out.mp4", cv::VideoWriter::fourcc('M', 'P', '4', 'V'), (std::max)(10.0, cap.get(cv::CAP_PROP_FPS)), cv::Size(static_cast<int32_t>(cap.get(cv::CAP_PROP_FRAME_WIDTH)), static_cast<int32_t>(cap.get(cv::CAP_PROP_FRAME_HEIGHT))));

    // Initialize image processor library 
    ImageProcessor::InputParam input_param = { WORK_DIR, 4 };
    if (ImageProcessor::Initialize(input_param) != 0) 
    {
        printf("Initialization Error\n");
        //return -1;
    }

    /*** Process for each frame ***/
    int32_t frame_cnt = 0;
    for (frame_cnt = 0; cap.isOpened() || frame_cnt < LOOP_NUM_FOR_TIME_MEASUREMENT; frame_cnt++) 
    {
        /* Read image */
        Mat image;
        if (cap.isOpened()) 
        {
            cap.read(image);
        } 

        /* Call image processor library */
        ImageProcessor::Result result;
        ImageProcessor::Process(image, result); //analyse the image

        /* Display result */
        if (writer.isOpened()) writer.write(image);
        imshow("Camera", image);

        /* Input key command */
        if (cap.isOpened()) 
        {
            if (CommonHelper::InputKeyCommand(cap)) break;
        };

    }
    
    /*** Finalize ***/
    /* Fianlize image processor library */
    ImageProcessor::Finalize();
    if (writer.isOpened()) writer.release();
    cv::waitKey(1);   

    return 0;
}

// open image function
int open_img()
{
    mtx.lock();
    VideoCapture cap("/home/siyuliu/C++/play_with_tflite/resource/body_00.jpg");   /* if cap is not opened, src is still image */ //open the camera    

    // Create video writer to save output video 
    VideoWriter writer;
    //writer = cv::VideoWriter("out.mp4", cv::VideoWriter::fourcc('M', 'P', '4', 'V'), (std::max)(10.0, cap.get(cv::CAP_PROP_FPS)), cv::Size(static_cast<int32_t>(cap.get(cv::CAP_PROP_FRAME_WIDTH)), static_cast<int32_t>(cap.get(cv::CAP_PROP_FRAME_HEIGHT))));

    // Initialize image processor library 
    ImageProcessor::InputParam input_param = { WORK_DIR, 4 };
    if (ImageProcessor::Initialize(input_param) != 0) 
    {
        printf("Initialization Error\n");
        //return -1;
    }

    /*** Process for each frame ***/
    int32_t frame_cnt = 0;
    for (frame_cnt = 0; cap.isOpened() || frame_cnt < LOOP_NUM_FOR_TIME_MEASUREMENT; frame_cnt++) 
    {
        /* Read image */
        Mat image;
        if (cap.isOpened()) 
        {
            cap.read(image);
        } 

        /* Call image processor library */
        ImageProcessor::Result result;
        ImageProcessor::Process(image, result); //analyse the image

        /* Display result */
        if (writer.isOpened()) writer.write(image);
        imshow("Image", image);

        /* Input key command */
        if (cap.isOpened()) 
        {
            if (CommonHelper::InputKeyCommand(cap)) break;
        };

    }
    
    /*** Finalize ***/
    /* Fianlize image processor library */
    ImageProcessor::Finalize();
    if (writer.isOpened()) writer.release();
    //cv::waitKey(1);   
    mtx.unlock();
    return 0;

/*
VideoCapture cap1("/home/siyuliu/C++/play_with_tflite/resource/body_00.jpg");
    Mat srcImage;
    cap1.read(srcImage);

    imshow("Image",srcImage);
    resizeWindow("Image",700,500);
    ImageProcessor::Finalize();
    waitKey(0);
    return 0;  
  
*/
    
}

int32_t main(int argc, char* argv[])
{

    thread img(open_img);
    thread cam(open_cam);
    //open_cam();

    img.join();
    cam.join();

    return 0;

    /*
    pthread_t pth_cam;    
    pthread_t pth_img;

    pthread_mutex_init(&mutex,NULL);
    int img=pthread_create(&pth_img,NULL,open_img,NULL);
    int cam=pthread_create(&pth_cam,NULL,open_cam,NULL);

    if(cam!=0)
    {
        cout<<"pthread_create open camera error !!!"<<cam<<endl;
    }
    if(img!=0)
    {
        cout<<"pthread_create open image error !!!"<<img<<endl;
    }       

    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);

    */
       
}


