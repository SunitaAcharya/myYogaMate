#define BOOST_TEST_MODULE SecondTest
#include "boost/test/included/unit_test.hpp"

#include <memory>
#include <string>
#include <iostream>
#include "../src/image_processor.h"
#include <opencv2/opencv.hpp>

#define TEST_FILE_PATH   RESOURCE_DIR

ImageProcessor_Initialize::InputParam input;
ImageProcessor_Initialize initialize_test;
char WORK_DIR[]=TEST_FILE_PATH "New-demo-video.gif";
ImageProcessor_Finalize finalize_test;
ImageProcessor_Process process_test;
cv::Mat test_mat;

/* Test of initialize */
BOOST_AUTO_TEST_SUITE(ImageProcessorInitialize)
BOOST_AUTO_TEST_CASE(TestWithoutWorkDir)
{
  for(int i=0;i<256;i++)
  {
    input.work_dir[i]='0';
  }
  input.num_threads=0;
  BOOST_CHECK_EQUAL(initialize_test.Initialize(input),-1);
}
BOOST_AUTO_TEST_CASE(TestWithWorkDir)
{
  for(int j=0;j<256;j++)
  {
    input.work_dir[j]='0';
  }
  for(long unsigned int i=0;i<sizeof(WORK_DIR);i++)
  {
    input.work_dir[i]=WORK_DIR[i];
  }
  input.num_threads=0;
  BOOST_CHECK_EQUAL(initialize_test.Initialize(input),-1);
}
BOOST_AUTO_TEST_SUITE_END()

/* Test of finalize */
BOOST_AUTO_TEST_SUITE(ImageProcessorFinalize)
BOOST_AUTO_TEST_CASE(FinalizeTest)
{
  BOOST_CHECK_EQUAL(finalize_test.Finalize(),-1);
}
BOOST_AUTO_TEST_SUITE_END()

/* Test of process */
BOOST_AUTO_TEST_SUITE(ImageProcessorProcess)
BOOST_AUTO_TEST_CASE(ProcessTest)
{
  BOOST_CHECK_EQUAL(process_test.Process(test_mat),-1);
}
BOOST_AUTO_TEST_SUITE_END()
