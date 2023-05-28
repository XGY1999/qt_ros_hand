#pragma once

#include <boost/shared_ptr.hpp>

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <map>
using std::map;

class irobot_hand{

public:
    irobot_hand(void);

    //1.operate hand

    //2.init
    virtual bool init_hand()=0;

    //3.read hand>
    virtual bool read_information()=0;

    //4.information input & set
    virtual bool admittance_set(int32_t position_set[],int16_t load_set[])=0;
    virtual bool load_set(int16_t load_set[])=0;
    virtual bool position_set(int32_t position_set[]) = 0;

    //5.Special operation
    virtual bool sync_move_for_load() = 0 ;
    virtual bool sync_move_for_position()= 0 ;
    virtual bool sync_move_for_Admittance()= 0 ;

    //  Static Function
    static boost::shared_ptr<irobot_hand> get_new_hand();

    std::map<unsigned int, int16_t>  m_joint_target_load;        //舵机目标力矩
    std::map<unsigned int, int32_t>  m_joint_target_position;    //舵机目标位置
    std::map<unsigned int, int32_t>  m_present_finger_positions; //舵机当前位置
    std::map<unsigned int, int32_t>  m_previous_finger_positions;//舵机上一时刻位置
    std::map<unsigned int, int16_t>  m_present_finger_loads;     //舵机当前力矩
    std::map<unsigned int, int32_t>  m_present_finger_velocitys; //舵机当前速度
    std::map<unsigned int, int>  m_parameter_K; //舵机当前K
    std::map<unsigned int, int>  m_parameter_B; //舵机当前B

//    std::map<unsigned int, int>  change_flags; //存放不同舵机运动方向的标志
    unsigned int m_motor_num; //舵机数目
    string info_out;
    int m_step;
    int parameter_K;
    int parameter_B;
};

typedef boost::shared_ptr<irobot_hand> irobot_hand_sptr;
