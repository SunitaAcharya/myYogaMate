//#pragma once
#include <iostream>
#include <string>


class image_helper
{
private:
    
    int _a;
    int _b;

    
public:
image_helper(int a,int b)
{
    this ->_a = a;
    this ->_b = b;
}
    void source_check();
    void key_check();
    void cv_set(); // temporarily



};
