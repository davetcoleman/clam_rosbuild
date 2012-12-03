# Convert xarco to URDF
rosrun xacro xacro.py clam_urdf.xacro > clam_urdf_generated.urdf;
roslaunch clam_bringup clam_simulation.launch;
