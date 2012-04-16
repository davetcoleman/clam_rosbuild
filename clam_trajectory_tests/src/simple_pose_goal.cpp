#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>

#include <arm_navigation_msgs/MoveArmAction.h>
#include <arm_navigation_msgs/utils.h>

int main(int argc, char **argv){
	ros::init (argc, argv, "simple_pose_goal"); // name is aribitrary
	ros::NodeHandle nh;
	actionlib::SimpleActionClient<arm_navigation_msgs::MoveArmAction> move_arm("move_clam",true);
	   // before: "move_clam_chain
	   // name corresponds with /clam_move_clam_chain node
	
	ROS_INFO("Waiting for server");
	move_arm.waitForServer();
	ROS_INFO("Connected to server");
	arm_navigation_msgs::MoveArmGoal goalA;

	goalA.motion_plan_request.group_name = "clam"; // corresponds to clam_planning_description.yaml group name
	goalA.motion_plan_request.num_planning_attempts = 1;
	goalA.motion_plan_request.planner_id = std::string("");
	goalA.planner_service_name = std::string("ompl_planning/plan_kinematic_path");
	goalA.motion_plan_request.allowed_planning_time = ros::Duration(50.0);

	arm_navigation_msgs::SimplePoseConstraint desired_pose;
	desired_pose.header.frame_id = "base_link";
	desired_pose.link_name = "gripper_roll_link"; //"gripper_roll_link";

	// the following are in m units, so 40cm = .40 m
	desired_pose.pose.position.x = 0.30;  // positive is straight towards estop buttons
	desired_pose.pose.position.y = 0.0;  // positive is right on plywood
	desired_pose.pose.position.z = 0.20;     // up

	desired_pose.pose.orientation.x = 0;
	desired_pose.pose.orientation.y = 0; //.5*3.14;
	desired_pose.pose.orientation.z = 0;
	desired_pose.pose.orientation.w = 1;

	desired_pose.absolute_position_tolerance.x = 0.02;
	desired_pose.absolute_position_tolerance.y = 0.02;
	desired_pose.absolute_position_tolerance.z = 0.02;

	desired_pose.absolute_roll_tolerance = 0.1;
	desired_pose.absolute_pitch_tolerance = 0.1;
	desired_pose.absolute_yaw_tolerance = 0.1;

	arm_navigation_msgs::addGoalConstraintToMoveArmGoal(desired_pose,goalA);

	if (nh.ok())
	{
		bool finished_within_time = false;
		move_arm.sendGoal(goalA);
		finished_within_time = move_arm.waitForResult(ros::Duration(200.0));
		if (!finished_within_time)
		{
			move_arm.cancelGoal();
			ROS_INFO("Timed out achieving goal A");
		}
		else
		{
			actionlib::SimpleClientGoalState state = move_arm.getState();
			bool success = (state == actionlib::SimpleClientGoalState::SUCCEEDED);
			if(success)
				ROS_INFO("Action finished: %s",state.toString().c_str());
			else
				ROS_INFO("Action failed: %s",state.toString().c_str());
		}
	}
	ros::shutdown();
}
