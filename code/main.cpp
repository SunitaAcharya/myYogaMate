// main.cpp for open camera and image by using thread - (Version 1.1)
//13/03/2022 Siyu Liu

#include <iostream> //input and output stream
#include "opencam.h" // open camera and image multi-threads

int main(int argc, char* argv[])
{
	
    pthread_t pth_cam;    
	pthread_t pth_img;
	
	int img=pthread_create(&pth_img,NULL,open_img,NULL);
    int cam=pthread_create(&pth_cam,NULL,open_cam,NULL);

	if(cam!=0)
	{
		cout<<"pthread_create open camera error !!!"<<cam<<endl;
	}
    if(img!=0)
	{
		cout<<"pthread_create open image error !!!"<<img<<endl;
	}				

	pthread_exit(NULL);

}


