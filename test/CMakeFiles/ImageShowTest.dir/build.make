# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/shujun/Downloads/1_1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/shujun/Downloads/1_1

# Include any dependencies generated for this target.
include test/CMakeFiles/ImageShowTest.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/ImageShowTest.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/ImageShowTest.dir/flags.make

test/CMakeFiles/ImageShowTest.dir/test_image_show.cpp.o: test/CMakeFiles/ImageShowTest.dir/flags.make
test/CMakeFiles/ImageShowTest.dir/test_image_show.cpp.o: test/test_image_show.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/shujun/Downloads/1_1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/ImageShowTest.dir/test_image_show.cpp.o"
	cd /home/shujun/Downloads/1_1/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ImageShowTest.dir/test_image_show.cpp.o -c /home/shujun/Downloads/1_1/test/test_image_show.cpp

test/CMakeFiles/ImageShowTest.dir/test_image_show.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ImageShowTest.dir/test_image_show.cpp.i"
	cd /home/shujun/Downloads/1_1/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/shujun/Downloads/1_1/test/test_image_show.cpp > CMakeFiles/ImageShowTest.dir/test_image_show.cpp.i

test/CMakeFiles/ImageShowTest.dir/test_image_show.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ImageShowTest.dir/test_image_show.cpp.s"
	cd /home/shujun/Downloads/1_1/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/shujun/Downloads/1_1/test/test_image_show.cpp -o CMakeFiles/ImageShowTest.dir/test_image_show.cpp.s

# Object files for target ImageShowTest
ImageShowTest_OBJECTS = \
"CMakeFiles/ImageShowTest.dir/test_image_show.cpp.o"

# External object files for target ImageShowTest
ImageShowTest_EXTERNAL_OBJECTS =

test/ImageShowTest: test/CMakeFiles/ImageShowTest.dir/test_image_show.cpp.o
test/ImageShowTest: test/CMakeFiles/ImageShowTest.dir/build.make
test/ImageShowTest: src/libsrc.a
test/ImageShowTest: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.71.0
test/ImageShowTest: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.71.0
test/ImageShowTest: /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so.1.71.0
test/ImageShowTest: src/common_helper/libCommonHelper.a
test/ImageShowTest: /usr/local/lib/libopencv_gapi.so.4.5.5
test/ImageShowTest: /usr/local/lib/libopencv_highgui.so.4.5.5
test/ImageShowTest: /usr/local/lib/libopencv_ml.so.4.5.5
test/ImageShowTest: /usr/local/lib/libopencv_objdetect.so.4.5.5
test/ImageShowTest: /usr/local/lib/libopencv_photo.so.4.5.5
test/ImageShowTest: /usr/local/lib/libopencv_stitching.so.4.5.5
test/ImageShowTest: /usr/local/lib/libopencv_video.so.4.5.5
test/ImageShowTest: /usr/local/lib/libopencv_calib3d.so.4.5.5
test/ImageShowTest: /usr/local/lib/libopencv_dnn.so.4.5.5
test/ImageShowTest: /usr/local/lib/libopencv_features2d.so.4.5.5
test/ImageShowTest: /usr/local/lib/libopencv_flann.so.4.5.5
test/ImageShowTest: /usr/local/lib/libopencv_videoio.so.4.5.5
test/ImageShowTest: /usr/local/lib/libopencv_imgcodecs.so.4.5.5
test/ImageShowTest: /usr/local/lib/libopencv_imgproc.so.4.5.5
test/ImageShowTest: /usr/local/lib/libopencv_core.so.4.5.5
test/ImageShowTest: src/inference_helper/libInferenceHelper.a
test/ImageShowTest: InferenceHelper/third_party/cmakes/../tflite_prebuilt/ubuntu/libtensorflowlite.so
test/ImageShowTest: test/CMakeFiles/ImageShowTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/shujun/Downloads/1_1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ImageShowTest"
	cd /home/shujun/Downloads/1_1/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ImageShowTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/ImageShowTest.dir/build: test/ImageShowTest

.PHONY : test/CMakeFiles/ImageShowTest.dir/build

test/CMakeFiles/ImageShowTest.dir/clean:
	cd /home/shujun/Downloads/1_1/test && $(CMAKE_COMMAND) -P CMakeFiles/ImageShowTest.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/ImageShowTest.dir/clean

test/CMakeFiles/ImageShowTest.dir/depend:
	cd /home/shujun/Downloads/1_1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/shujun/Downloads/1_1 /home/shujun/Downloads/1_1/test /home/shujun/Downloads/1_1 /home/shujun/Downloads/1_1/test /home/shujun/Downloads/1_1/test/CMakeFiles/ImageShowTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/ImageShowTest.dir/depend
