/*
* Software License Agreement (BSD License)
*
* Copyright (c) 2010, Arizona Robotics Research Group,
* University of Arizona. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
*  * Redistributions of source code must retain the above copyright
*    notice, this list of conditions and the following disclaimer.
*  * Redistributions in binary form must reproduce the above
*    copyright notice, this list of conditions and the following
*    disclaimer in the documentation and/or other materials provided
*    with the distribution.
*  * Neither the name of University of Arizona nor the names of its
*    contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
* Author: Antons Rebguns
*
*/

#include <ros/ros.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <urdf/model.h>
#include <smart_arm_kinematics/SmartArmIK.h>

#define IKFAST_NO_MAIN
#include "smart_arm_ik.cpp"

class SmartArmIKService
{
private:
    ros::NodeHandle nh;
    tf::TransformListener tf_listener;
    ros::ServiceServer ik_service;
    IKReal rotation[9];
    std::vector<IKReal> free_params;
    std::vector<std::string> joint_names;
    std::vector<double> joint_limits_lower;
    std::vector<double> joint_limits_upper;
    std::string root_link;

public:
    SmartArmIKService(ros::NodeHandle node) : nh(node)
    {
        ros::NodeHandle local_nh("~");

        // gets the location of the robot description on the parameter server
        std::string robot_desc;
        local_nh.searchParam("robot_description", robot_desc);
        local_nh.param("root_link", root_link, std::string("arm_base_link"));

        rotation[0] = 1.0; rotation[1] = 0.0; rotation[2] = 0.0;
        rotation[3] = 0.0; rotation[4] = 1.0; rotation[5] = 0.0;
        rotation[6] = 0.0; rotation[7] = 0.0; rotation[8] = 1.0;
        free_params.push_back(0.0);

        joint_names.push_back("shoulder_pan_joint");
        joint_names.push_back("shoulder_pitch_joint");
        joint_names.push_back("elbow_flex_joint");
        joint_names.push_back("wrist_roll_joint");

        urdf::Model model;
        if (!model.initParam(robot_desc)) { ROS_ERROR("Failed to parse URDF description"); }

        for (size_t i = 0; i < joint_names.size(); ++i)
        {
            joint_limits_lower.push_back(model.getJoint(joint_names[i])->limits->lower);
            joint_limits_upper.push_back(model.getJoint(joint_names[i])->limits->upper);
        }

        ik_service = nh.advertiseService("smart_arm_ik_service", &SmartArmIKService::do_ik, this);
        ROS_INFO("smart_arm_ik_service:: successfully started");
    }

    bool do_ik(smart_arm_kinematics::SmartArmIK::Request  &req,
               smart_arm_kinematics::SmartArmIK::Response &res)
    {
        ROS_DEBUG("smart_arm_ik_service:: received service request");
        tf::Stamped<tf::Point> point_stamped;
        tf::pointStampedMsgToTF(req.goal, point_stamped);

        // convert to reference frame of root link of the arm
        if (!tf_listener.canTransform(root_link, point_stamped.frame_id_, point_stamped.stamp_))
        {
            std::string err;
            if (tf_listener.getLatestCommonTime(point_stamped.frame_id_, root_link, point_stamped.stamp_, &err) != tf::NO_ERROR)
            {
                ROS_ERROR("smart_arm_ik_service:: Cannot transform from '%s' to '%s'. TF said: %s", point_stamped.frame_id_.c_str(), root_link.c_str(), err.c_str());
                return false;
            }
        }

        try
        {
            tf_listener.transformPoint(root_link, point_stamped, point_stamped);
        }
        catch(...)
        {
            ROS_ERROR("smart_arm_ik_service:: Cannot transform from '%s' to '%s'", point_stamped.frame_id_.c_str(), root_link.c_str());
            return false;
        }

        IKReal translation[3];

        translation[0] = (float) point_stamped.x();
        translation[1] = (float) point_stamped.y();
        translation[2] = (float) point_stamped.z();

        std::vector<IKSolution> ik_solutions;
        res.success = ik(translation, rotation, &free_params[0], ik_solutions);

        if (res.success)
        {
            std::vector<IKReal> sol(getNumJoints());

            for (size_t i = 0; i < ik_solutions.size(); ++i)
            {
                std::vector<IKReal> vsolfree(ik_solutions[i].GetFree().size());
                ik_solutions[i].GetSolution(&sol[0], vsolfree.size() > 0 ? &vsolfree[0] : NULL);

                // check to see if returned solution are within joint limits
                bool outside_joint_limits = false;

                for ( size_t j = 0; j < sol.size(); ++j)
                {
                    if (sol[j] > joint_limits_upper[j] || sol[j] < joint_limits_lower[j])
                    {
                        outside_joint_limits = true;
                        break;
                    }
                }

                if (!outside_joint_limits)
                {
                    for ( size_t j = 0; j < sol.size(); ++j)
                    {
                        res.solutions.push_back(sol[j]);
                    }
                }
            }
        }

        if (res.solutions.size() == 0) { res.success = false; }

        return true;
    }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "smart_arm_ik_service_node");
    ros::NodeHandle node;
    SmartArmIKService ik_service(node);
    ros::spin();
}

