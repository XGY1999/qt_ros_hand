#include "dxl_hand.h"
#include <dxl_motor/idxl_motor.h>
#include <boost/make_shared.hpp>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <cmath>
#include <fstream>

//#include <ros/ros.h>
//#include "sensor_msgs/JointState.h"

using namespace std;

dxl_hand::dxl_hand()//舵机初始化
    : msp_motor(nullptr)
{
    msp_motor = idxl_motor::get_new_motor(MotorType_DynamixelXC430_W150T);//选择舵机型号
    m_step = 50;
    parameter_K = 10;
    parameter_B = 2;
    msp_motor->open_port();//打开端口
    m_motor_num = 6;
//    unsigned int ids[1]={1};//设置舵机ID
    unsigned int ids[6]={1,2,3,4,5,6};//设置舵机ID
    int len = sizeof(ids) / sizeof(unsigned int);//舵机数量
    msp_motor->enable_all_torques(ids,len);//舵机使能
    info_out = msp_motor->info_out;

    int16_t init_load[6]={0,0,0,0,0,0};//设置初始力矩
    int32_t init_position[6]={500,2048,3000,2048,3200,2048};//设置初始位置
    int32_t max_position[6]={1200,2400,3700,2420,3250,2600};//设置最大安全位置(5,6号反转)
    int32_t min_position[6]={500,1500,3000,1500,2500,1650};//设置最小安全位置 (5,6号反转)

    //舵机设定位置匹配ID
    for (int i=1;i<= 6;i++)
    {
        m_joint_target_load.insert(std::make_pair(i,init_load[i-1]));
        m_joint_target_position.insert(std::make_pair(i,init_position[i-1]));
        m_joint_safe_position_max.insert(std::make_pair(i,max_position[i-1]));
        m_joint_safe_position_min.insert(std::make_pair(i,min_position[i-1]));

        m_previous_finger_positions.insert(std::make_pair(i,0));
        m_present_finger_positions.insert(std::make_pair(i,0));
        m_present_finger_loads.insert(std::make_pair(i,0));
        m_present_finger_velocitys.insert(std::make_pair(i,0));

        m_parameter_B.insert(std::make_pair(i,2));
        m_parameter_K.insert(std::make_pair(i,10));
    }

    //初始化flag
    for (int i = 1; i <= 6; i++)
    {
        change_flags.insert(std::make_pair(i,0));
    }
}

//析构
dxl_hand::~dxl_hand()
{
    //设置舵机ID
    unsigned int ids[6]={1,2,3,4,5,6};
    int len = sizeof(ids) / sizeof(unsigned int);
    msp_motor->disable_all_torques(ids,len);//舵机去能
    cout<<"System shutdown"<<endl;
}

//初始化
bool dxl_hand::init_hand() {
    sync_move_for_position();
    return true;
}

bool dxl_hand::admittance_set(int32_t position_set[],int16_t load_set[])
{
    m_joint_target_load.clear();
    m_joint_target_position.clear();
    for (unsigned int i = 1; i <= m_motor_num; i++)
    {
        m_joint_target_position.insert(std::make_pair(i,position_set[i-1]));
        m_joint_target_load.insert(std::make_pair(i,load_set[i-1]));
    }
    return true;
}

//力矩输入设定
bool dxl_hand::load_set(int16_t load_set[]){
    m_joint_target_load.clear();
    for (unsigned int i = 1; i <= m_motor_num; i++)
    {
        m_joint_target_load.insert(std::make_pair(i,load_set[i-1]));
    }
    return true;
}

//位置输入设定
bool dxl_hand::position_set(int32_t position_set[]){
    m_joint_target_position.clear();
    for (unsigned int i = 1; i <= m_motor_num; i++)
    {
        m_joint_target_position.insert(std::make_pair(i,position_set[i-1]));
    }
    return true;
}

//
idxl_motor_sptr dxl_hand::get_msp_motor()
{
    return msp_motor;
}

//对比目标力矩，判断策略
bool dxl_hand::judge_load(std::map<unsigned int, int16_t> present_finger_loads,
std::map<unsigned int, int16_t> &_joint_target_load)
{
    for (std::map<unsigned int, int>::iterator it = change_flags.begin(); it!=change_flags.end();it++)
    {
        if ((_joint_target_load[it->first]-present_finger_loads[it->first]) > 10)
        {
            change_flags[it->first] = 1; //当前力矩小于目标力矩，舵机正转
        }
        else if ((_joint_target_load[it->first]-present_finger_loads[it->first]) <-10)
        {
            change_flags[it->first] = 2; //当前力矩大于目标力矩，舵机反转
        }
        else {
            change_flags[it->first] = 3; //当前力矩接近目标力矩，舵机停转
        }
    }
    return true;

}

