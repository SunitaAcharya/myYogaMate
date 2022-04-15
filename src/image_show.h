/**
*@file image_show.h
*@brief includes image_show and camera_show functions
*
*MIT License
*
*Copyright (c) 2022 SunitaAcharya
*
*/

#ifndef IMAGE_SHOW_H
#define IMAGE_SHOW_H

#include <iostream>
#include <string>
#include <vector>
#include <thread> // the C++11 standard
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

/**
* @brief Image callback function for main code to call function back.
* Include pure virtual function definition for creating two threads to show the image and camera at the same time
* 
*/
class IMAGEcallback{
    public:
    virtual void yoga_thread(std::string cam_path, std::string img_path) = 0;
};

/**
 * @brief image_show class for showing the analyzed image.
 * This class includes analyzing image pose function 'img_process'.
 * This class also includes the home page of the MyYogaMate application.
 * The setter and getter function for the private variable MAX_PIXEL.
 * The callback function, start and stop function which is used in the main code to start the MyYogaMate application,
 * and wait for the user to press the key to change the image or stop the application.
 * 
*/
class image_show
{
    private:
        static std::string m_input_name_img;
        std::vector<cv::Mat> imageVector; // mat variable used in multipleImage and homepage functions

        std::thread* imgThread = nullptr; // define a thread pointer for start and stop the application
        int running = 0;
        IMAGEcallback* imagecallback = nullptr;
        void run();
        static void exec(image_show* imageshow) { imageshow->run(); }

    public:
    /**
     * @brief Constructor and destructor function for image_show class
     * The destructor function runs every time when image_show function is called.
     * This will delete the pointer and release the memory each time.
     * 
    **/    
        image_show() { }
        ~image_show() { stop(); }
        
    /**
     * @brief This function is for reading and analyzing the image pose.
     * Thread number 2 is for showing images.
     * This function includes checking the image source type and path,
     * initializing, analyzing, and finalizing the image.
     * 
    */
        int32_t img_process(std::string Source_path);
        
    /**
     * @brief Creating a home page for the MyYogaMate application.
     * All the images will show on one home page for users to select at first.
     * 
    */
        void multipleImage(std::vector<cv::Mat> imgVector, cv::Mat& dst, int imgCols, int pixel);
        void homepage();

    /**
     * @brief Callback function for main code to call image_show function.
     * Define the start and stop functions for starting and stoping the application.
     * 
    */
        void registerCallback(IMAGEcallback* cb);
        void unRegisterCallback();
        void start();
        void stop();

};

/**
 * @brief image_show class for showing the analyzed the camera window.
 * This class includes analyzing user's pose from camera function 'cam_process'.
 * 
 */
class camera_show
{
private:
    static std::string m_input_name_cam;
    int32_t frame_cnt = 0;    

public:
    static int Thread_num; // Define the Thread_num variable for image_show.cpp and image_processor.cpp
    static bool key_status;
    
    camera_show() { }
    ~camera_show() { }
    
    /**
     * @brief This function is about reading and analyzing the user pose from the camera.
     * Thread number 1 is for reading users' poses from the camera.
     * This function includes checking the camera number,
     * initializing, analyzing, and finalizing the images from the camera.
     * 
    */
    int32_t cam_process(std::string Webcam_id);

};


#endif
