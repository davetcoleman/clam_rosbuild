rosrun xacro xacro.py clam_urdf.xarco > clam_urdf_generated.xml;
rosrun urdf_parser check_urdf clam_urdf_generated.xml;