//对比目标位置，判断策略
bool dxl_hand::judge_position(std::map<unsigned int, int32_t> present_finger_positions,
std::map<unsigned int, int32_t> &_joint_target_position)
{
    for (std::map<unsigned int, int>::iterator it = change_flags.begin(); it!=change_flags.end();it++)
    {
        if ((_joint_target_position[it->first]-present_finger_positions[it->first]) >20){
            change_flags[it->first] = 1; //当前位置小于目标位置，舵机正转
        }
        else if ((_joint_target_position[it->first]-present_finger_positions[it->first]) < -20)
        {
            change_flags[it->first] = 2; //当前位置大于目标位置，舵机反转
        }
        else {
            change_flags[it->first] = 3; //当前力矩位置目标位置，舵机停转
        }
    }

    return true;

}

//导纳控制,判断策略
bool dxl_hand::judge_Admittance(std::map<unsigned int, int32_t> &Admittance_target_position)
{
    for (std::map<unsigned int, int32_t>::iterator it = Admittance_target_position.begin();
         it!=Admittance_target_position.end();it++){
        //此为忽略x''和x'
//        it->second = m_joint_target_position[it->first] - m_present_finger_loads[it->first]/parameter_K;
        //此为忽略x''
//        if (abs(m_present_finger_loads[it->first])>abs(m_joint_target_load[it->first])){
          it->second = m_joint_target_position[it->first]
                       +(m_previous_finger_positions[it->first]-m_joint_target_position[it->first])
                       +0.05*(-(m_present_finger_loads[it->first]-m_joint_target_load[it->first])
                              -m_parameter_K[it->first]*(m_present_finger_positions[it->first]-m_joint_target_position[it->first]))/m_parameter_B[it->first];
//        }else{
//            it->second = m_joint_target_position[it->first]
//                         +(m_previous_finger_positions[it->first]-m_joint_target_position[it->first])
//                         +0.05*(0
//                                -parameter_K*(m_present_finger_positions[it->first]-m_joint_target_position[it->first]))/parameter_B;
//        }
    }
    return true;
}

//根据策略，调整每个舵机的位置
bool dxl_hand::return_move_object(std::map<unsigned int, int32_t> &one_time_target_position)
{
    int32_t temp;
    for (std::map<unsigned int, int>::iterator it =change_flags.begin();
        it!=change_flags.end();it++){
        switch (it->second)
        {
        case 1:
            temp = m_present_finger_positions[it->first] + m_step;
            one_time_target_position [it->first]=temp;
            break;
        case 2:
            temp = m_present_finger_positions[it->first] - m_step;
            one_time_target_position [it->first] =temp;
            break;
        case 3:
            temp = m_present_finger_positions[it->first];
            one_time_target_position [it->first] = temp;
            break;
        default:
            break;
        }
    }

    return true;

}

//舵机安全位置检测
bool dxl_hand::safe_position_test(){

    for (std::map<unsigned int, int32_t>::iterator it = m_present_finger_positions.begin();
    it != m_present_finger_positions.end();it++)
    {
        if(it->second > m_joint_safe_position_max[it->first] || it->second < m_joint_safe_position_min[it->first])
        {
            change_flags[it->first] = 3;
        }
    }
    return true;
}

//力控舵机
bool dxl_hand::sync_move_for_load(){
    loop_flag = false;//循环标志

    do{
        //获取舵机当前位置和力矩
        msp_motor->get_motor_load(m_present_finger_loads);
        msp_motor->get_motor_position(m_present_finger_positions);
        //比较当前力矩与目标力矩，给出舵机移动信号
        judge_load(m_present_finger_loads,m_joint_target_load);
        //舵机位置安全检测,超出安全范围的舵机的信号为3（不转动）
        safe_position_test();
        //通过信号设定舵机下一步移动
        return_move_object(m_joint_target_position);

        //设置目标位置并输入所有舵机
        for(std::map<unsigned int, int32_t>::iterator it = m_joint_target_position.begin();
            it != m_joint_target_position.end(); ++it){
            msp_motor->set_motor_goal_position(it->first,it->second);
        }

        msp_motor->go2position();
        //获取舵机当前位置和力矩
        msp_motor->get_motor_load(m_present_finger_loads);
        msp_motor->get_motor_position(m_present_finger_positions);
        //判断所有手指的力矩是否满足要求，均满足则停止循环
        for(std::map<unsigned int, int>::iterator it = change_flags.begin();
            it != change_flags.end(); ++it){
            if (it->second ==3){
                loop_flag = false;
            }
            else if (it->second != 3){
                loop_flag = true;   //只要有未达目标的手指，便继续循环执行
                break;
            }
        }

    }while (loop_flag);

    return true;

}

