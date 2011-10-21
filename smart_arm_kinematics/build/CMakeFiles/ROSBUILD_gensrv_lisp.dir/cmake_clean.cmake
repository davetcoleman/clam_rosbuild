FILE(REMOVE_RECURSE
  "../src/smart_arm_kinematics/srv"
  "../srv_gen"
  "../srv_gen"
  "CMakeFiles/ROSBUILD_gensrv_lisp"
  "../srv_gen/lisp/SmartArmIK.lisp"
  "../srv_gen/lisp/_package.lisp"
  "../srv_gen/lisp/_package_SmartArmIK.lisp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_gensrv_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
