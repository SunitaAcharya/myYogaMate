#include <iostream>
#include<thread>

#define NUM_THREADS 2
#include "image_show.h"
#include"image_helper.h"

#define DEFAULT_IMAGE_PATH            RESOURCE_DIR "yogapose1.jpg"
#define DEFAULT_WEBCAM_ID             "0"

class IMAGESHOWCallback : public IMAGEcallback 
{
	virtual void yoga_thread(std::string cam_path, std::string img_path) 
    {
        image_show yoga_img;
        camera_show yoga_cam;

        // check error and key status to break the loop
        // create two threads, run cam_process until finishing image process 
        std::thread th_img(&image_show::img_process, &yoga_img, img_path);
        th_img.join();
        std::thread th_cam(&camera_show::cam_process, &yoga_cam, cam_path);       
        th_cam.join();
	}
};

int main(int argc, char *argv[]) 
{
	IMAGESHOWCallback imageshowcallback;
    image_show yoga_img;
    yoga_img.registerCallback(&imageshowcallback);
    yoga_img.start();
    yoga_img.stop();
    //std::cout << "program end ! \n" << std::endl;
	return 0;
}


