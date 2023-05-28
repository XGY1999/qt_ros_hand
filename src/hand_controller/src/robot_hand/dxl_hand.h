#pragma once
using namespace std;
#include <robot_hand/irobot_hand.h>

#include <dxl_motor/idxl_motor.h>

#include <vector>
using std::vector;

#include <map>
using std::map;

#include <string>
using std::string;

#include <fstream>
using std::fstream;

#include <mutex>

#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
//#define Step 50
#define MAX_TORQUE 1.6

class dxl_hand
        : public irobot_hand
{
public:
    dxl_hand();
    ~dxl_hand();

public:
//    vector<dxl_finger_sptr>             m_finger_vec;
    idxl_motor_sptr                     msp_motor;

//    ofstream                            ofs;
//    bool                                flag;

public:
    //1.operate hand

    //2.init
    bool init_hand(void) override;

    //3.information input & set & read
    bool admittance_set(int32_t position_set[],int16_t load_set[]) override;
    bool load_set(int16_t load_set[]) override;
    bool position_set(int32_t position_set[]) override;
    bool read_information() override;

    //4.information judge & processing
    bool judge_load(std::map<unsigned int, int16_t> present_finger_loads,std::map<unsigned int, int16_t> &_joint_target_load);
    bool judge_position(std::map<unsigned int, int32_t> present_finger_positions,std::map<unsigned int, int32_t> &_joint_target_position);    
    bool return_move_object(std::map<unsigned int, int32_t> &m_joint_target_position);
    bool safe_position_test();
    bool judge_Admittance(std::map<unsigned int, int32_t> &Admittance_target_position);

    //5.get sptr to finger
    idxl_motor_sptr get_msp_motor();

    //6.Special operation
    bool sync_move_for_load()  override;
    bool sync_move_for_position()  override;
    bool sync_move_for_Admittance()  override;

    //7.Special function
    bool get_motor_data();

    std::map<unsigned int, int32_t>  m_joint_safe_position_max; //舵机最大安全位置
    std::map<unsigned int, int32_t>  m_joint_safe_position_min; //舵机最大安全位置
    std::map<unsigned int, int>  change_flags; //存放不同舵机运动方向的标志
//    std::map<unsigned int, int16_t>  m_joint_target_load;       //舵机目标力矩
//    std::map<unsigned int, int32_t>  m_joint_target_position;   //舵机目标位置
//    std::map<unsigned int, int32_t>  m_present_finger_positions;//舵机当前位置
//    std::map<unsigned int, int16_t>  m_present_finger_loads;    //舵机当前力矩
    
    bool loop_flag; //循环标志


//    std::array<double,3> m_present_load;
//    mutex mtx;
    ros::NodeHandle m_n;
    ros::Publisher m_hand_pub;
    sensor_msgs::JointState msg;
//    ros::Rate loop_rate;




private:
    //define dynamixel initial position
    std::array<int,9> m_dyn_init_position;

};

typedef boost::shared_ptr<dxl_hand> dxl_hand_sptr;

