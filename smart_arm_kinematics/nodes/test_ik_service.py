#!/usr/bin/env python
# Copyright (c) 2010, Antons Rebguns. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of the Willow Garage, Inc. nor the names of its
#       contributors may be used to endorse or promote products derived from
#       this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 'AS IS'
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

# Author: Antons Rebguns

import roslib; roslib.load_manifest('smart_arm_kinematics')

import time

import rospy
from geometry_msgs.msg import PointStamped
from smart_arm_kinematics.srv import SmartArmIK
from std_msgs.msg import Float64

if __name__ == '__main__':
    try:
        rospy.init_node('test_ik_service', anonymous=True)
        rospy.wait_for_service('smart_arm_ik_service')
        
        shoulder_pan_pub = rospy.Publisher('shoulder_pan_controller/command', Float64)
        shoulder_tilt_pub = rospy.Publisher('shoulder_pitch_controller/command', Float64)
        elobow_tilt_pub = rospy.Publisher('elbow_flex_controller/command', Float64)
        wrist_rotate_pub = rospy.Publisher('wrist_roll_controller/command', Float64)
        
        rospy.sleep(1)
        
        try:
            ik_service = rospy.ServiceProxy('smart_arm_ik_service', SmartArmIK)
            point = PointStamped()
            point.header.stamp = rospy.Time.now()
            point.header.frame_id = 'arm_base_link'
            point.point.x = 0.15
            point.point.y = 0.20
            point.point.z = 0.0
            resp = ik_service(point)
            
            if resp:
                rospy.loginfo('%s = %s' % (str(resp.success), str(resp.solutions)))
                
                if resp.success:
                    rospy.logdebug("Publishing stuff")
                    sol1 = resp.solutions[0:4]
                    rospy.logdebug("%s" % str(sol1))
                    shoulder_pan_pub.publish(sol1[0])
                    shoulder_tilt_pub.publish(sol1[1])
                    elobow_tilt_pub.publish(sol1[2])
                    wrist_rotate_pub.publish(sol1[3])
                
        except rospy.ServiceException, e:
            rospy.logerr('Service call failed %s' % e)
    except rospy.ROSInterruptException: pass