//位置控制舵机
bool dxl_hand::sync_move_for_position(){
    //初始化参数
    loop_flag = false;//循环标志
    std::map<unsigned int, int32_t> one_time_target_position;
    for(std::map<unsigned int, int>::iterator it = m_joint_target_position.begin();
        it != m_joint_target_position.end(); ++it){
        one_time_target_position.insert(std::make_pair(it->first,0));
    }
    do{
        //获取舵机当前位置和力矩
        msp_motor->get_motor_load(m_present_finger_loads);
        msp_motor->get_motor_position(m_present_finger_positions);
        //比较当前为位置与目标位置，给出舵机移动信号
        judge_position(m_present_finger_positions,m_joint_target_position);
        //舵机位置安全检测,超出安全范围的舵机的信号为3（不转动）
//        safe_position_test();
        //通过信号设定舵机下一步移动
        return_move_object(one_time_target_position);


        //设置目标位置并输入所有舵机
        for(std::map<unsigned int, int32_t>::iterator it = one_time_target_position.begin();
            it != one_time_target_position.end(); ++it){
            msp_motor->set_motor_goal_position(it->first,it->second);
        }
        msp_motor->go2position();
        //获取舵机当前位置和力矩
        msp_motor->get_motor_load(m_present_finger_loads);
        msp_motor->get_motor_position(m_present_finger_positions);

        //判断所有手指的位置是否满足要求，均满足则停止循环
        for(std::map<unsigned int, int>::iterator it = change_flags.begin();
            it != change_flags.end(); ++it){
            if (it->second ==3){
                loop_flag = false;
            }
            else if (it->second != 3){
                loop_flag = true;   //只要有未达目标的手指，便继续循环执行
                break;
            }
        }

    }while (loop_flag);

    return true;
}

bool dxl_hand::sync_move_for_Admittance()
{
    //创建一个pubilsher，发布名为hand的topic,消息类型为sensor_msgs::JointState
//    ros::Publisher m_hand_pub = m_n.advertise<sensor_msgs::JointState>("m_hand",1000);
//    ros::Rate loop_rate(30);
    loop_flag = false;//循环标志
    std::map<unsigned int, int32_t> Admittance_target_position;
    for(std::map<unsigned int, int>::iterator it = m_joint_target_position.begin();
        it != m_joint_target_position.end(); ++it){
        Admittance_target_position.insert(std::make_pair(it->first,it->second));
    }
    do{
        //获取舵机当前位置和力矩
        get_motor_data();

        //********ros publish***********
//        msg.name={"ID1","ID2","ID3","ID4","ID5","ID6"};
//        msg.header.stamp = ros::Time::now();
//        msg.effort.resize(m_motor_num);
//        msg.position.resize(m_motor_num);
//        for (int i=0;i<6;i++) {
//          msg.effort[i] = m_present_finger_loads[i+1];
//          msg.position[i] = m_present_finger_positions[i+1];
//        }
//        m_hand_pub.publish(msg);
//        const boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
//        const boost::posix_time::time_duration td = now.time_of_day();
//        int hh = td.hours();
//        int mm = td.minutes();
//        int ss = td.seconds();
//        int ms = td.total_milliseconds() - ((hh * 3600 + mm * 60 + ss) * 1000);
//        cout <<"time_start: "<< hh << ":" << mm << ":" << ss << ":" << ms << endl;
//        ros::spinOnce();
//        loop_rate.sleep();
        //********end********************
        //比较当前与目标，给出舵机移动信号
        judge_Admittance(Admittance_target_position);
        //舵机位置安全检测,超出安全范围的舵机的信号为3（不转动）
        safe_position_test();
        //设置目标位置并输入所有舵机
        for(std::map<unsigned int, int32_t>::iterator it = Admittance_target_position.begin();
            it != Admittance_target_position.end(); ++it){
            msp_motor->set_motor_goal_position(it->first,it->second);
        }

        msp_motor->go2position();
        //获取舵机当前位置和力矩
//        get_motor_data();
        //判断所有手指的位置是否满足要求，均满足则停止循环
//        for(std::map<unsigned int, int>::iterator it = change_flags.begin();
//            it != change_flags.end(); ++it){
//            if (it->second ==3){
//                loop_flag = false;
//            }
//            else if (it->second != 3){
//                loop_flag = true;   //只要有未达目标的手指，便继续循环执行
//                break;
//            }
//        }

    }while (loop_flag);
    return true;
}

bool dxl_hand::get_motor_data()
{
    msp_motor->get_motor_load(m_present_finger_loads);
    msp_motor->get_motor_position(m_present_finger_positions);
    m_previous_finger_positions.clear();
    m_previous_finger_positions = m_present_finger_positions;
    msp_motor->get_motor_velocity(m_present_finger_velocitys);
    return true;
}

bool dxl_hand::read_information(){
    // 打印舵机当前位置和力矩
    cout << "***************************************"<<endl;
    for (std::map<unsigned int, int32_t>::iterator it = m_present_finger_positions.begin();
        it != m_present_finger_positions.end();it++){
        cout << "[id:00" << it->first
        << " PresPos:" << it->second
        << " GoalPos:" << m_joint_target_position[it->first]
        << " PresLoad: "
        << m_present_finger_loads[it->first]
//        << (m_present_finger_loads[it->first]/1000.0)*MAX_TORQUE
        << " GoalLoad: " << m_joint_target_load[it->first]
        << "]"<<endl;
    }
    cout << "***************************************"<<endl;
    return true;
}
