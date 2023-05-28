#pragma once

#include <boost/shared_ptr.hpp>

#include <string>
using std::string;
#include <map>
using std::map;

enum MotorType
{
    MotorType_DynamixelXC430_W150T,
//    MotorType_DynamixelMX106,
};

class idxl_motor
{
public:
    idxl_motor();

    //  1.open/close port
    virtual bool open_port() = 0;
    virtual bool close_port() = 0;

    //  2. Enable torque
    virtual bool enable_all_torques(unsigned int * ids,int len) = 0;
    virtual bool disable_all_torques(unsigned int * ids,int len) = 0;
//    virtual bool enable_torque(unsigned int _motor_id) = 0;
//    virtual bool disable_torque(unsigned int _motor_id) = 0;

    //  3. Move to goal position
    virtual bool go2position(void) = 0;
    // virtual bool go2position(std::map<unsigned int, int>& _motor_positions) = 0;
    // virtual bool go2position(int dxl_goal_position) = 0;
    virtual bool set_motor_goal_position(unsigned int _motor_id, int _goal_position) = 0;

    //  4. Get current data
    virtual bool get_motor_position(std::map<unsigned int, int32_t>& _motor_positions) = 0;
    virtual bool get_motor_velocity(std::map<unsigned int, int32_t>& _motor_velocitys) = 0;
    virtual bool get_motor_load(std::map<unsigned int, int16_t>& _motor_loads) = 0;

    // virtual bool get_motor_data(int dxl_goal_position) = 0;

//    virtual bool set_motor_group(vector<uint8_t> _ids) = 0;
//    virtual bool add_motor_id(unsigned int _id) = 0;
//    virtual bool delete_motor_id(uint8_t _id) = 0;
//    virtual bool add_parameter_for_read(unsigned int _motor_index) = 0;
//    virtual int input_motor_goal_position(int dxl_goal_position) = 0;

    //  Static Function
    static boost::shared_ptr<idxl_motor> get_new_motor(MotorType _type );

    string info_out;
};

typedef boost::shared_ptr<idxl_motor> idxl_motor_sptr;


