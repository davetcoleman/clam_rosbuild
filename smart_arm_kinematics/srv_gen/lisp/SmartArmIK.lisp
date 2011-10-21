; Auto-generated. Do not edit!


(cl:in-package smart_arm_kinematics-srv)


;//! \htmlinclude SmartArmIK-request.msg.html

(cl:defclass <SmartArmIK-request> (roslisp-msg-protocol:ros-message)
  ((goal
    :reader goal
    :initarg :goal
    :type geometry_msgs-msg:PointStamped
    :initform (cl:make-instance 'geometry_msgs-msg:PointStamped)))
)

(cl:defclass SmartArmIK-request (<SmartArmIK-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SmartArmIK-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SmartArmIK-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name smart_arm_kinematics-srv:<SmartArmIK-request> is deprecated: use smart_arm_kinematics-srv:SmartArmIK-request instead.")))

(cl:ensure-generic-function 'goal-val :lambda-list '(m))
(cl:defmethod goal-val ((m <SmartArmIK-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smart_arm_kinematics-srv:goal-val is deprecated.  Use smart_arm_kinematics-srv:goal instead.")
  (goal m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SmartArmIK-request>) ostream)
  "Serializes a message object of type '<SmartArmIK-request>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'goal) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SmartArmIK-request>) istream)
  "Deserializes a message object of type '<SmartArmIK-request>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'goal) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SmartArmIK-request>)))
  "Returns string type for a service object of type '<SmartArmIK-request>"
  "smart_arm_kinematics/SmartArmIKRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SmartArmIK-request)))
  "Returns string type for a service object of type 'SmartArmIK-request"
  "smart_arm_kinematics/SmartArmIKRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SmartArmIK-request>)))
  "Returns md5sum for a message object of type '<SmartArmIK-request>"
  "330a33b8e6f4e7b91d8e0afbea1b0223")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SmartArmIK-request)))
  "Returns md5sum for a message object of type 'SmartArmIK-request"
  "330a33b8e6f4e7b91d8e0afbea1b0223")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SmartArmIK-request>)))
  "Returns full string definition for message of type '<SmartArmIK-request>"
  (cl:format cl:nil "geometry_msgs/PointStamped goal~%~%================================================================================~%MSG: geometry_msgs/PointStamped~%# This represents a Point with reference coordinate frame and timestamp~%Header header~%Point point~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SmartArmIK-request)))
  "Returns full string definition for message of type 'SmartArmIK-request"
  (cl:format cl:nil "geometry_msgs/PointStamped goal~%~%================================================================================~%MSG: geometry_msgs/PointStamped~%# This represents a Point with reference coordinate frame and timestamp~%Header header~%Point point~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SmartArmIK-request>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'goal))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SmartArmIK-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SmartArmIK-request
    (cl:cons ':goal (goal msg))
))
;//! \htmlinclude SmartArmIK-response.msg.html

(cl:defclass <SmartArmIK-response> (roslisp-msg-protocol:ros-message)
  ((success
    :reader success
    :initarg :success
    :type cl:boolean
    :initform cl:nil)
   (solutions
    :reader solutions
    :initarg :solutions
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass SmartArmIK-response (<SmartArmIK-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SmartArmIK-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SmartArmIK-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name smart_arm_kinematics-srv:<SmartArmIK-response> is deprecated: use smart_arm_kinematics-srv:SmartArmIK-response instead.")))

(cl:ensure-generic-function 'success-val :lambda-list '(m))
(cl:defmethod success-val ((m <SmartArmIK-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smart_arm_kinematics-srv:success-val is deprecated.  Use smart_arm_kinematics-srv:success instead.")
  (success m))

(cl:ensure-generic-function 'solutions-val :lambda-list '(m))
(cl:defmethod solutions-val ((m <SmartArmIK-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader smart_arm_kinematics-srv:solutions-val is deprecated.  Use smart_arm_kinematics-srv:solutions instead.")
  (solutions m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SmartArmIK-response>) ostream)
  "Serializes a message object of type '<SmartArmIK-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'success) 1 0)) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'solutions))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'solutions))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SmartArmIK-response>) istream)
  "Deserializes a message object of type '<SmartArmIK-response>"
    (cl:setf (cl:slot-value msg 'success) (cl:not (cl:zerop (cl:read-byte istream))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'solutions) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'solutions)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SmartArmIK-response>)))
  "Returns string type for a service object of type '<SmartArmIK-response>"
  "smart_arm_kinematics/SmartArmIKResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SmartArmIK-response)))
  "Returns string type for a service object of type 'SmartArmIK-response"
  "smart_arm_kinematics/SmartArmIKResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SmartArmIK-response>)))
  "Returns md5sum for a message object of type '<SmartArmIK-response>"
  "330a33b8e6f4e7b91d8e0afbea1b0223")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SmartArmIK-response)))
  "Returns md5sum for a message object of type 'SmartArmIK-response"
  "330a33b8e6f4e7b91d8e0afbea1b0223")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SmartArmIK-response>)))
  "Returns full string definition for message of type '<SmartArmIK-response>"
  (cl:format cl:nil "bool success~%float64[] solutions~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SmartArmIK-response)))
  "Returns full string definition for message of type 'SmartArmIK-response"
  (cl:format cl:nil "bool success~%float64[] solutions~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SmartArmIK-response>))
  (cl:+ 0
     1
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'solutions) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SmartArmIK-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SmartArmIK-response
    (cl:cons ':success (success msg))
    (cl:cons ':solutions (solutions msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SmartArmIK)))
  'SmartArmIK-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SmartArmIK)))
  'SmartArmIK-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SmartArmIK)))
  "Returns string type for a service object of type '<SmartArmIK>"
  "smart_arm_kinematics/SmartArmIK")