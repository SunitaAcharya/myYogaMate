#define BOOST_TEST_MODULE ThirdTest
#include "boost/test/included/unit_test.hpp"

#include "../src/image_show.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#define TEST_FILE_PATH   RESOURCE_DIR

image_show img_process_test;
camera_show cam_process_test; 

/* Test of img process */
BOOST_AUTO_TEST_SUITE(ImageShowTest)
BOOST_AUTO_TEST_CASE(CorrectPathTest)
{
  BOOST_CHECK_EQUAL(img_process_test.img_process(TEST_FILE_PATH "/test1.jpg"),0);
}
BOOST_AUTO_TEST_CASE(IncorrectPathTest)
{
  BOOST_CHECK_EQUAL(img_process_test.img_process(TEST_FILE_PATH "/New-demo-video.gif"),0);
}
BOOST_AUTO_TEST_SUITE_END()

/* Test of cam process */
BOOST_AUTO_TEST_SUITE(camera_showTest)
BOOST_AUTO_TEST_CASE(Incorrectcam_id)
{
  //BOOST_CHECK_EQUAL(cam_process_test.cam_process("-1"),0);
}
BOOST_AUTO_TEST_CASE(Correctcam_id)
{
  BOOST_CHECK_EQUAL(cam_process_test.cam_process("0"),-1);
  cv::destroyAllWindows();
}
BOOST_AUTO_TEST_SUITE_END()

