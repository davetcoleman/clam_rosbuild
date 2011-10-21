FILE(REMOVE_RECURSE
  "../src/dynamixel_controllers/srv"
  "../srv_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_gensrv_cpp"
  "../srv_gen/cpp/include/dynamixel_controllers/SetCompliancePunch.h"
  "../srv_gen/cpp/include/dynamixel_controllers/SetSpeed.h"
  "../srv_gen/cpp/include/dynamixel_controllers/StopController.h"
  "../srv_gen/cpp/include/dynamixel_controllers/TorqueEnable.h"
  "../srv_gen/cpp/include/dynamixel_controllers/StartController.h"
  "../srv_gen/cpp/include/dynamixel_controllers/RestartController.h"
  "../srv_gen/cpp/include/dynamixel_controllers/SetComplianceMargin.h"
  "../srv_gen/cpp/include/dynamixel_controllers/SetComplianceSlope.h"
  "../srv_gen/cpp/include/dynamixel_controllers/SetTorqueLimit.h"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_cpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
