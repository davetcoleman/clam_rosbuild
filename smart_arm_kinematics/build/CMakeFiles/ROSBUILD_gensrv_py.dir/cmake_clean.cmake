FILE(REMOVE_RECURSE
  "../src/smart_arm_kinematics/srv"
  "../srv_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_gensrv_py"
  "../src/smart_arm_kinematics/srv/__init__.py"
  "../src/smart_arm_kinematics/srv/_SmartArmIK.py"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_py.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
