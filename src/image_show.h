#ifndef IMAGE_SHOW_H
#define IMAGE_SHOW_H

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

class IMAGEcallback{
    public:
    virtual void yoga_thread(std::string cam_path, std::string img_path) = 0;
};

class image_show
{
    private:
        static std::string m_input_name_img;
        std::vector<cv::Mat> imageVector;

        std::thread* imgThread = nullptr;
        int running = 0;
        IMAGEcallback* imagecallback = nullptr;
        void run();
        static void exec(image_show* imageshow) {
		imageshow->run();
	    }

    public:    
        image_show() { }
        ~image_show() { stop(); }
        int32_t img_process(std::string Source_path);
        void multipleImage(std::vector<cv::Mat> imgVector, cv::Mat& dst, int imgCols);
        void homepage();
        
        void registerCallback(IMAGEcallback* cb);
        void unRegisterCallback();
        void start();
        void stop();

};

class camera_show
{
private:
    static std::string m_input_name_cam;   

public:
    static bool key_status;
    camera_show() { }
    ~camera_show() { }
    int32_t cam_process(std::string Webcam_id);

};

#endif
