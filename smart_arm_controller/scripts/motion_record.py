#!/usr/bin/env python
import roslib; roslib.load_manifest('smart_arm_controller')
import rospy
from std_msgs.msg import String
from dynamixel_msgs.msg import JointState
from dynamixel_controllers.srv import TorqueEnable
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

def callback(data):

    # print data.motor_ids[0]+' = '+data.current_pos
    coords.append(  [data.motor_ids[0], data.current_pos]   )


def listener():
    rospy.init_node('motion_record', anonymous=True)
    for joint_name in joint_names:
        rospy.Subscriber("/"+joint_name+"/state", JointState, callback)

    rospy.spin()

if __name__ == '__main__':

    print 'Disabling Torque to Servos'

    for joint_name in joint_names:
        print 'Looking for service ', joint_name
        rospy.wait_for_service('/'+joint_name+'/torque_enable')

        try:
            torquer = rospy.ServiceProxy('/'+joint_name+'/torque_enable', TorqueEnable)
            response = torquer(0)
            print 'Response from '+joint_name+':', response
        except rospy.ServiceException, e:
            print "Service call failed: %s"%e
            
    # begin recording joint angles
    print '-----------------------------------------------'
    print 'Listening'
    print '-----------------------------------------------'
    print ''

    listener()
    print 'Done listening'

    # Load the file where we will dump the position data
    f = open('dump.dat','w')
    pickle.dump(coords,f)
    f.close()

    print 'Recording successful'


