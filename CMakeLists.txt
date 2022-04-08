
cmake_minimum_required(VERSION 3.0)

# Create project
set(ProjectName "main")
project(${ProjectName})

# Select build system and set compile options
include(${CMAKE_CURRENT_LIST_DIR}/common_helper/cmakes/build_setting.cmake)

# Create executable file
add_executable(${ProjectName} main.cpp)

# Link ImageProcessor module
add_subdirectory(./src src)
target_include_directories(${ProjectName} PUBLIC ./src)
target_link_libraries(${ProjectName} src)


# For OpenCV
find_package(OpenCV REQUIRED)
target_include_directories(${ProjectName} PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${ProjectName} ${OpenCV_LIBS})

# Copy resouce
file(COPY ${CMAKE_CURRENT_LIST_DIR}/resource DESTINATION ${CMAKE_BINARY_DIR}/)
add_definitions(-DRESOURCE_DIR="${CMAKE_BINARY_DIR}/resource/")

#add_subdirectory (test)
#enable_testing ()
#add_test (NAME MyTest COMMAND Test)
