#include <iostream>
#include <string>
#include <mutex>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>


#include "image_processor.h"
#include "common_helper_cv.h"
#include "image_show.h"
#include "image_helper.h"

#define WORK_DIR                      RESOURCE_DIR
#define LOOP_NUM_FOR_TIME_MEASUREMENT 10
std::mutex mtx;

/***** global variables *****/
int Thread_num = 0;
int BOOL[8]={0,0,0,0,0,0,0,0};
double angle0[8]={0,0,0,0,0,0,0,0};

/***** static variables from image_show class *****/
bool camera_show::key_status = 0;
std::string camera_show::m_input_name_cam;
std::string image_show::m_input_name_img;

/***** cam_process function aims to process images from webcam *****/
int32_t camera_show::cam_process (std::string Webcam_id)
{
    mtx.lock(); // lock
    Thread_num = 1; // 1 is webcam thread
    m_input_name_cam = Webcam_id;

    cv::VideoCapture cap; 

    /***** create image_helper instance and check webcam id *****/
    image_check check_source;
    check_source.source_check(m_input_name_cam,cap);

    /***** create writer *****/
    cv::VideoWriter writer;   
    ImageProcessor_Initialize::InputParam input_param = { WORK_DIR, 2 };
    if (ImageProcessor_Initialize::Initialize(input_param) != 0) 
    {
        std::cout<< "Initialization Error" << std::endl;
        return -1;
    }

    /***** output each frame *****/
    /***** add lines in each frame *****/
    int32_t frame_cnt = 0;
    for (frame_cnt = 0; cap.isOpened() || frame_cnt < LOOP_NUM_FOR_TIME_MEASUREMENT; frame_cnt++) 
    {
        cv::Mat image;
        if (cap.isOpened()) 
        {
            cap.read(image);
        } 
        else 
        {
            image = cv::imread(m_input_name_cam);
        }

        if (image.empty()) break;
        ImageProcessor_Process::Result result;
        ImageProcessor_Process::Process(image, result);

        /***** set webcam cv parameters, resize and flip *****/
        image_helper cam_cv_set;
        cam_cv_set.cv_setparam(image, 3, 1, 1);

        /***** show images *****/
        if (writer.isOpened()) writer.write(image);
        cv::imshow("Webcam", image);

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
    mtx.unlock(); // unlock
    return 0;    
}


/***** img_process function aims to process images from picture *****/
int32_t image_show::img_process (std::string Source_path)
{
    mtx.lock(); // lock
    Thread_num = 2; // 2 is webcam thread

    /***** change image source *****/
    key img;
    if (m_input_name_img.empty())
    {
        m_input_name_img = Source_path;
    }
    else m_input_name_img = img.get_img_name();
   
    /***** create image instance, check image format *****/
    cv::VideoCapture cap;
    image_check source_check_img;
    source_check_img.source_check(m_input_name_img,cap);

    /***** create writer *****/
    cv::VideoWriter writer;
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
        image = cv::imread(m_input_name_img);
    }
    ImageProcessor_Process::Result result;
    ImageProcessor_Process::Process(image, result);

    /***** set image cv parameters, resize and flip *****/
    image_helper img_cv_set;
    img_cv_set.cv_setparam(image, 0.2, 1, 0);
        
    /***** show images *****/
    if (writer.isOpened()) writer.write(image);
    cv::imshow("Image show", image);

    /***** finalize image process *****/
    ImageProcessor_Finalize::Finalize();
    if (writer.isOpened()) writer.release();
    Thread_num = 0; 
    mtx.unlock(); // before return 0;
    return 0;   
}

/***** multiple images are shown in one windows *****/
/***** set parameters for the images *****/
void image_show::multipleImage(std::vector<cv::Mat> imgVector, cv::Mat& dst, int imgCols) 
{
    /***** set max pixel for every images *****/
    const int MAX_PIXEL=600;
    int imgNum = imgVector.size();
    /***** set the longest side and resize to 600 pixel *****/
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

/***** set paths of the images *****/
/***** show multiple images *****/
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

    imageVector.push_back(image1);
    imageVector.push_back(image2);
    imageVector.push_back(image3);
    imageVector.push_back(image4);
    imageVector.push_back(image5);
    imageVector.push_back(image6);
    /***** set the window parameters*****/
    multipleImage(imageVector, dst, 3);
    /***** set image window *****/
    cv::namedWindow("My Yoga Mate");
    cv::imshow("My Yoga Mate", dst);
    std::cout << "Please press any key to start" << std::endl;
    cv::waitKey(0);
}
