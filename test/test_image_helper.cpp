#define BOOST_TEST_MODULE FirstTest
#include "boost/test/included/unit_test.hpp"

#include <string>
#include "../src/image_helper.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

cv::VideoCapture cap;
image_check source_test;

/* Test of source check */
BOOST_AUTO_TEST_SUITE(ImageCheckTest)
BOOST_AUTO_TEST_CASE(Incorrect)
{
  BOOST_CHECK_EQUAL(source_test.source_check("/home/shujun/Downloads/YoagProject/test/New-demo-video.gif", cap),-1);
}

BOOST_AUTO_TEST_CASE(Correct)
{
  BOOST_CHECK_EQUAL(source_test.source_check("/home/shujun/Downloads/YoagProject/test/test1.jpg", cap),0);
}
BOOST_AUTO_TEST_SUITE_END()

