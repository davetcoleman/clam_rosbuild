#!/usr/bin/env python
import roslib; roslib.load_manifest('smart_arm_controller')
import rospy
from std_msgs.msg import String
from dynamixel_msgs.msg import JointState
from dynamixel_controllers.srv import *
import time
import sys

joint_names = ('shoulder_pan_controller',
               'shoulder_pitch_controller',
               'elbow_roll_controller',
               'elbow_pitch_controller',
               'wrist_roll_controller',
               'wrist_pitch_controller',
               'gripper_roll_controller',
               'gripper_grip_controller')


if __name__ == '__main__':

    if len(sys.argv) != 2:
        print 'Usage: speed.py <number>\n'
        sys.exit(1)

    print 'Setting speed to '+sys.argv[1]

    ivalue  = float(sys.argv[1])
    service_name = 'set_speed'

    for joint_name in joint_names:

        print 'Looking for service ', joint_name + '/' + service_name

        rospy.wait_for_service('/'+joint_name+'/'+service_name)

        try:
            service1 = rospy.ServiceProxy('/'+joint_name+'/'+service_name, SetSpeed)
            response = service1(ivalue)
            print '\tSuccess'
        except rospy.ServiceException, e:
            print "\tService call failed: %s"%e
            



