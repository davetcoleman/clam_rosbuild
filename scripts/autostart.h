#!/bin/sh
echo "-----------------------------------";
echo "Auto starting CLAM - Correll Lab Arm Manipulator";
echo "Current IP Address:";
ifconfig wlan0 | grep "inet addr" | awk -F: '{print $2}' | awk '{print $1}';
echo "-----------------------------------";
echo "Checking serial connections:";
cd /dev;
find dynamixel_**;
cd ~/ros/clam2/scripts/;
read -p "Press any key to continue";
roslaunch smart_arm_controller smart_arm.launch;