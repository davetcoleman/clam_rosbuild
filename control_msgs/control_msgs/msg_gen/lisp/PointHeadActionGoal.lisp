; Auto-generated. Do not edit!


(cl:in-package control_msgs-msg)


;//! \htmlinclude PointHeadActionGoal.msg.html

(cl:defclass <PointHeadActionGoal> (roslisp-msg-protocol:ros-message)
  ((target
    :reader target
    :initarg :target
    :type geometry_msgs-msg:PointStamped
    :initform (cl:make-instance 'geometry_msgs-msg:PointStamped))
   (pointing_axis
    :reader pointing_axis
    :initarg :pointing_axis
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (pointing_frame
    :reader pointing_frame
    :initarg :pointing_frame
    :type cl:string
    :initform "")
   (min_duration
    :reader min_duration
    :initarg :min_duration
    :type cl:real
    :initform 0)
   (max_velocity
    :reader max_velocity
    :initarg :max_velocity
    :type cl:float
    :initform 0.0))
)

(cl:defclass PointHeadActionGoal (<PointHeadActionGoal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PointHeadActionGoal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PointHeadActionGoal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name control_msgs-msg:<PointHeadActionGoal> is deprecated: use control_msgs-msg:PointHeadActionGoal instead.")))

(cl:ensure-generic-function 'target-val :lambda-list '(m))
(cl:defmethod target-val ((m <PointHeadActionGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader control_msgs-msg:target-val is deprecated.  Use control_msgs-msg:target instead.")
  (target m))

(cl:ensure-generic-function 'pointing_axis-val :lambda-list '(m))
(cl:defmethod pointing_axis-val ((m <PointHeadActionGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader control_msgs-msg:pointing_axis-val is deprecated.  Use control_msgs-msg:pointing_axis instead.")
  (pointing_axis m))

(cl:ensure-generic-function 'pointing_frame-val :lambda-list '(m))
(cl:defmethod pointing_frame-val ((m <PointHeadActionGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader control_msgs-msg:pointing_frame-val is deprecated.  Use control_msgs-msg:pointing_frame instead.")
  (pointing_frame m))

(cl:ensure-generic-function 'min_duration-val :lambda-list '(m))
(cl:defmethod min_duration-val ((m <PointHeadActionGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader control_msgs-msg:min_duration-val is deprecated.  Use control_msgs-msg:min_duration instead.")
  (min_duration m))

(cl:ensure-generic-function 'max_velocity-val :lambda-list '(m))
(cl:defmethod max_velocity-val ((m <PointHeadActionGoal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader control_msgs-msg:max_velocity-val is deprecated.  Use control_msgs-msg:max_velocity instead.")
  (max_velocity m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PointHeadActionGoal>) ostream)
  "Serializes a message object of type '<PointHeadActionGoal>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'target) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'pointing_axis) ostream)
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'pointing_frame))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'pointing_frame))
  (cl:let ((__sec (cl:floor (cl:slot-value msg 'min_duration)))
        (__nsec (cl:round (cl:* 1e9 (cl:- (cl:slot-value msg 'min_duration) (cl:floor (cl:slot-value msg 'min_duration)))))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __sec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 0) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __nsec) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __nsec) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'max_velocity))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PointHeadActionGoal>) istream)
  "Deserializes a message object of type '<PointHeadActionGoal>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'target) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'pointing_axis) istream)
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'pointing_frame) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'pointing_frame) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__sec 0) (__nsec 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __sec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 0) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __nsec) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __nsec) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'min_duration) (cl:+ (cl:coerce __sec 'cl:double-float) (cl:/ __nsec 1e9))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'max_velocity) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PointHeadActionGoal>)))
  "Returns string type for a message object of type '<PointHeadActionGoal>"
  "control_msgs/PointHeadActionGoal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PointHeadActionGoal)))
  "Returns string type for a message object of type 'PointHeadActionGoal"
  "control_msgs/PointHeadActionGoal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PointHeadActionGoal>)))
  "Returns md5sum for a message object of type '<PointHeadActionGoal>"
  "8b92b1cd5e06c8a94c917dc3209a4c1d")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PointHeadActionGoal)))
  "Returns md5sum for a message object of type 'PointHeadActionGoal"
  "8b92b1cd5e06c8a94c917dc3209a4c1d")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PointHeadActionGoal>)))
  "Returns full string definition for message of type '<PointHeadActionGoal>"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%geometry_msgs/PointStamped target~%geometry_msgs/Vector3 pointing_axis~%string pointing_frame~%duration min_duration~%float64 max_velocity~%~%================================================================================~%MSG: geometry_msgs/PointStamped~%# This represents a Point with reference coordinate frame and timestamp~%Header header~%Point point~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PointHeadActionGoal)))
  "Returns full string definition for message of type 'PointHeadActionGoal"
  (cl:format cl:nil "# ====== DO NOT MODIFY! AUTOGENERATED FROM AN ACTION DEFINITION ======~%geometry_msgs/PointStamped target~%geometry_msgs/Vector3 pointing_axis~%string pointing_frame~%duration min_duration~%float64 max_velocity~%~%================================================================================~%MSG: geometry_msgs/PointStamped~%# This represents a Point with reference coordinate frame and timestamp~%Header header~%Point point~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PointHeadActionGoal>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'target))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'pointing_axis))
     4 (cl:length (cl:slot-value msg 'pointing_frame))
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PointHeadActionGoal>))
  "Converts a ROS message object to a list"
  (cl:list 'PointHeadActionGoal
    (cl:cons ':target (target msg))
    (cl:cons ':pointing_axis (pointing_axis msg))
    (cl:cons ':pointing_frame (pointing_frame msg))
    (cl:cons ':min_duration (min_duration msg))
    (cl:cons ':max_velocity (max_velocity msg))
))
