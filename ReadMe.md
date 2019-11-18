# Week12_HW
[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)

---
## Overview
This project use Gazebo and ros to navigation robot to empty space.

After cloned the repository, go to results folder and unzip output.bag.zip file in results folder.


## Required packages:
c++ 11
ros-kinetic
gazebo
nodelet
laser_filters
turtlebot
turtlebot_simulator


## Build Instructions
```
cd ~
mkdir catkin_ws
cd catkin_ws
mkdir src
cd src
git clone https://github.com/jingCGM/week12.git
cd week12
git checkout Week12_HW
cd ../../
catkin_make
echo "source ~/catkin_ws/devel/setup.bash" >> ~/.bashrc
```

## Run launch files:
Launch file brings up designed gazebo environment and also Navigation node. If customer wants to record a rosbag in 15s, then use ifRecord parameter:

Run files without recording:
```
	roslaunch week12 week12.launch ifRecord:=false
```

Run files with recording:
```
	roslaunch week12 week12.launch ifRecord:=true
```


## Play rosbag:
Following instructions bring up gazebo simulator and play rosbag

In one terminal:
```
	roslaunch week12 base.launch
```
In another terminal:
```
	roscd week12
	rosbag play ./results/output.bag
```

## Notes:
I wrote lidar sensor for turtlebot so launch file uses my self-defined model of turtlebot
