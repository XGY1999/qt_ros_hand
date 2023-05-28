#include <iostream>
using namespace std;

#include <thread>
using std::thread;

#include <robot_hand/irobot_hand.h>
#include <dxl_motor/idxl_motor.h>

#include <map>
using std::map;

#include <cmath>
using std::abs;

#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/JointState.h"

int main(int argc, char **argv)
{
    ros::init(argc ,argv , "hand_publisher");
    ros::NodeHandle n;
    ros::Publisher hand_pub = n.advertise<sensor_msgs::JointState>("hand_info",1);
    ros::Rate loop_rate(30);
    sensor_msgs::JointState msg;

    //init sptr
    irobot_hand_sptr sp_hand = irobot_hand::get_new_hand();
    sp_hand->init_hand();
    sleep(1);
    cout<<"control begin"<<endl;

    bool ControlKey = true;
    bool RosKey = false;
    std::thread th1([&]{
    while (ControlKey)
    {
        sp_hand->sync_move_for_Admittance();
    }
    });

    std::thread th2([&]{
    msg.header.stamp = ros::Time::now();
    msg.name={"ID1","ID2","ID3","ID4","ID5","ID6"};
    msg.effort.resize(6);
    msg.position.resize(6);
    msg.velocity.resize(13);
    while (ControlKey)
    {
      if (RosKey){
        msg.header.stamp = ros::Time::now();
        for (int i=0;i<12;i++) {
          if(i<6){
            msg.effort[i] = sp_hand->m_present_finger_loads[i+1];
            msg.position[i] = sp_hand->m_present_finger_positions[i+1];
            msg.velocity[i] = sp_hand->m_parameter_B[i+1];
          }
          else {
            msg.effort[i] = sp_hand->m_joint_target_load[i-5];
            msg.position[i] = sp_hand->m_joint_target_position[i-5];
            msg.velocity[i] = sp_hand->m_parameter_K[i-5];
          }
        }
//        msg.velocity[12] =
        hand_pub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
      }
      else{
        sleep(1);
      }
    }
    });

    while (ControlKey)
     {
         int flag;
         cout<<"Choose your action 1.Init 2.Grasp 3.Open 4.Stop pub 5.Run pub 9.Info 0.Exit"<<endl;
         cin>> flag;
         switch (flag)
         {
         case 1://初始化
         {
             int32_t position_set[] = {500,2048,3000,2048,3200,2048};
             int16_t load_set[] = {0,0,0,0,0,0};
             sp_hand->admittance_set(position_set,load_set);
             break;
         }
         case 2://抓取
         {
             int32_t position_set[] = {1100,2300,3600,2300,2600,1800};
             int16_t load_set[] = {0,0,0,0,0,0};
             sp_hand->admittance_set(position_set,load_set);
             break;
         }
         case 3://张开
         {
             int32_t position_set[] = {500,1700,3000,1700,3200,2400};
             int16_t load_set[] = {0,0,0,0,0,0};
             sp_hand->admittance_set(position_set,load_set);
             break;
         }
         case 4://关闭pub节点
         {
             RosKey = false;
             break;
         }
         case 5://打开pub节点
         {
             RosKey = true;
             break;
         }
         case 9://信息读取
             sp_hand->read_information();
             break;
         case 0://退出
         {
             int32_t position_set[] = {500,2048,3000,2048,3200,2048};
             int16_t load_set[] = {0,0,0,0,0,0};
             sp_hand->admittance_set(position_set,load_set);
             sleep(1);
             ControlKey = false;
             // ::exit(0);
             break;
         }
         default:
             break;
         }
    }


    th1.detach();
    th2.detach();

    return 0;

}
