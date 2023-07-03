
(cl:in-package :asdf)

(defsystem "point-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "point" :depends-on ("_package_point"))
    (:file "_package_point" :depends-on ("_package"))
  ))