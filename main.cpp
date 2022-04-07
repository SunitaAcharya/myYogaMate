#include <iostream>
#include<thread>

#define NUM_THREADS 2
#include "image_show.h"
#include"image_helper.h"

#define DEFAULT_IMAGE_PATH            RESOURCE_DIR "yogapose1.jpg"
#define DEFAULT_WEBCAM_ID             "0"



int32_t main(int argc, char* argv[])
{   
     image_show homepage_show;
     homepage_show.homepage();
    /*two threads, th_img for image process and th_cam for webcam process*/
    /*th_img and th_cam, lock has been added in image_show::img_process and image_show::cam_process to avoid mixing-up common used variables */
    std::string cam_path = DEFAULT_WEBCAM_ID;
    std::string img_path = DEFAULT_IMAGE_PATH;
    while(1)
    {
        /***** create image_show instance *****/       
        image_show yoga_img;
        camera_show yoga_cam;

        /***** check error and key status to break the loop *****/
        if (camera_show::key_status == 1 || yoga_img.img_process(img_path) == -1 || yoga_cam.cam_process(cam_path) == -1) break;
        
        /***** create two threads, run cam_process until finishing image process *****/
        std::thread th_img(&image_show::img_process, &yoga_img, img_path);
        th_img.join();
        std::thread th_cam(&camera_show::cam_process, &yoga_cam, cam_path);       
        th_cam.join();
    }
    return 0;
}
