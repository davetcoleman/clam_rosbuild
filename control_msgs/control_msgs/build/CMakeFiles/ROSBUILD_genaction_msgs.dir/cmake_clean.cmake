FILE(REMOVE_RECURSE
  "../src/control_msgs/msg"
  "../msg_gen"
  "../msg_gen"
  "CMakeFiles/ROSBUILD_genaction_msgs"
  "../msg/FollowJointTrajectoryAction.msg"
  "../msg/FollowJointTrajectoryGoal.msg"
  "../msg/FollowJointTrajectoryActionGoal.msg"
  "../msg/FollowJointTrajectoryResult.msg"
  "../msg/FollowJointTrajectoryActionResult.msg"
  "../msg/FollowJointTrajectoryFeedback.msg"
  "../msg/FollowJointTrajectoryActionFeedback.msg"
  "../msg/PointHeadActionAction.msg"
  "../msg/PointHeadActionGoal.msg"
  "../msg/PointHeadActionActionGoal.msg"
  "../msg/PointHeadActionResult.msg"
  "../msg/PointHeadActionActionResult.msg"
  "../msg/PointHeadActionFeedback.msg"
  "../msg/PointHeadActionActionFeedback.msg"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genaction_msgs.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
