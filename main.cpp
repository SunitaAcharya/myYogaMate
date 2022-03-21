#include <iostream>
#include "image_show.h"

int32_t main(int argc, char* argv[])
{
    
    image_show yoga("0", "/home/yuan/Downloads/test3.jpg");

    yoga.img_process();
    yoga.cam_process();

    return 0;

}