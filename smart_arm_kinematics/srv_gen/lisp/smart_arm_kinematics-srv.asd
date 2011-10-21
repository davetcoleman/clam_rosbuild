
(cl:in-package :asdf)

(defsystem "smart_arm_kinematics-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
)
  :components ((:file "_package")
    (:file "SmartArmIK" :depends-on ("_package_SmartArmIK"))
    (:file "_package_SmartArmIK" :depends-on ("_package"))
  ))