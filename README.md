# myYogaMate
It is a Real time embedded progarmming project called "My Yoga Mate" which will detect human posture doing yoga and compare it with the stored image/video and show the user to correct yoga pose. <br/>
This project is built in C++ code using WebCam for detect the human pose from user and image. We have use openCV and tensorflow to find human keypoints and pose estimation. <br/>

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

<h2 id="contents">Contents</h2>

### To download our project along with submodule
```sh
$ git init 
$ git clone git@github.com:SunitaAcharya/myYogaMate.git  
$ cd myYogaMate/
$ git submodule update --init --recursive --remote
$ sh third_party/download_prebuilt_libraries.sh
```
<br/>

### To Build
```sh
cmake
make
```

### Install
```sh
sudo make install
```

### How to use it
1. Run the above git commands
2. Install cmake,make using sudo
3.


<h2 id="credits">Credits</h2>
 <a href="https://github.com/SunitaAcharya/myYogaMate">Sunita Acharya</a> <br/>
 <a href="https://github.com/YuanZhang2672750">Yuan Zhang</a> <br/>
 <a href="https://github.com/siyu0415">Siyu Liu</a> <br/>
 <a href="https://github.com/qwershu007">Shujun Wang</a> <br/>

<h2 id="referencelinks">Reference Links</h2>
<br/>
To install Ubuntu on Windows 10 for Dual SetUP:https://linuxconfig.org/how-to-install-ubuntu-20-04-alongside-windows-10-dual-boot
<br/>
https://www.youtube.com/watch?v=fiDaAc7z_kQ&list=PLm3gcFKTH-o-GhANAGu93TYwHc6YmVbwE&index=4
<br/>
Human Basic Pose classification :   
https://bleedai.com/introduction-to-pose-detection-and-basic-pose-classification/
<br/>
OpenCv installation Guide :  
http://techawarey.com/programming/install-opencv-c-c-in-ubuntu-18-04-lts-step-by-step-guide/
<br/>
OpenCv  Lib:
https://github.com/opencv/opencv_contrib <br/>
Object Oriented Programming  :
https://www.digitalocean.com/community/conceptual_articles/s-o-l-i-d-the-first-five-principles-of-object-oriented-design <br/>
C++ memory management
https://www.programiz.com/cpp-programming/memory-management <br/>
https://www.mygreatlearning.com/blog/readme-file/ </br>

