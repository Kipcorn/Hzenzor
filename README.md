# Hzenzor

## Project Description
The Hzenzor is a sustainable solution to implement autonomy in the waterways in the Oosterschelde, Netherlands.
THe purpose of the Hzenzor is to measure the water quality of the water as a result of Rijkswaterstaat raising the sand level. 

This application is the software of the autonomous boat. It uses the autopilot system of Ardupilot in conjunction with the middleware ROS noetic.
The use of these technologies was determined by an research group before the application was determined. The current design is
able to connect to a virtual board computer where it can simulate in a vehicle in a 3d enviroment with a GCS (Ground control station).

The challenges this project will face is the actual implementation of Autonomy was this application is only be able to drive on waypoints.
But it also needs other input aswell as camera detection in conjunction with a LIDAR system.

# Table of contents

## Getting started

### Installing Ubuntu

Install image
https://releases.ubuntu.com/20.04/

Installation Guide
https://ubuntu.com/tutorials/install-ubuntu-desktop#1-overview

### Installing software

#### Git
https://www.atlassian.com/git/tutorials/install-git#linux

#### ROS
Use the full install. This will also download the required 3d simulation software<br>
http://wiki.ros.org/noetic/Installation/Ubuntu

#### Mavros
https://docs.px4.io/v1.12/en/ros/mavros_installation.html

Replace kinetic from `sudo apt-get install ros-kinetic-mavros ros-kinetic-mavros-extras` with noetic.

#### Ardupilot
https://ardupilot.org/dev/docs/building-setup-linux.html

#### GCS (QGroundControl)
https://docs.qgroundcontrol.com/master/en/getting_started/download_and_install.html#ubuntu

#### Arduino
https://docs.arduino.cc/software/ide-v1/tutorials/Linux

## Prerequisites
1. Understanding of the Linux terminal
2. Understanding of the ROS middleware see: http://wiki.ros.org/ROS/Tutorials beginner tutorials are highly reccomended.

## Setting up the project

### Ardupilot
https://github.com/ArduPilot/ardupilot/blob/master/BUILD.md
`./waf configure --board sitl`
`./waf rover`

https://ardupilot.org/dev/docs/using-sitl-for-ardupilot-testing.html
`sim_vehicle.py -v Rover --console` to start the Ardupilot system

### ROS





## How to use the project

# Credits

# Licensing
MIT
