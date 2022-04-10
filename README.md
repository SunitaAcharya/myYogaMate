# myYogaMate
<br/>
<p align="center">
<img src="https://github.com/SunitaAcharya/myYogaMate/blob/main/image/logo.png" width="400" height="350">
  </p>
<br/>

<h2 id="status">Status</h2>
<p><a href="LICENSE"><img src="https://img.shields.io/badge/License-MIT-yellow.svg" alt="License" /></a>
<img src="https://img.shields.io/github/stars/SunitaAcharya/myYogaMate.svg?style=flat&amp;label=Star&amp;maxAge=86400" alt="Stars" />
<a href="https://github.com/SunitaAcharya/myYogaMate/issues"><img src="https://img.shields.io/github/issues-raw/SunitaAcharya/myYogaMate.svg" alt="GitHub open issues" /></a> 
<a href="https://github.com/SunitaAcharya/myYogaMate/pulls"><img src="https://img.shields.io/github/issues-pr-raw/SunitaAcharya/myYogaMate.svg" alt="GitHub open pull requests" /></a> <img src="https://img.shields.io/github/repo-size/SunitaAcharya/myYogaMate.svg?label=Repo%20size&amp;style=flat-square" alt="" /> 
<img src="https://img.shields.io/github/contributors/SunitaAcharya/myYogaMate.svg?style=flat&amp;label=Contributors&amp;maxAge=86400" alt="Contributors" />
</p>

### Table of contents


* [About the project](#about-the-project)
* [Requirements](#requirements)
* [Guide](#guide)
* [License](#license)
* [Authors](#authors)
* [References](#references)

### About the Project
My Yoga Mate - MYM , is a project built by postgraduate students of University of Glasgow. MYM detects human posture doing yoga and compares it with the stored original image and state the user whether the pose is correct or not. We have build this project in C++ language and used Tensorflow libaries to find the key points of hunan pose estimation. This will be a great use for people who do yoga on a daily basis where they can get a guidance for correct posture of a human doing a particular yoag pose. We can extend our project and make an app for this so that it will be easy and convinient foreveryone to use it daily.

### Requirements
Hardware 
* Linux Laptop/ Ubuntu dual setup in Windows Laptop
* Webcam

Software
* Ubuntu(x64)
* C++ API
* Visual Studio(2019)

Install<br/>
```sh
sudo make install
```
To download our source code along with submodule<br/>
```sh
$ git init 
$ git clone git@github.com:SunitaAcharya/myYogaMate.git  
$ cd myYogaMate/
$ git submodule update --init --recursive --remote
```
To download pre-build libararies
```sh
$ sh third_party/download_prebuilt_libraries.sh
```
<br/>

To Build<br/>
```sh
mkdir build
cd build
cmake ..
make    #to compile program
./main 
```



### Guide
1. Run the above commands to download our siurce code and build it
2. Press any key to start the program
3. Select 1,2 ,3,4,5,6 to select image
4. Press q to exit


### License
Copyright 2022 UofG_rtep_team4<br/>
Licensed under the MIT License<br/>
Please visit <a href="https://github.com/SunitaAcharya/myYogaMate/blob/main/LICENSE">License </a>  for more details.<br/>

### Authors
 <a href="https://github.com/SunitaAcharya/myYogaMate">Sunita Acharya</a> <br/>
 <a href="https://github.com/YuanZhang2672750">Yuan Zhang</a> <br/>
 <a href="https://github.com/siyu0415">Siyu Liu</a> <br/>
 <a href="https://github.com/qwershu007">Shujun Wang</a> <br/>

### References
<a href="https://linuxconfig.org/how-to-install-ubuntu-20-04-alongside-windows-10-dual-boot">To install Ubuntu on Windows 10 for Dual SetUP </a></br> 
<a href="https://bleedai.com/introduction-to-pose-detection-and-basic-pose-classification/">Human Basic Pose classification </a> </br>
<a href="http://techawarey.com/programming/install-opencv-c-c-in-ubuntu-18-04-lts-step-by-step-guide/">OpenCv installation Guide </a></br> 
<a href="https://github.com/opencv/opencv_contrib">OpenCv  Lib </a> </br>
<a href="https://www.digitalocean.com/community/conceptual_articles/s-o-l-i-d-the-first-five-principles-of-object-oriented-design ">Object Oriented Programming </a> </br>
<a href="https://www.programiz.com/cpp-programming/memory-management">C++ memory management </a> </br>
<a href="https://github.com/iwatake2222/InferenceHelper">InferenceHelper </a> </br>
<a href="https://www.mygreatlearning.com/blog/readme-file/">How to use README File </a> </br>
https://www.youtube.com/watch?v=fiDaAc7z_kQ&list=PLm3gcFKTH-o-GhANAGu93TYwHc6YmVbwE&index=4 </br>


 </br> </br>
&copy; 2022 Copyright UofG_rtep_team4
