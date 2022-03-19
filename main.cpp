
#include <cstdint>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <pthread.h>
#include<thread>
using namespace std;
#define NUM_THREADS 5
#include <opencv2/highgui.hpp>
#include <mutex>

#include "image_processor.h"
#include "common_helper_cv.h"

#define WORK_DIR                      RESOURCE_DIR
#define DEFAULT_INPUT_IMAGE           RESOURCE_DIR"/body_00.jpg"
#define LOOP_NUM_FOR_TIME_MEASUREMENT 10
mutex mtx;

int Thread_num = 0;
int BOOL[8]={0,0,0,0,0,0,0,0};
double angle0[8]={0,0,0,0,0,0,0,0};


int32_t cam_process (string Webcam_id)
{
    mtx.lock();
    Thread_num = 1;
    std::string input_name = Webcam_id;
    //double angle0[8]={2,2,0,0,0,0,0,0};


    
    cv::VideoCapture cap;   
     if (!CommonHelper::FindSourceImage(input_name, cap)) {
         return -1;
     }

    cv::VideoWriter writer;
    
    ImageProcessor::InputParam input_param = { WORK_DIR, 4 };
     if (ImageProcessor::Initialize(input_param) != 0) {
         printf("Initialization Error\n");
         return -1;
     }

    int32_t frame_cnt = 0;
    for (frame_cnt = 0; cap.isOpened() || frame_cnt < LOOP_NUM_FOR_TIME_MEASUREMENT; frame_cnt++) {

        cv::Mat image;
        if (cap.isOpened()) {
            cap.read(image);
        } else {
            image = cv::imread(input_name);
        }
        if (image.empty()) break;

        flip(image, image, 1);
        cv::resize(image, image, cv::Size(), 2.5, 2.5);

        ImageProcessor::Result result;
        ImageProcessor::Process(image, result);



        if (writer.isOpened()) writer.write(image);
        cv::imshow("Webcam", image);

        if (cap.isOpened()) {
            if (CommonHelper::InputKeyCommand(cap)) break;
        };

        //double angle0[8]={2,2,0,0,0,0,0,0};
        //printf("Angle ===== %f, \n", angle0[1]);

        // printf("=== Finished %d frame ===\n\n", frame_cnt);
   
    }

    ImageProcessor::Finalize();
    if (writer.isOpened()) writer.release();
    
    cv::waitKey(-1);
    mtx.unlock();
    return 0;
    

}

int32_t img_process (string Source_path)
{
    mtx.lock();

    Thread_num = 2;
    std::string input_name = Source_path;

    cv::VideoCapture cap;   
     if (!CommonHelper::FindSourceImage(input_name, cap)) {
         return -1;
     }

    cv::VideoWriter writer;
 
    ImageProcessor::InputParam input_param = { WORK_DIR, 4 };
    if (ImageProcessor::Initialize(input_param) != 0) {
        printf("Initialization Error\n");
        return -1;
    }

        cv::Mat image;
        if (cap.isOpened()) {
            cap.read(image);
        } else {
            image = cv::imread(input_name);
        }

        flip(image, image, 1);
        cv::resize(image, image, cv::Size(), 2.5, 2.5);

        ImageProcessor::Result result;
        ImageProcessor::Process(image, result);

        
      
        if (writer.isOpened()) writer.write(image);
        cv::imshow("Image show", image);

    //double angle0[8]={2,2,0,0,0,0,0,0};
    //printf("Angle ===== %f,\n", angle0[1]);

    ImageProcessor::Finalize();
    if (writer.isOpened()) writer.release();
    //cv::waitKey(-1);
    
    Thread_num = 0;
    mtx.unlock(); // before return 0;
    return 0;
    
}



int32_t main(int argc, char* argv[])
{
    string cam_path = "0";
    string img_path = "/home/yuan/Downloads/test2.jpg";


    thread th_img(img_process, img_path);
    th_img.join();


    thread th_cam(cam_process,cam_path);
    th_cam.join();
    
    return 0;

}