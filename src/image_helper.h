/**
*@file image_helper.h
*@brief functions for helping other files to analyze image poses
*
*MIT License
*
*Copyright (c) 2022 SunitaAcharya
*
*/

#pragma once
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#define DEFAULT_IMAGE_PATH1            RESOURCE_DIR

/**
 * @brief An interface for the image_check function.
 * This interface defines a pure virtual function for checking the image source type.
 * 
 */
class ImageSourceInterface 
{
public:
    virtual ~ImageSourceInterface() {}
/**
 * @brief In this application, if detecting the image type as jpg or png, then open the image,
 * else, read from the camera.
*/
    virtual int source_check(const std::string& input_name,cv::VideoCapture& cap)=0;
};

/**
 * @brief An interface for key function 
 * This interface defines two pure virtual functions. 
 * 
*/
class KeyInterface 
{
public:
    virtual ~KeyInterface() {}
    
/**
 * @brief One is to check users' input to change the images.
 * When changing the image, first the camera will pause for a while. After changing the image, reopen the camera.
 * 
*/
    virtual bool key_check(cv::VideoCapture& cap)=0;

/**
 * @brief This function is about returning the specific source path name when users change the image.
 * 
*/
    virtual std::string get_img_name(void)=0;
};

/**
 * @brief The image_helper class includes some helpful functions for showing the image window and camera window.
 * 
*/

struct tips_settings 
{
/**
 * @brief The tips_settings for all tips shown in the images for users.
 * 
*/
    std::string image1_comment1 = " Warrior II ";
    std::string image1_comment2 = " Tips: ";
    std::string image1_comment3 = " 1: Stand with feet wide, 3-4 feet apart";
    std::string image1_comment4 = " 2: Turn your left foot out 90 degrees";
    std::string image1_comment5 = " 3: Bend your left knee to a 90 degree";
    std::string image1_comment6 = " 4: Bring arms to a T at shoulder height";
    std::string image1_comment7 = " 5: Draw your shoulder blades down the back";

    std::string image2_comment1 = " Bound Ankle Pose ";
    std::string image2_comment2 = " Tips: ";
    std::string image2_comment3 = " 1: Sitting on the floor";
    std::string image2_comment4 = " 2: bend knees and open them out";
    std::string image2_comment5 = " 3: Bring your palms in front of your sternum";
    //std::string image2_comment6 = "";
    //std::string image2_comment7 = "";

    std::string image3_comment1 = " Chaturanga ";
    std::string image3_comment2 = " Tips: ";
    std::string image3_comment3 = " 1: Gently tuck the taibone";
    std::string image3_comment4 = " 2: Down pull the shoulders";
    std::string image3_comment5 = " 3: Back the stomach is strong";
    //std::string image3_comment6 = "";
    //std::string image3_comment7 = "";

    std::string image4_comment1 = " Body Stretches ";
    std::string image4_comment2 = " Tips: ";
    std::string image4_comment3 = " 1: Raise your arms";
    std::string image4_comment4 = " 2: Spread your fingers";
    std::string image4_comment5 = " 3: Reach up through your fingertips";
    //std::string image4_comment6 = "";
    //std::string image4_comment7 = "";

    std::string image5_comment1 = " Plow Pose ";
    std::string image5_comment2 = " Tips: ";
    std::string image5_comment3 = " 1: Sit at the front end of your mat";
    std::string image5_comment4 = " 2: Lie back over the blankets";
    std::string image5_comment5 = " 3: Bring your knees toward your chest";
    std::string image5_comment6 = " 4: Using the strength of your abs";
    std::string image5_comment7 = " 5: Lower your legs backward over your head";

    std::string image6_comment1 = " Upward-Facing Dog ";
    std::string image6_comment2 = " Tips: ";
    std::string image6_comment3 = " 1: Keep your feet on the mat";
    std::string image6_comment4 = " 2: Point your toes";
    std::string image6_comment5 = " 3: Press the tops of your feet down";
    std::string image6_comment6 = " 4: Straighten as much as possible";
    std::string image6_comment7 = " 5: Slowly lower down onto your stomach";

};


class image_helper
{
private:
    
    cv::Mat m_mat;
    double m_zoom;
    double fps;
    std::string fps_result;
    tips_settings tips;

public:
    
    image_helper() {}
    ~image_helper() {}
    static double zoomsize;

/**
 * @brief The cv_FPS function refers to frame per second. This function calculates how many frames per second the system processes.
 * The FPS result will be shown on the left top side of the camera window.
 * 
*/
    void cv_FPS(cv::Mat& mat);

/**
 * @brief In image_processor function. The system needs to compare the users' pose with the image pose.
 * The pose_alert function will be used to give the text feedback on the screen about users' poses.  
 * If the users' pose is correct, The message will be 'Your pose is correct, keep it!', if not the message is 'Your pose is incorrect'.
 * 
*/
    void pose_alert(cv::Mat& mat);

/**
 * @brief The resize functions are overloaded to adjust the window size of the image window and camera window.
 * 
*/
    void cv_resize(cv::Mat& mat); // overload for webcam window
    void cv_resize(cv::Mat& mat, double ratio); //overload for fixed image window
    void cv_flip(cv::Mat& mat);

};

/**
 * @brief This class is the derived class of ImageSourceInterface. The image_check is about checking the image source path.
 * Detecting and checking if the image source type is 'jpg' or 'png'.
 * Also check if the camera is opened correctly.
 * If the image or camera does not open correctly, output a message and stop the system.
 * 
*/
class image_check : public ImageSourceInterface
{
private:
    cv::Mat img;
    int cam_id = 0;
public:
    image_check() {}
    ~image_check() {}

    virtual int source_check(const std::string& input_name,cv::VideoCapture& cap);

};

/**
 * @brief This class is the derived class of KeyInterface. The key function is about identifying the input command by users.
 * 
*/
class key : public KeyInterface
{
private:
    //std::string input_name1 = DEFAULT_IMAGE_PATH;
public:
    key() {}
    ~key() {}
    static std::string image_input_name;

/**
 * @brief This function is mainly about realizing change image processes.
 * If users want to change the image, they can type '1' to check the first image. Type '2' to check the second image. Type '3' to check the third image.
 * At this time, there are 6 images shown as examples.
 * If users want to end the application, they can type 'q'.
 * Once the user changes the image, the specific image path will be returned by get_img_name function.
 *  
*/
    virtual bool key_check(cv::VideoCapture& cap);
    virtual std::string get_img_name(void);

};

