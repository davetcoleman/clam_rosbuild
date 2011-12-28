CLAM Arm Manipulator
==========
* Author: Dave Coleman <davetcoleman@gmail.com>
* Website: correll.cs.colorado.edu
* License: GNU General Public License, version 3 (GPL-3.0)
* Date: 12/27/2011

Controls for the robotic arm in the Correll Lab at the University of Colorado Boulder. Special thanks to Antons Rebguns and his similar work at the University of Arizona.


BUILDING
---------

**1) Download CLAM**

		git clone git@github.com:DaveTColeman/CLAM.git

**2) Install Stack Dependencies**

   Package dynamixel_hardware_interface:

   	   www.ros.org/browse/details.php?name=dynamixel_hardware_interface

   Package control_msgs: 

   	   www.ros.org/wiki/control_msgs

   Package gearbox:

   	   www.ros.org/browse/details.php?name=gearbox

**3) Build the stack**

		rosmake clam

**4) Setup the Dynamixel2USB controllers**

   - Copy the file /setup/50-usb-serial.rules to /etc/udev/rules.d/

   - Disable a conflicting system udev rule if necessary located at /lib/udev/rules.d/95-upower-wup.rules


RUN
---------
		roslaunch clam_description clam_description.launch


TEST
---------
		roscd clam_controller/scripts
		python animate_all.py