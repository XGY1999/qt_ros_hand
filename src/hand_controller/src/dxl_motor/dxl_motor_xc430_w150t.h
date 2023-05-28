#pragma once

#include <dxl_motor/idxl_motor.h>

#include "dynamixel_sdk.h"                                  // Uses Dynamixel SDK library

#include <fcntl.h>
#include <termios.h>
#include <mutex>
using namespace std;

#define STDIN_FILENO 0

// Control table address
#define ADDR_PRO_TORQUE_ENABLE          64                 // Control table address is different in Dynamixel model
#define ADDR_PRO_GOAL_POSITION          116
#define ADDR_PRO_PRESENT_LOAD           126
#define ADDR_PRO_PRESENT_VELOCITY       128
#define ADDR_PRO_PRESENT_POSITION       132

// Data Byte Length
#define LEN_PRO_GOAL_POSITION           4
#define LEN_PRO_PRESENT_POSITION        4
#define LEN_PRO_PRESENT_LOAD            2
#define LEN_PRO_PRESENT_VELOCITY        4

//// Protocol version
#define PROTOCOL_VERSION                2.0                 // See which protocol version is used in the Dynamixel

// Default setting
#define DXL1_ID                         1                   // Dynamixel#1 ID: 1
#define DXL2_ID                         2                   // Dynamixel#2 ID: 2
#define BAUDRATE                        115200
#define DEVICENAME                      "/dev/ttyUSB0"      // Check which port is being used on your controller
//                                                            // ex) Windows: "COM1"   Linux: "/dev/ttyUSB0" Mac: "/dev/tty.usbserial-*"

#define TORQUE_ENABLE                   1                   // Value for enabling the torque
#define TORQUE_DISABLE                  0                   // Value for disabling the torque
#define DXL_MINIMUM_POSITION_VALUE      0             // Dynamixel will rotate between this value
#define DXL_MAXIMUM_POSITION_VALUE      4095              // and this value (note that the Dynamixel would not move when the position value is out of movable range. Check e-manual about the range of the Dynamixel you use.)
#define DXL_MOVING_STATUS_THRESHOLD     20                  // Dynamixel moving status threshold

#define ESC_ASCII_VALUE                 0x1b

#define DXL_LOWORD(l)       ((uint16_t)(((uint64_t)(l)) & 0xffff))
#define DXL_HIWORD(l)       ((uint16_t)((((uint64_t)(l)) >> 16) & 0xffff))
#define DXL_LOBYTE(w)       ((uint8_t)(((uint64_t)(w)) & 0xff))
#define DXL_HIBYTE(w)       ((uint8_t)((((uint64_t)(w)) >> 8) & 0xff))



#include <vector>
using std::vector;


class dxl_motor_xc430_w150t : public idxl_motor
{
public:
    // dxl_motor_xc430_w150t();

    //  1.open/close port
    virtual bool open_port()override;
    bool close_port() override;

    //  2. Enable torque
    bool enable_all_torques(unsigned int * ids,int len)override;
    bool disable_all_torques(unsigned int * ids,int len) override;

    //  3. Move to goal position
    bool set_motor_goal_position(unsigned int _motor_index, int dxl_goal_position) override;
    bool go2position() override;
    // bool go2position(std::map<unsigned int, int> &_motor_positions) override;
    // bool go2position(int dxl_goal_position) override;

    //  4. Get current position(or load)
    bool get_motor_position(std::map<unsigned int, int32_t> &_motor_positions) override;
    bool get_motor_velocity(std::map<unsigned int, int32_t>& _motor_velocitys) override;
    bool get_motor_load(std::map<unsigned int, int16_t> &_motor_loads) override;
    // bool get_motor_data(int dxl_goal_position) override;

    // 5.others
    bool add_motor_id(unsigned int _id);
    bool delete_motor_id(unsigned int _id);
    bool add_parameter_for_read(unsigned int _motor_index);



private:
    dynamixel::PortHandler*     m_portHandler;
    dynamixel::PacketHandler*   m_packetHandler;

    // Initialize GroupSyncWrite instance
    boost::shared_ptr<dynamixel::GroupSyncWrite>  m_goalPositionSyncWrite;
    boost::shared_ptr<dynamixel::GroupSyncRead>   m_positionSyncRead;
    boost::shared_ptr<dynamixel::GroupSyncRead>   m_velocitySyncRead;
    boost::shared_ptr<dynamixel::GroupSyncRead>   m_loadSyncRead;

    vector<int>             m_motor_ids;
    mutex                   mtx;
};


