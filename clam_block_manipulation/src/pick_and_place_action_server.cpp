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
#include <clam_block_manipulation/ClamArmAction.h> // for controlling the gripper
#include <geometry_msgs/PoseArray.h>

namespace clam_block_manipulation
{

class PickAndPlaceServer
{
private:

  ros::NodeHandle nh_;
  std::string action_name_;

  actionlib::SimpleActionClient<arm_navigation_msgs::MoveArmAction> client_;
  actionlib::SimpleActionServer<clam_block_manipulation::PickAndPlaceAction> as_;
  actionlib::SimpleActionClient<ClamArmAction> clam_arm_action_;

  ClamArmGoal clam_arm_goal_; // sent to the clam_arm_action_server
  clam_block_manipulation::PickAndPlaceFeedback     feedback_;
  clam_block_manipulation::PickAndPlaceResult       result_;
  clam_block_manipulation::PickAndPlaceGoalConstPtr goal_;


  ros::Subscriber pick_and_place_sub_;

  // Parameters from goal
  std::string arm_link;
  double gripper_open;
  double gripper_closed;
  double z_up;

public:
  PickAndPlaceServer(const std::string name) :
    nh_("~"), as_(name, false), action_name_(name), 
    client_("move_clam_arm", true),
    clam_arm_action_("clam_arm", true)
  {

    //register the goal and feeback callbacks
    as_.registerGoalCallback(boost::bind(&PickAndPlaceServer::goalCB, this));
    as_.registerPreemptCallback(boost::bind(&PickAndPlaceServer::preemptCB, this));

    as_.start();
  }

  // Recieve Action Goal Function
  void goalCB()
  {
    ROS_INFO("[pick and place] Received goal!");

    goal_ = as_.acceptNewGoal();
    arm_link = goal_->frame;
    gripper_open = goal_->gripper_open;
    gripper_closed = goal_->gripper_closed;
    z_up = goal_->z_up;

    // Check if our listener has recieved a goal from the topic yet
    if (goal_->topic.length() < 1)
      pickAndPlace(goal_->pickup_pose, goal_->place_pose); // yes, start moving arm
    else
      pick_and_place_sub_ = nh_.subscribe(goal_->topic, 1, // no, wait for topic
                                          &PickAndPlaceServer::sendGoalFromTopic, this);
  }

  void sendGoalFromTopic(const geometry_msgs::PoseArrayConstPtr& msg)
  {
    ROS_INFO("[pick and place] Got goal from topic! %s", goal_->topic.c_str());
    pickAndPlace(msg->poses[0], msg->poses[1]);
    pick_and_place_sub_.shutdown();
  }

  // Cancel the action
  void preemptCB()
  {
    ROS_INFO("[%s] Preempted", action_name_.c_str());
    // set the action state to preempted
    as_.setPreempted();
  }

