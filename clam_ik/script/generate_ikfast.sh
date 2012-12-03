# Generate IKFast module
# Run this script from within clam_ik/scripts

# First create dae file
#. ~/ros/clam/clam_description/urdf/run_convert_to_collada.sh

# Now create IK. Make sure urdf/dae file location path is correct
python /usr/lib/python2.7/dist-packages/openravepy/_openravepy_0_8/ikfast.py --robot=~/ros/clam/clam_description/urdf/clam.dae --iktype=transform6d --baselink=0 --eelink=7 --savefile=output_ikfast61.cpp --freeindex=2

# Compile test program. I had to add the -I part myself, is system dependent probably
cd ../src
g++ -lstdc++ -llapack -o ../bin/test_ikfast ikfastdemo.cpp -lrt -I /usr/lib/python2.7/dist-packages/openravepy/_openravepy_0_8/

# Do a bunch of tests
. ../bin/test_ikfast iktiming 
# Results:
# 12/3/12 joints 0-7, free index 2:   avg time: 3.039000 ms   over 1000000 tests
# Run specific test (this does not seem to work)
. ../bin/test_ikfast ik 0.2222066 -0.0088 .197156 0.703466 0.00 0.710502 -0.01755 0.0

# Create plugin for arm_navigation
mkdir ~/ros/clam/clam_arm_navigation/src
mkdir ~/ros/clam/clam_arm_navigation/include
cp output_ikfast61.cpp ~/ros/clam/clam_arm_navigation/src/clam_clam_arm_ikfast_solver.cpp #<robot_name>_<group_name>_ikfast_solver.cpp

# Make sure arm_kinematics_tools package is installed
#roscd
#svn co http://kaist-ros-pkg.googlecode.com/svn/trunk/arm_kinematics_tools/ arm_kinematics_tools

# ikfast.h unfound??
cp /usr/lib/python2.7/dist-packages/openravepy/_openravepy_0_8/ikfast.h ~/ros/clam/clam_arm_navigation/include/

# Create plugin
rosrun arm_kinematics_tools create_ikfast_plugin.py clam

# Rebuild pkg
rosmake clam_arm_navigation

# Patch arm_kinematics_constraint_aware plugin
cd /opt/ros/fuerte/stacks/arm_navigation/
sudo chown -R dave:dave arm_kinematics_constraint_aware/
cd arm_kinematics_constraint_aware/
sudo wget https://code.ros.org/trac/ros-pkg/raw-attachment/ticket/5586/fk_solver.patch
sudo patch -p1 < fk_solver.patch
rosmake arm_kinematics_constraint_aware

# Switch between using KDL and IKFast
#rosed clam_arm_navigation constraint_aware_kinematics.launch
#<param name="use_plugin_fk" type="bool" value="true" />
#<param name="OLDkinematics_solver" type="string" value="arm_kinematics_constraint_aware/KDLArmKinematicsPlugin"/>