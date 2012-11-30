/*
 * Copyright (c) 2012, CU Boulder
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
 * Author: Dave Coleman
 */

/*
  Allows you to reset the arm to its default pose, as well as open and close the gripper
*/

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <actionlib/client/simple_action_client.h>
#include <clam_block_manipulation/ClamArmAction.h>
#include <control_msgs/FollowJointTrajectoryAction.h>
#include <std_msgs/Float64.h>

namespace clam_block_manipulation
{

typedef actionlib::SimpleActionClient< control_msgs::FollowJointTrajectoryAction > TrajClient;

class ClamArmServer
{
private:
  ros::NodeHandle nh_;

  actionlib::SimpleActionServer<clam_block_manipulation::ClamArmAction> as_;

  std::string action_name_;

  clam_block_manipulation::ClamArmFeedback     feedback_;
  clam_block_manipulation::ClamArmResult       result_;
  clam_block_manipulation::ClamArmGoalConstPtr goal_;

  ros::Publisher joint_pub_; // publish joint values to servos

  // Constants that define the limits of the gripper
  static const float GRIPPER_OPEN_VALUE = -1.0;
  static const float GRIPPER_CLOSE_VALUE = -0.1;

  // Action client for the joint trajectory action used to trigger the arm movement action
  TrajClient* trajectory_client_;

public:
  ClamArmServer(const std::string name) :
    nh_("~"), as_(name, false), action_name_(name)
  {

    trajectory_client_ = new TrajClient("clam_arm_controller/follow_joint_trajectory", true);

    // wait for action server to come up
    while(!trajectory_client_->waitForServer(ros::Duration(5.0))){
      ROS_INFO("Waiting for the joint_trajectory_action server");
    }

    //register the goal and feeback callbacks
    as_.registerGoalCallback(boost::bind(&ClamArmServer::goalCB, this));
    as_.registerPreemptCallback(boost::bind(&ClamArmServer::preemptCB, this));

    as_.start();

    // Create publisher for gripper servo position
    joint_pub_ = nh_.advertise< std_msgs::Float64 >("/l_gripper_aft_controller/command", 1, true);
  }

  // Recieve Action Goal Function
  void goalCB()
  {
    ROS_INFO("[clam arm] Received goal!");

    goal_ = as_.acceptNewGoal();

    if( goal_->command == "RESET")
    {
      resetArm();
    }
    else if( goal_->command == "OPEN_GRIPPER" )
    {
      openGripper(true);
    }
    else if( goal_->command == "CLOSE_GRIPPER" )
    {
      openGripper(false);
    }
    else
    {
      ROS_ERROR_STREAM("Unknown command to clam_arm_action_server: " << goal_->command);
    }
  }

  // Cancel the action
  void preemptCB()
  {
    ROS_INFO("[%s] Preempted", action_name_.c_str());
    // set the action state to preempted
    as_.setPreempted();
  }

  //! Generates a simple trajectory with two waypoints, used as an example
  /*! Note that this trajectory contains two waypoints, joined together
    as a single trajectory. Alternatively, each of these waypoints could
    be in its own trajectory - a trajectory can have one or more waypoints
    depending on the desired application.
  */
  control_msgs::FollowJointTrajectoryGoal resetTrajectory()
  {
    ROS_INFO("Creating trajectory");

    //our goal variable
    control_msgs::FollowJointTrajectoryGoal goal;

    // First, the joint names, which apply to all waypoints
    goal.trajectory.joint_names.push_back("shoulder_pan_joint");
    goal.trajectory.joint_names.push_back("shoulder_pitch_joint");
    goal.trajectory.joint_names.push_back("elbow_roll_joint");
    goal.trajectory.joint_names.push_back("elbow_pitch_joint");
    goal.trajectory.joint_names.push_back("wrist_roll_joint");
    goal.trajectory.joint_names.push_back("wrist_pitch_joint");
    goal.trajectory.joint_names.push_back("gripper_roll_joint");
    //    goal.trajectory.joint_names.push_back("l_gripper_aft_joint");

    // We will have two waypoints in this goal trajectory
    goal.trajectory.points.resize(1);
    unsigned int num_joints = 7;

    // First trajectory point
    // Positions
    int ind = 0;
    goal.trajectory.points[ind].positions.resize(num_joints);
    goal.trajectory.points[ind].positions[0] = 0.0;
    goal.trajectory.points[ind].positions[1] = 0.0;
    goal.trajectory.points[ind].positions[2] = 0.0;
    goal.trajectory.points[ind].positions[3] = 0.0;
    goal.trajectory.points[ind].positions[4] = 0.0;
    goal.trajectory.points[ind].positions[5] = 1.5;
    goal.trajectory.points[ind].positions[6] = 0.0;
    //goal.trajectory.points[ind].positions[7] = 0.0;

    // Velocities
    goal.trajectory.points[ind].velocities.resize(num_joints);
    for (size_t j = 0; j < num_joints; ++j)
    {
      goal.trajectory.points[ind].velocities[j] = 2.0;
    }
    // To be reached 1 second after starting along the trajectory
    goal.trajectory.points[ind].time_from_start = ros::Duration(4.0);

    //we are done; return the goal
    ROS_INFO("FINISHED CREATING GOAL");
    return goal;
  }

  //! Returns the current state of the action
  actionlib::SimpleClientGoalState getState()
  {
    return trajectory_client_->getState();
  }

  // Actually run the action
  void resetArm()
  {
    control_msgs::FollowJointTrajectoryGoal goal = resetTrajectory();

    ROS_INFO("Starting trajectory");

    // When to start the trajectory: 1s from now
    goal.trajectory.header.stamp = ros::Time::now() + ros::Duration(1.0);
    trajectory_client_->sendGoal(goal);

    // Wait for trajectory completion
    while(!getState().isDone() && ros::ok())
    {
      ros::Duration(0.5).sleep();
    }

    as_.setSucceeded(result_);
  }

  // Open or close gripper
  void openGripper( bool open )
  {
    /*
  static const float GRIPPER_OPEN_VALUE = -1.0;
  static const float GRIPPER_CLOSE_VALUE = -0.1;
    */
    // Publish command to servos
    if(open)
    {
      //      joint_pub_.publish(-1.0);
    }
    else
    {
      //      joint_pub_.publish(-0.1);
    }

    // Just a guess on how long to wait
    ros::Duration(2).sleep();

    // Assume it works TODO don't assume?
    as_.setSucceeded(result_);
  }
};

};


int main(int argc, char** argv)
{
  ros::init(argc, argv, "clam_arm_action_server");

  clam_block_manipulation::ClamArmServer server("clam_arm");
  ros::spin();

  return 0;
}

