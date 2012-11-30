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
  Simply sends arm into its "cobra" pose where it is out of view of the camera/Kinect
*/

#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <actionlib/client/simple_action_client.h>
#include <clam_block_manipulation/ResetArmAction.h>
//#include <arm_navigation_msgs/MoveArmAction.h>
//#include <arm_navigation_msgs/utils.h>
#include <control_msgs/FollowJointTrajectoryAction.h>

typedef actionlib::SimpleActionClient< control_msgs::FollowJointTrajectoryAction > TrajClient;

namespace clam_block_manipulation
{

class ResetArmServer
{
private:

  // Action client for the joint trajectory action
  // used to trigger the arm movement action
  TrajClient* traj_client_;

  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<clam_block_manipulation::ResetArmAction> as_;
  std::string action_name_;

  clam_block_manipulation::ResetArmFeedback     feedback_;
  clam_block_manipulation::ResetArmResult       result_;
  clam_block_manipulation::ResetArmGoalConstPtr goal_;

public:
  ResetArmServer(const std::string name) :
    nh_("~"), as_(name, false), action_name_(name)
  {
    // tell the action client that we want to spin a thread by default
    traj_client_ = new TrajClient("clam_arm_controller/follow_joint_trajectory", true);
    //traj_client_ = new TrajClient("clam_move_clam_arm/follow_joint_trajectory", true);

    // wait for action server to come up
    while(!traj_client_->waitForServer(ros::Duration(5.0))){
      ROS_INFO("Waiting for the joint_trajectory_action server");
    }

    //register the goal and feeback callbacks
    as_.registerGoalCallback(boost::bind(&ResetArmServer::goalCB, this));
    as_.registerPreemptCallback(boost::bind(&ResetArmServer::preemptCB, this));

    as_.start();
  }

  //! Clean up the action client
  ~ResetArmServer()
  {
    delete traj_client_;
  }

  // Recieve Action Goal Function
  void goalCB()
  {
    ROS_INFO("[reset arm] Received goal!");

    goal_ = as_.acceptNewGoal();

    resetArm();
  }

  // Cancel the action
  void preemptCB()
  {
    ROS_INFO("[%s] Preempted", action_name_.c_str());
    // set the action state to preempted
    as_.setPreempted();
  }

  //! Sends the command to start a given trajectory
  void startTrajectory(control_msgs::FollowJointTrajectoryGoal goal)
  {
    ROS_INFO("Starting trajectory");

    // When to start the trajectory: 1s from now
    goal.trajectory.header.stamp = ros::Time::now() + ros::Duration(1.0);
    traj_client_->sendGoal(goal);
  }

  //! Generates a simple trajectory with two waypoints, used as an example
  /*! Note that this trajectory contains two waypoints, joined together
    as a single trajectory. Alternatively, each of these waypoints could
    be in its own trajectory - a trajectory can have one or more waypoints
    depending on the desired application.
  */
  control_msgs::FollowJointTrajectoryGoal armExtensionTrajectory()
  {
    ROS_INFO("Creating trajectory");

    //our goal variable
    control_msgs::FollowJointTrajectoryGoal goal;

    // First, the joint names, which apply to all waypoints
    goal.trajectory.joint_names.push_back("shoulder_pan_joint");
    goal.trajectory.joint_names.push_back("gripper_roll_joint");
    goal.trajectory.joint_names.push_back("l_gripper_aft_joint");
    goal.trajectory.joint_names.push_back("shoulder_pitch_joint");
    goal.trajectory.joint_names.push_back("elbow_roll_joint");
    goal.trajectory.joint_names.push_back("elbow_pitch_joint");
    goal.trajectory.joint_names.push_back("wrist_roll_joint");
    goal.trajectory.joint_names.push_back("wrist_pitch_joint");

    // We will have two waypoints in this goal trajectory
    goal.trajectory.points.resize(2);

    // First trajectory point
    // Positions
    int ind = 0;
    goal.trajectory.points[ind].positions.resize(8);
    goal.trajectory.points[ind].positions[0] = 0.0;
    goal.trajectory.points[ind].positions[1] = 0.0;
    goal.trajectory.points[ind].positions[2] = 0.0;
    goal.trajectory.points[ind].positions[3] = 0.0;
    goal.trajectory.points[ind].positions[4] = 0.0;
    goal.trajectory.points[ind].positions[5] = 0.0;
    goal.trajectory.points[ind].positions[6] = 0.0;
    goal.trajectory.points[ind].positions[7] = 0.0;
    // Velocities
    goal.trajectory.points[ind].velocities.resize(8);
    for (size_t j = 0; j < 8; ++j)
    {
      goal.trajectory.points[ind].velocities[j] = 1.0;
    }
    // To be reached 1 second after starting along the trajectory
    goal.trajectory.points[ind].time_from_start = ros::Duration(5.0);

    // Second trajectory point
    // Positions
    ind ++;
    goal.trajectory.points[ind].positions.resize(8);
    goal.trajectory.points[ind].positions[0] = 0.0;
    goal.trajectory.points[ind].positions[1] = 0.2;
    goal.trajectory.points[ind].positions[2] = -0.1;
    goal.trajectory.points[ind].positions[3] = 0.0;
    goal.trajectory.points[ind].positions[4] = 1.5;
    goal.trajectory.points[ind].positions[5] = -0.3;
    goal.trajectory.points[ind].positions[6] = 0.5;
    goal.trajectory.points[ind].positions[7] = 0.5;

    // Velocities
    goal.trajectory.points[ind].velocities.resize(8);
    for (size_t j = 0; j < 8; ++j)
    {
      goal.trajectory.points[ind].velocities[j] = 1.0;
    }
    // To be reached 2 seconds after starting along the trajectory
    goal.trajectory.points[ind].time_from_start = ros::Duration(5.0);

    //we are done; return the goal
    ROS_INFO("FINISHED CREATING GOAL");
    return goal;
  }

  //! Returns the current state of the action
  actionlib::SimpleClientGoalState getState()
  {
    return traj_client_->getState();
  }

  // Actually run the action
  void resetArm()
  {
    // Send the trajectory
    startTrajectory(armExtensionTrajectory());

    // Wait for trajectory completion
    while(!getState().isDone() && ros::ok())
    {
      ros::Duration(1).sleep();
    }

    //          as_.setSucceeded(result_);
  }
};

};


int main(int argc, char** argv)
{
  ros::init(argc, argv, "reset_arm_action_server");

  clam_block_manipulation::ResetArmServer server("reset_arm");
  ros::spin();

  return 0;
}

