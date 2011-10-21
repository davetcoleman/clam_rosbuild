; Auto-generated. Do not edit!


(cl:in-package dynamixel_msgs-msg)


;//! \htmlinclude JointStateList.msg.html

(cl:defclass <JointStateList> (roslisp-msg-protocol:ros-message)
  ((motor_states
    :reader motor_states
    :initarg :motor_states
    :type (cl:vector dynamixel_msgs-msg:JointState)
   :initform (cl:make-array 0 :element-type 'dynamixel_msgs-msg:JointState :initial-element (cl:make-instance 'dynamixel_msgs-msg:JointState))))
)

(cl:defclass JointStateList (<JointStateList>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <JointStateList>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'JointStateList)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name dynamixel_msgs-msg:<JointStateList> is deprecated: use dynamixel_msgs-msg:JointStateList instead.")))

(cl:ensure-generic-function 'motor_states-val :lambda-list '(m))
(cl:defmethod motor_states-val ((m <JointStateList>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader dynamixel_msgs-msg:motor_states-val is deprecated.  Use dynamixel_msgs-msg:motor_states instead.")
  (motor_states m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <JointStateList>) ostream)
  "Serializes a message object of type '<JointStateList>"
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'motor_states))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'motor_states))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <JointStateList>) istream)
  "Deserializes a message object of type '<JointStateList>"
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'motor_states) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'motor_states)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'dynamixel_msgs-msg:JointState))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<JointStateList>)))
  "Returns string type for a message object of type '<JointStateList>"
  "dynamixel_msgs/JointStateList")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'JointStateList)))
  "Returns string type for a message object of type 'JointStateList"
  "dynamixel_msgs/JointStateList")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<JointStateList>)))
  "Returns md5sum for a message object of type '<JointStateList>"
  "39b7d137ea0a3aade285e88b8dd58dfe")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'JointStateList)))
  "Returns md5sum for a message object of type 'JointStateList"
  "39b7d137ea0a3aade285e88b8dd58dfe")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<JointStateList>)))
  "Returns full string definition for message of type '<JointStateList>"
  (cl:format cl:nil "JointState[] motor_states~%~%================================================================================~%MSG: dynamixel_msgs/JointState~%Header header~%string name         # joint name~%int32[] motor_ids   # motor ids controlling this joint~%int32[] motor_temps # motor temperatures, same order as motor_ids~%~%float64 goal_pos    # commanded position (in radians)~%float64 current_pos # current joint position (in radians)~%float64 error       # error between commanded and current positions (in radians)~%float64 velocity    # current joint speed (in radians per second)~%float64 load        # current load~%bool is_moving      # is joint currently in motion~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'JointStateList)))
  "Returns full string definition for message of type 'JointStateList"
  (cl:format cl:nil "JointState[] motor_states~%~%================================================================================~%MSG: dynamixel_msgs/JointState~%Header header~%string name         # joint name~%int32[] motor_ids   # motor ids controlling this joint~%int32[] motor_temps # motor temperatures, same order as motor_ids~%~%float64 goal_pos    # commanded position (in radians)~%float64 current_pos # current joint position (in radians)~%float64 error       # error between commanded and current positions (in radians)~%float64 velocity    # current joint speed (in radians per second)~%float64 load        # current load~%bool is_moving      # is joint currently in motion~%~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <JointStateList>))
  (cl:+ 0
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'motor_states) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <JointStateList>))
  "Converts a ROS message object to a list"
  (cl:list 'JointStateList
    (cl:cons ':motor_states (motor_states msg))
))
