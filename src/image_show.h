//#pragma once
#include <iostream>
#include <string>




class image_show
{
private:
    std::string _Webcam_id;
    std::string _Source_path;

    
public:
image_show(std::string Webcam_id, std::string Source_path)
{
    this ->_Webcam_id = Webcam_id;
    this ->_Source_path = Source_path;
}
    int32_t cam_process();
    int32_t img_process();



};