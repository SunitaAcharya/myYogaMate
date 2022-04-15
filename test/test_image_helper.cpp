#define BOOST_TEST_MODULE FirstTest
#include "boost/test/included/unit_test.hpp"

#include <string>
#include "../src/image_helper.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#define TEST_FILE_PATH   RESOURCE_DIR

cv::VideoCapture cap;
image_check source_test;

/* Test of source check */
BOOST_AUTO_TEST_SUITE(ImageCheckTest)
BOOST_AUTO_TEST_CASE(Incorrect)
{
  BOOST_CHECK_EQUAL(source_test.source_check(TEST_FILE_PATH "New-demo-video.gif", cap),-1);
}

BOOST_AUTO_TEST_CASE(Correct)
{
  BOOST_CHECK_EQUAL(source_test.source_check(TEST_FILE_PATH "test1.jpg", cap),0);
}
BOOST_AUTO_TEST_SUITE_END()