  // Actually run the action
  void pickAndPlace(const geometry_msgs::Pose& start_pose, const geometry_msgs::Pose& end_pose)
  {
    ROS_INFO("[pick and place] Picking and placing.");

    // Wait for MoveArmAction to be ready ----------------------------------------------------------
    ROS_INFO("[pick and place] Waiting for server");
    client_.waitForServer();
    ROS_INFO("[pick and place] Connected to server");

    // Create goal ---------------------------------------------------------------------------------
    arm_navigation_msgs::MoveArmGoal goal;
    goal.motion_plan_request.group_name = "clam_arm"; // corresponds to clam_planning_description.yaml group name
    goal.motion_plan_request.num_planning_attempts = 1;
    goal.motion_plan_request.planner_id = std::string("");
    goal.planner_service_name = std::string("ompl_planning/plan_kinematic_path");
    goal.motion_plan_request.allowed_planning_time = ros::Duration(50.0);

    // Create pose template to be resused ----------------------------------------------------------
    arm_navigation_msgs::SimplePoseConstraint desired_pose;
    desired_pose.header.frame_id = "base_link";
    desired_pose.link_name = "gripper_roll_link";

    desired_pose.absolute_position_tolerance.x = 1; // 0.1
    desired_pose.absolute_position_tolerance.y = 1;
    desired_pose.absolute_position_tolerance.z = 1;

    desired_pose.absolute_roll_tolerance = 1; // 0.1
    desired_pose.absolute_pitch_tolerance = 1;
    desired_pose.absolute_yaw_tolerance = 1;


    // Create Approach------------------------------------------------------------------------------

    // arm straight up
    tf::Quaternion temp;
    temp.setRPY(0,1.57,0);
    desired_pose.pose.orientation.x = temp.getX();
    desired_pose.pose.orientation.y = temp.getY();
    desired_pose.pose.orientation.z = temp.getZ();
    desired_pose.pose.orientation.w = temp.getW();
    ROS_INFO_STREAM("Pose orientation: " << desired_pose.pose.orientation.x << "\t" << desired_pose.pose.orientation.y << "\t"  << desired_pose.pose.orientation.z << "\t"  << desired_pose.pose.orientation.w );

    // hover over
    desired_pose.pose.position.x = start_pose.position.x;
    desired_pose.pose.position.y = start_pose.position.y;
    desired_pose.pose.position.z = 0.2; // z_up;

    ROS_INFO_STREAM("Pose position: " << desired_pose.pose.position.x << "\t" << desired_pose.pose.position.y << "\t"  << desired_pose.pose.position.z );

    // Send command
    arm_navigation_msgs::addGoalConstraintToMoveArmGoal(desired_pose, goal);
    client_.sendGoal(goal);
    bool finished_within_time = client_.waitForResult(ros::Duration(200.0));
    if (!finished_within_time)
    {
      client_.cancelGoal();
      ROS_INFO("Timed out achieving goal");
      as_.setAborted(result_);
      return;
    }
    else
    {
      actionlib::SimpleClientGoalState state = client_.getState();
      if(state == actionlib::SimpleClientGoalState::SUCCEEDED)
      {
        ROS_INFO("Action 1 finished: %s",state.toString().c_str());
      }
      else
      {
        ROS_INFO("Action 1 failed: %s",state.toString().c_str());
        as_.setAborted(result_);
        return;
      }
    }

    // Close gripper -------------------------------------------------------------------------------

    clam_arm_goal_.command = "CLOSE_GRIPPER";
    clam_arm_action_.sendGoal(clam_arm_goal_);
    while(!clam_arm_action_.getState().isDone() && ros::ok())
    {
      ROS_INFO("Waiting for gripper to close");
      ros::Duration(0.5).sleep();
    }

    // Move Arm to new location --------------------------------------------------------------------

    // arm straight up
    tf::Quaternion temp2;
    temp2.setRPY(0,1.57,0);
    desired_pose.pose.orientation.x = temp2.getX();
    desired_pose.pose.orientation.y = temp2.getY();
    desired_pose.pose.orientation.z = temp2.getZ();
    desired_pose.pose.orientation.w = temp2.getW();

    ROS_INFO_STREAM("Pose orientation: " << desired_pose.pose.orientation.x << "\t" << desired_pose.pose.orientation.y << "\t"  << desired_pose.pose.orientation.z << "\t"  << desired_pose.pose.orientation.w );

    // hover over
    desired_pose.pose.position.x = end_pose.position.x;
    desired_pose.pose.position.y = end_pose.position.y;
    desired_pose.pose.position.z = 0.2; // z_up;

    ROS_INFO_STREAM("Pose position: " << desired_pose.pose.position.x << "\t" << desired_pose.pose.position.y << "\t"  << desired_pose.pose.position.z );

    // Send command
    arm_navigation_msgs::addGoalConstraintToMoveArmGoal(desired_pose, goal);
    client_.sendGoal(goal);
    finished_within_time = client_.waitForResult(ros::Duration(200.0));
    if (!finished_within_time)
    {
      client_.cancelGoal();
      ROS_INFO("Timed out achieving goal");
      as_.setAborted(result_);
      return;
    }
    else
    {
      actionlib::SimpleClientGoalState state = client_.getState();
      if(state == actionlib::SimpleClientGoalState::SUCCEEDED)
      {
        ROS_INFO("Action 1 finished: %s",state.toString().c_str());
      }
      else
      {
        ROS_INFO("Action 1 failed: %s",state.toString().c_str());
        as_.setAborted(result_);
        return;
      }
    }

    // Open gripper -------------------------------------------------------------------------------

    clam_arm_goal_.command = "OPEN_GRIPPER";
    clam_arm_action_.sendGoal(clam_arm_goal_);
    while(!clam_arm_action_.getState().isDone() && ros::ok())
    {
      ROS_INFO("Waiting for gripper to open");
      ros::Duration(0.5).sleep();
    }


    // Done ---------------------------------------------------------------------------------------
    // Demo will automatically reset arm
    
    as_.setSucceeded(result_);    
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

