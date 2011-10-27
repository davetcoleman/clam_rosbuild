#!/usr/bin/env python
import roslib; roslib.load_manifest('smart_arm_controller')
import rospy
from std_msgs.msg import String
from dynamixel_msgs.msg import JointState
from dynamixel_controllers.srv import *
import time
import sys
import pickle

joint_names = ('shoulder_pan_controller',
               'shoulder_pitch_controller',
               'elbow_roll_controller',
               'elbow_pitch_controller',
               'wrist_roll_controller',
               'wrist_pitch_controller',
               'gripper_roll_controller',
               'gripper_grip_controller')

coords = []   # store an array of coordinates over time

if __name__ == '__main__':

    if len(sys.argv) != 2:
        print 'Usage: compliance.py <1-255>\n'
        sys.exit(1)

    print 'Setting compliance slope to '+sys.argv[1]

    ivalue  = int(sys.argv[1])
    service_name = 'set_compliance_slope'

    for joint_name in joint_names:

        print 'Looking for service ', joint_name + '/' + service_name

        rospy.wait_for_service('/'+joint_name+'/'+service_name)

        try:
            service1 = rospy.ServiceProxy('/'+joint_name+'/'+service_name, SetComplianceSlope)
            response = service1(ivalue)
            print '\tSuccess'
        except rospy.ServiceException, e:
            print "\tService call failed: %s"%e
            
    # begin recording joint angles
    



