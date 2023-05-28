#!/usr/bin/env python3

import rospy
import cv2
import os
import time
from std_msgs.msg import String
import numpy as np
from scipy.io import loadmat

if __name__=="__main__":
   dir_path="/home/lsw/111"
   files=os.listdir(dir_path)
   for file in files:
    img=cv2.imread(dir_path+"/"+file)
    cv2.imshow("src",img)
    cv2.waitKey(500)
    #cv2.destroyWindow("src")

