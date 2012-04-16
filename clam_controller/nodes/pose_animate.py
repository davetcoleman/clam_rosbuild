#!/usr/bin/env python

import roslib; roslib.load_manifest('clam_controller')
import time
import rospy

from std_msgs.msg import Float64

class PoseAnimate():
    def __init__(self):
        rospy.init_node('pose_animate', anonymous=True)

        self.joint_names = ('shoulder_pan_controller',
                       'shoulder_pitch_controller',
                       'elbow_roll_controller',
                       'elbow_pitch_controller',
                       'wrist_roll_controller',
                       'wrist_pitch_controller',
                       'gripper_roll_controller',
                       'l_gripper_aft_controller')
        
        self.joint_commands = (-1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, -1.0)
        self.joint_commands2 = (0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)


        pubs = [rospy.Publisher(name + '/command', Float64) for name in self.joint_names]
   
        while(True):
            for i in range(len(pubs)):
                pubs[i].publish(self.joint_commands[i])
                print 'sending command'
                time.sleep(.5)

            print ' -------------------------------'
            time.sleep(4);

            for i in range(len(pubs)):
                pubs[i].publish(self.joint_commands2[i])
                print 'sending command'
                time.sleep(.5)

            time.sleep(4);


# Where the program starts                                                                                          
if __name__ == "__main__":
    try:
        s = PoseAnimate()
        rospy.spin()
    except rospy.ROSInterruptException: pass
