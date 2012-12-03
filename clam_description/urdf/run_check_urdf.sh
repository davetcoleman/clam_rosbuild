# Convert to urdf and run through URDF verifier
rosrun xacro xacro.py clam_urdf.xacro > clam_urdf_generated.urdf;
rosrun urdf_parser check_urdf clam_urdf_generated.urdf;
