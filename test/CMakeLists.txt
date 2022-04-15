find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

include_directories (${TEST_SOURCE_DIR}/../src
                     ${Boost_INCLUDE_DIRS})

set(LibraryName "UNITTEST")
add_library (${LibraryName} test_image_processor.cpp test_image_show.cpp test_image_helper.cpp)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_include_directories(${LibraryName} PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${LibraryName} ${OpenCV_LIBS})

set(INFERENCE_HELPER_DIR ${CMAKE_CURRENT_LIST_DIR}/../InferenceHelper/)
set(INFERENCE_HELPER_ENABLE_TFLITE ON CACHE BOOL "TFLITE")
set(INFERENCE_HELPER_ENABLE_TFLITE_DELEGATE_XNNPACK ON CACHE BOOL "TFLITE_XNNPACK")
target_include_directories(${LibraryName} PUBLIC ${INFERENCE_HELPER_DIR}/inference_helper)
include_directories(${INFERENCE_HELPER_DIR})


add_definitions (-DBOOST_TEST_DYN_LINK)

add_executable (FirstTest test_image_helper.cpp)
target_link_libraries(FirstTest src ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${OpenCV_LIBS} InferenceHelper)
add_executable (SecondTest test_image_processor.cpp)
target_link_libraries(SecondTest src ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${OpenCV_LIBS} InferenceHelper)
add_executable (ThirdTest test_image_show.cpp)
target_link_libraries(ThirdTest src ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${OpenCV_LIBS} InferenceHelper)

add_test(ImageHelperTest FirstTest)
add_test(ImageProcessorTest SecondTest)
add_test(ImageShowTest ThirdTest)

