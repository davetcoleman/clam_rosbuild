#!/bin/sh
echo "-----------------------------------";
echo "Auto starting CLAM - Correll Lab Arm Manipulator";
echo "Current IP Address:";
ifconfig wlan0 | grep "inet addr" | awk -F: '{print $2}' | awk '{print $1}';
echo "-----------------------------------";
echo "Checking serial connections:";
cd /dev;
find dynamixel_**;
cd /home/share/ros/clam/scripts/;
read -p "Press any key to continue";
roslaunch clam_description clam_description.launch