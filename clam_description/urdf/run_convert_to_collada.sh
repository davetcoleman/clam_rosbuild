# Convert URDF to collada format
rosrun collada_urdf urdf_to_collada clam.urdf clam.generated.dae
# Install openrave here: http://openrave.org/docs/latest_stable/install/#install
openrave clam.generated.dae
