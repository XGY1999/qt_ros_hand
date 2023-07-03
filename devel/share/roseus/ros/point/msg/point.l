;; Auto-generated. Do not edit!


(when (boundp 'point::point)
  (if (not (find-package "POINT"))
    (make-package "POINT"))
  (shadow 'point (find-package "POINT")))
(unless (find-package "POINT::POINT")
  (make-package "POINT::POINT"))

(in-package "ROS")
;;//! \htmlinclude point.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass point::point
  :super ros::object
  :slots (_header _out_of_track _x _y ))

(defmethod point::point
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:out_of_track __out_of_track) (let (r) (dotimes (i 0) (push nil r)) r))
    ((:x __x) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:y __y) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _header __header)
   (setq _out_of_track __out_of_track)
   (setq _x __x)
   (setq _y __y)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:out_of_track
   (&optional __out_of_track)
   (if __out_of_track (setq _out_of_track __out_of_track)) _out_of_track)
  (:x
   (&optional __x)
   (if __x (setq _x __x)) _x)
  (:y
   (&optional __y)
   (if __y (setq _y __y)) _y)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; bool[] _out_of_track
    (* 1    (length _out_of_track)) 4
    ;; float32[] _x
    (* 4    (length _x)) 4
    ;; float32[] _y
    (* 4    (length _y)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; bool[] _out_of_track
     (write-long (length _out_of_track) s)
     (dotimes (i (length _out_of_track))
       (if (elt _out_of_track i) (write-byte -1 s) (write-byte 0 s))
       )
     ;; float32[] _x
     (write-long (length _x) s)
     (dotimes (i (length _x))
       (sys::poke (elt _x i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;; float32[] _y
     (write-long (length _y) s)
     (dotimes (i (length _y))
       (sys::poke (elt _y i) (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; bool[] _out_of_track
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _out_of_track (make-list n))
     (dotimes (i n)
     (setf (elt _out_of_track i) (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
     ))
   ;; float32[] _x
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _x (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _x i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;; float32[] _y
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _y (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _y i) (sys::peek buf ptr- :float)) (incf ptr- 4)
     ))
   ;;
   self)
  )

(setf (get point::point :md5sum-) "7739175ded79f351deb9a2f8b5da48ef")
(setf (get point::point :datatype-) "point/point")
(setf (get point::point :definition-)
      "std_msgs/Header header
bool[] out_of_track
float32[] x
float32[] y

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

")



(provide :point/point "7739175ded79f351deb9a2f8b5da48ef")


