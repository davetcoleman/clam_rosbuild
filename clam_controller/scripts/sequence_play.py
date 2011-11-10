import roslib; roslib.load_manifest('clam_controller')
import time
import rospy
import pickle
import traceback
import sys
from std_msgs.msg import Float64

joint_names = ('shoulder_pan_controller',
               'shoulder_pitch_controller',
               'elbow_roll_controller',
               'elbow_pitch_controller',
               'wrist_roll_controller',
               'wrist_pitch_controller',
               'gripper_roll_controller',
               'gripper_grip_controller')
               
def main():

    pubs = [rospy.Publisher(name + '/command', Float64) for name in joint_names]
    rospy.init_node('motion_play', anonymous=True)
    
    # determine file name to open
    if len(sys.argv) != 2:
        filename = 'dump.dat'
    else:
        filename = sys.argv[1]

    f = open(filename,'r')
    read_coords = pickle.load(f)

    print read_coords;

    for coor in read_coords:
        print 'Playing...'

        print coor

        pubs[coor[0]].publish(coor[1])
        print 'sending command', coor[1]
        time.sleep(.1)

    print 'COMPLETE ---------------------------- '


# Where the program starts                                                                                          
if __name__ == "__main__":
    try:
        main()
    # Now attempt to prevent the robot from falling limp                                                            
    except KeyboardInterrupt:
        print "done"
    except Exception as e:
        traceback.print_exc(e)
        print "done"
