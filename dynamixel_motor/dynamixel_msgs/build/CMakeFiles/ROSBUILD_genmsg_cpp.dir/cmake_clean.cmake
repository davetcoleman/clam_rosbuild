FILE(REMOVE_RECURSE
  "../src/dynamixel_msgs/msg"
  "../msg_gen"
  "../msg_gen"
  "CMakeFiles/ROSBUILD_genmsg_cpp"
  "../msg_gen/cpp/include/dynamixel_msgs/JointStateList.h"
  "../msg_gen/cpp/include/dynamixel_msgs/MotorState.h"
  "../msg_gen/cpp/include/dynamixel_msgs/MotorStateList.h"
  "../msg_gen/cpp/include/dynamixel_msgs/JointState.h"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_cpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
