/**
*@file image_show.cpp
*@brief implementation of functions from image_show and camera_show classes 
*
*MIT License
*
*Copyright (c) 2022 SunitaAcharya
*
*/

#include <iostream>
#include <string>
#include <mutex>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include "image_processor.h"
#include "image_show.h"
#include "image_helper.h"

#define WORK_DIR                      RESOURCE_DIR
#define LOOP_NUM_FOR_TIME_MEASUREMENT 10

/***** static variables from image_show class *****/
bool camera_show::key_status = 0;
std::string camera_show::m_input_name_cam;
std::string image_show::m_input_name_img;
int camera_show::Thread_num;
std::mutex mtx;

/***** cam_process function aims to process images from webcam *****/
int32_t camera_show::cam_process (std::string Webcam_id)
{
    mtx.lock(); // lock

    camera_show::Thread_num = 1; // thread number 1 is for webcam thread
    m_input_name_cam = Webcam_id; // assign webcam number for variable m_input_name_cam

    cv::VideoCapture cap; 

    /***** create image_helper instance and check webcam id *****/
    image_check check_source; // create check_shorce object
    int check = check_source.source_check(m_input_name_cam,cap);

    if(check == (-1)) // check if the camera source read successfully
    {
        return -1;
    }

    cv::VideoWriter writer; // creating writer

    // Initializing the camera process   
    ImageProcessor_Initialize::InputParam input_param = { WORK_DIR, 2 };
    if (ImageProcessor_Initialize::Initialize(input_param) != 0) 
    {
        std::cout<< "Initialization Error" << std::endl;
        return -1;
    }

    /***** Output each frame reading from camera *****/
    for (frame_cnt = 0; cap.isOpened() || frame_cnt < LOOP_NUM_FOR_TIME_MEASUREMENT; frame_cnt++) 
    {
        cv::Mat image;
        if (cap.isOpened()) 
        {
            cap.read(image); // open camera and read the images from camera
        } 
        else 
        {
            image = cv::imread(m_input_name_cam);
        }

        if (image.empty()) break; // check image

        ImageProcessor_Process imgpro;
        imgpro.Process(image); // Analyzing the image pose

        /***** set webcam cv parameters, resize and flip the image windows *****/
        image_helper cam_cv_set;
        cam_cv_set.cv_flip(image);
        cam_cv_set.pose_alert(image);
        cam_cv_set.cv_FPS(image);
        cam_cv_set.cv_resize(image);

        if (writer.isOpened()) writer.write(image);
        cv::imshow("Webcam", image); // show images

        /***** create image_helper instance and check the pressed key *****/
        if (cap.isOpened()) 
        {
            key Keycheck;
            if(Keycheck.key_check(cap)) 
            {
                key_status = 1;
                return -1;
            }
        };  
    }

    /***** finalize image process *****/
    ImageProcessor_Finalize::Finalize();
    if (writer.isOpened()) writer.release();

    mtx.unlock(); // unlock the thread
    return 0;    
}


/***** img_process function aims to process images from picture *****/
int32_t image_show::img_process (std::string Source_path)
{
    mtx.lock(); // lock the thread

    camera_show::Thread_num = 2;  // thread number 2 is for showing image 

    /***** change image source *****/
    key img;
    if (m_input_name_img.empty())
    {
        m_input_name_img = Source_path;
    }
    else m_input_name_img = img.get_img_name(); // change the image source if the user wants to change the image
   
    /***** create image instance, check image format *****/
    cv::VideoCapture cap;
    image_check source_check_img; // create check_shorce object
    int check = source_check_img.source_check(m_input_name_img,cap);
    if(check == (-1)) // check if the image source read successfully
    {
        return -1;
    }
    
    cv::VideoWriter writer; // create writer

    // Initializing the image process
    ImageProcessor_Initialize::InputParam input_param = { WORK_DIR, 4 };
    if (ImageProcessor_Initialize::Initialize(input_param) != 0) 
    {
        std::cout<< "Initialization Error" << std::endl;
        return -1;
    }

    /***** add lines in images *****/
    cv::Mat image;
    if (cap.isOpened()) 
    {
        cap.read(image);
    } 
    else 
    {
        image = cv::imread(m_input_name_img); // read image from specific source
    }
    
    ImageProcessor_Process imgpro;
    imgpro.Process(image); // Analysing the image pose

    /***** set image cv parameters, resize and flip *****/
    image_helper img_cv_set;
    image_helper white_cv_set;
    img_cv_set.cv_flip(image);

    /***** set fixed pexel *****/
    cv::Mat whiteimage = cv::imread(WORK_DIR "white.jpg");  
    imageVector.push_back(image);
    imageVector.push_back(whiteimage);
    multipleImage(imageVector, image, 1, 750);
    img_cv_set.cv_comment(image);

    /***** show images *****/
    if (writer.isOpened()) writer.write(image);
    cv::imshow("Image show", image); // show images

    /***** finalize image process *****/
    ImageProcessor_Finalize::Finalize();
    if (writer.isOpened()) writer.release();
    
    camera_show::Thread_num=0; 
    mtx.unlock(); // before return 0;
    return 0;   
}

