// open camera and image multithreads - (Version 1.1)
// 13/03/2022 Siyu Liu

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp> //image processing 
#include <pthread.h> // for multithreading

using namespace cv;
using namespace std;


// open camera function
void *open_cam(void*)
{
	VideoCapture cap(0); // read from Webcam
	Mat img; // create Matrix data type variable
	while (true)
	{
		cap.read(img); // read from cam
		resizeWindow("video",640,480);
		imshow("Video",img); //show the images
		waitKey(1); //delay time for showing the picture
	}
}

// open image function
void *open_img(void*)
{
    //Mat srcImage = imread("/home/siyuliu/C++/detect.jpg");
    VideoCapture cap("/home/siyuliu/C++/detect.jpg");
    Mat srcImage;
    cap.read(srcImage);
	imshow("Image",srcImage);
	resizeWindow("Image",700,500);
	waitKey(0);
	pthread_exit(NULL);
}
