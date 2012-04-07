ClamArm Manipulator
==========
* Author: Dave Coleman <davetcoleman.com>
* Website: correll.cs.colorado.edu/clam
* License: GNU General Public License, version 3 (GPL-3.0)
* Inception Date: 12/27/2011

Controls for the 7-dof robotic arm in the Correll Lab at the University of Colorado Boulder. 


BUILDING
---------

**1) Download CLAM**

		git clone git@github.com:davetcoleman/clam.git

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
		roslaunch clam_bringup clam.launch
		roslaunch clam_bringup clam_interactive_markers.launch


TEST
---------
		roscd clam_controller/scripts
		python pose_cobra.py

CONTRIBUTORS
---------
Andy McEvoy - CU Boulder
Antons Rebguns - University of Arizona