/***** multiple images are shown in one windows *****/
/***** set parameters for the images *****/
void image_show::multipleImage(std::vector<cv::Mat> imgVector, cv::Mat& dst, int imgCols, int pixel)
{
    /***** set max pixel for every images *****/
    const int MAX_PIXEL = pixel;
    int imgNum = imgVector.size();

    /***** set the longest side and resize to fixed pixel *****/
    cv::Size imgOriSize = imgVector[0].size();
    int imgMaxPixel = std::max(imgOriSize.height, imgOriSize.width);

    /***** get ratio of the max pixel *****/
    double prop = imgMaxPixel < MAX_PIXEL ?  (double)imgMaxPixel/MAX_PIXEL : MAX_PIXEL/(double)imgMaxPixel;

    /***** show the fixed size of images *****/
    cv::Size imgStdSize(imgOriSize.width * prop, imgOriSize.height * prop);

    /***** standard image *****/
    cv::Mat imgStd;
    /***** start from (0,0) coordinate *****/
    cv::Point2i location(0, 0);

    /***** create image window *****/
    cv::Mat imgWindow(imgStdSize.height*((imgNum-1)/imgCols + 1), imgStdSize.width*imgCols, imgVector[0].type());
    for (int i=0; i<imgNum; i++)
    {
        location.x = (i%imgCols)*imgStdSize.width;
        location.y = (i/imgCols)*imgStdSize.height;
        cv::resize(imgVector[i], imgStd, imgStdSize, prop, prop, cv::INTER_LINEAR);
        imgStd.copyTo( imgWindow( cv::Rect(location, imgStdSize) ) );
    }
    dst = imgWindow;
}

/***** define the home page for application and set paths of each images *****/
void image_show::homepage()
{
    /***** create images *****/
    cv::Mat image1 = cv::imread(WORK_DIR "yogapose1.jpg");
    cv::Mat image2 = cv::imread(WORK_DIR "yogapose2.jpg");
    cv::Mat image3 = cv::imread(WORK_DIR "yogapose3.jpg");
    cv::Mat image4 = cv::imread(WORK_DIR "yogapose4.jpg");
    cv::Mat image5 = cv::imread(WORK_DIR "yogapose5.jpg");
    cv::Mat image6 = cv::imread(WORK_DIR "yogapose6.jpg");
    cv::Mat dst;
    /***** flip all images *****/
    image_helper flipimage;
    flipimage.cv_flip(image1);
    flipimage.cv_flip(image2);
    flipimage.cv_flip(image3);
    flipimage.cv_flip(image4);
    flipimage.cv_flip(image5);
    flipimage.cv_flip(image6);

    imageVector.push_back(image1);
    imageVector.push_back(image2);
    imageVector.push_back(image3);
    imageVector.push_back(image4);
    imageVector.push_back(image5);
    imageVector.push_back(image6);

    /***** set the window parameters*****/
    multipleImage(imageVector, dst, 3, 600);

    /***** set image window *****/
    cv::namedWindow("My Yoga Mate");
    cv::imshow("My Yoga Mate", dst);
    std::cout << "Please press any key to start" << std::endl;
    cv::waitKey(0);
}

/******** callback function for image show ***********/
void image_show::registerCallback(IMAGEcallback* cb)
{
    imagecallback = cb;
}
void image_show::unRegisterCallback() 
{
	imagecallback = nullptr;
}

void image_show::run()
{
    /***** set parameters and initialize them *****/
    std::string cam_path = "0";
    std::string img_path = WORK_DIR "yogapose1.jpg";
    running = 1;

    /***** show homepage any key press from users to start the application *****/
    image_show homepage_show;
    homepage_show.homepage();

    /***** run image and webcam *****/
    while(running)
    {
        /***** create yoga_img and yoga_cam instance *****/      
        image_show yoga_img;
        camera_show yoga_cam;

        /***** determine callback, key, img_process, and cam_process functions *****/
        if(nullptr != imagecallback)
        {
            if (camera_show::key_status == 1 || yoga_img.img_process(img_path) == -1 || yoga_cam.cam_process(cam_path) == -1) break;
            imagecallback->yoga_thread(cam_path, WORK_DIR "yogapose1.jpg");
        }
    }
}

/******* Start and stop functions for application *******/
void image_show::start()
{
    std::cout << "image start \n";
    if(nullptr != imgThread) // create thread
    {
        std::cout << "thread issue \n";
        return;
    }
    imgThread = new std::thread(exec, this); // after starting the application, run the 'run' function to analyze the images
}

void image_show::stop()
{
    running = 0; // stop the application after running the application
    if(nullptr != imgThread)
    {
        imgThread->join();
        cv::destroyAllWindows();
        delete imgThread; // delect the pointer to release the memory
        imgThread = nullptr;
    }
}

