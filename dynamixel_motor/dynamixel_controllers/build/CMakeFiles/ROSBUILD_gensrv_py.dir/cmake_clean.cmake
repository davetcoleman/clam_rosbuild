FILE(REMOVE_RECURSE
  "../src/dynamixel_controllers/srv"
  "../srv_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_gensrv_py"
  "../src/dynamixel_controllers/srv/__init__.py"
  "../src/dynamixel_controllers/srv/_SetCompliancePunch.py"
  "../src/dynamixel_controllers/srv/_SetSpeed.py"
  "../src/dynamixel_controllers/srv/_StopController.py"
  "../src/dynamixel_controllers/srv/_TorqueEnable.py"
  "../src/dynamixel_controllers/srv/_StartController.py"
  "../src/dynamixel_controllers/srv/_RestartController.py"
  "../src/dynamixel_controllers/srv/_SetComplianceMargin.py"
  "../src/dynamixel_controllers/srv/_SetComplianceSlope.py"
  "../src/dynamixel_controllers/srv/_SetTorqueLimit.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
