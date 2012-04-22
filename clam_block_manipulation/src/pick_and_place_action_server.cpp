/* 
 * Copyright (c) 2011, Vanadium Labs LLC
 * All Rights Reserved
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Vanadium Labs LLC nor the names of its 
 *       contributors may be used to endorse or promote products derived 
 *       from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL VANADIUM LABS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 * Author: Michael Ferguson, Helen Oleynikova
 */

#include <ros/ros.h>
#include <tf/tf.h>

#include <actionlib/server/simple_action_server.h>
#include <clam_block_manipulation/PickAndPlaceAction.h>

#include <actionlib/client/simple_action_client.h>
//#include <simple_arm_server/MoveArmAction.h>
#include <arm_navigation_msgs/MoveArmAction.h>
#include <arm_navigation_msgs/utils.h> // is this necessary?

#include <geometry_msgs/PoseArray.h>

namespace clam_block_manipulation
{

	class PickAndPlaceServer
	{
	private:
    
		ros::NodeHandle nh_;
		actionlib::SimpleActionServer<clam_block_manipulation::PickAndPlaceAction> as_;
		std::string action_name_;
  
		clam_block_manipulation::PickAndPlaceFeedback     feedback_;
		clam_block_manipulation::PickAndPlaceResult       result_;
		clam_block_manipulation::PickAndPlaceGoalConstPtr goal_;
  
		actionlib::SimpleActionClient<arm_navigation_msgs::MoveArmAction> client_;
  
		ros::Subscriber pick_and_place_sub_;
  
		// Parameters from goal
		std::string arm_link;
		double gripper_open;
		double gripper_closed;
		double z_up;
	public:
		PickAndPlaceServer(const std::string name) : 
			nh_("~"), as_(name, false), action_name_(name), client_("/move_arm", true)
		{
  
			//register the goal and feeback callbacks
			as_.registerGoalCallback(boost::bind(&PickAndPlaceServer::goalCB, this));
			as_.registerPreemptCallback(boost::bind(&PickAndPlaceServer::preemptCB, this));
    
			as_.start();
		}

		void goalCB()
		{
			ROS_INFO("[pick and place] Received goal!");
			goal_ = as_.acceptNewGoal();
			arm_link = goal_->frame;
			gripper_open = goal_->gripper_open;
			gripper_closed = goal_->gripper_closed;
			z_up = goal_->z_up;
    
			if (goal_->topic.length() < 1)
				pickAndPlace(goal_->pickup_pose, goal_->place_pose);
			else
				pick_and_place_sub_ = nh_.subscribe(goal_->topic, 1, &PickAndPlaceServer::sendGoalFromTopic, this);
		}

		void sendGoalFromTopic(const geometry_msgs::PoseArrayConstPtr& msg)
		{
			ROS_INFO("[pick and place] Got goal from topic! %s", goal_->topic.c_str());
			pickAndPlace(msg->poses[0], msg->poses[1]);
			pick_and_place_sub_.shutdown();
		}

		void preemptCB()
		{
			ROS_INFO("%s: Preempted", action_name_.c_str());
			// set the action state to preempted
			as_.setPreempted();
		}
  
