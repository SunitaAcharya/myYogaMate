#ifndef IMAGE_SHOW_H
#define IMAGE_SHOW_H

#include <iostream>
#include <string>

class image_show
{
    private:
        static std::string m_input_name_img;
   
    public:    
        image_show() { }
        ~image_show() { }
        int32_t img_process(std::string Source_path);
        
};

#endif