		void pickAndPlace(const geometry_msgs::Pose& start_pose, const geometry_msgs::Pose& end_pose)
		{
			ROS_INFO("[pick and place] Picking. Also placing.");

			actionlib::SimpleActionClient<arm_navigation_msgs::MoveArmAction> client2_("move_arm",true);
			ROS_INFO("Waiting for server");			
			client2_.waitForServer();
			ROS_INFO("Connected to server");	
			arm_navigation_msgs::MoveArmGoal goal;
	
			goal.motion_plan_request.group_name = "clam"; // corresponds to clam_planning_description. yaml group name
			goal.motion_plan_request.num_planning_attempts = 1;
			goal.motion_plan_request.planner_id = std::string("");
			goal.planner_service_name = std::string("ompl_planning/plan_kinematic_path");
			goal.motion_plan_request.allowed_planning_time = ros::Duration(50.0);
	
			arm_navigation_msgs::SimplePoseConstraint desired_pose;
			desired_pose.header.frame_id = "base_link";
			desired_pose.link_name = "gripper_roll_link";
    
			/* arm straight up */
			/*btQuaternion temp;
			  temp.setRPY(0,1.57,0);
			  desired_pose.pose.orientation.x = temp.getX();
			  desired_pose.pose.orientation.y = temp.getY();
			  desired_pose.pose.orientation.z = temp.getZ();
			  desired_pose.pose.orientation.w = temp.getW();*/

			// Temp:
			desired_pose.pose.orientation.x = 0.034366;
			desired_pose.pose.orientation.y = 0.72035;
			desired_pose.pose.orientation.z = -0.010556;
			desired_pose.pose.orientation.w = 0.692725;
	
			// Hover Over
			desired_pose.pose.position.x = 0.30; //start_pose.position.x;
			desired_pose.pose.position.y = 0.0; //start_pose.position.y;
			desired_pose.pose.position.z = 0.20; //z_up;
	
			desired_pose.absolute_position_tolerance.x = 0.02;
			desired_pose.absolute_position_tolerance.y = 0.02;
			desired_pose.absolute_position_tolerance.z = 0.02;

			desired_pose.absolute_roll_tolerance = 0.1;
			desired_pose.absolute_pitch_tolerance = 0.1;
			desired_pose.absolute_yaw_tolerance = 0.1;

			arm_navigation_msgs::addGoalConstraintToMoveArmGoal(desired_pose, goal);
	
			/* go down *
			   action.goal.position.z = start_pose.position.z;
			   action.move_time.sec = 1.5;
			   goal.motions.push_back(action);


			   action.goal.orientation.x = temp.getX();
			   action.goal.orientation.y = temp.getY();
			   action.goal.orientation.z = temp.getZ();
			   action.goal.orientation.w = temp.getW();

			   hover over 
			   action.goal.position.x = start_pose.position.x;
			   action.goal.position.y = start_pose.position.y;
			   action.goal.position.z = z_up;
			   action.move_time.sec = 0.25;
			   //goal.motions.push_back(action);

			   close gripper 
			   grip.type = arm_navigation_msgs::ArmAction::MOVE_GRIPPER;
			   grip.command = gripper_closed;
			   grip.move_time.sec = 1.0;
			   goal.motions.push_back(grip); TODO 

			   go up *
			   action.goal.position.z = z_up;
			   action.move_time.sec = 1.0;
			   goal.motions.push_back(action);

			   hover over *
			   action.goal.position.x = end_pose.position.x;
			   action.goal.position.y = end_pose.position.y;
			   action.goal.position.z = z_up;
			   action.move_time.sec = 1.0;
			   goal.motions.push_back(action);

			   go down *
			   action.goal.position.z = end_pose.position.z;
			   action.move_time.sec = 1.5;
			   goal.motions.push_back(action);

			   open gripper *
			   grip.command = gripper_open;
			   goal.motions.push_back(grip);

			   go up *
			   action.goal.position.z = z_up;
			   action.move_time.sec = 1.0;
			   goal.motions.push_back(action);
			*/
	
			//goal.header.frame_id = arm_link;

			if (nh_.ok())
			{
				bool finished_within_time = false;
				client2_.sendGoal(goal);
				finished_within_time = client2_.waitForResult(ros::Duration(200.0));
				if (!finished_within_time)
				{
					client2_.cancelGoal();
					ROS_INFO("Timed out achieving goal");
				}
				else
				{
					actionlib::SimpleClientGoalState state = client2_.getState();
					bool success = (state == actionlib::SimpleClientGoalState::SUCCEEDED);
					if(success)
						ROS_INFO("Action finished: %s",state.toString().c_str());
					else
						ROS_INFO("Action failed: %s",state.toString().c_str());
				}
			}



			/*
			  client_.sendGoal(goal);
			  ROS_INFO("[pick and place] Sent goal. Waiting.");
			  client_.waitForResult(ros::Duration(30.0));
			  ROS_INFO("[pick and place] Received result.");
			  if (client_.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
			  as_.setSucceeded(result_);
			  else
			  {
			  ROS_INFO("Actual state: %s", client_.getState().toString().c_str());
			  as_.setAborted(result_);
			  }*/
		}
	};

};


int main(int argc, char** argv)
{
	ros::init(argc, argv, "pick_and_place_action_server");

	clam_block_manipulation::PickAndPlaceServer server("pick_and_place");
	ros::spin();

	return 0;
}

