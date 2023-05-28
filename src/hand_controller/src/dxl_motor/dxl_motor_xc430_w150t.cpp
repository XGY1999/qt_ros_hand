#include "dxl_motor_xc430_w150t.h"
#include "dxl_motor_config.h"

#include <iostream>
using std::cout;
using std::endl;


#include <boost/make_shared.hpp>

bool dxl_motor_xc430_w150t::open_port()//舵机端口开启
{
    m_portHandler = dynamixel::PortHandler::getPortHandler(DEVICENAME);
    m_packetHandler = dynamixel::PacketHandler::getPacketHandler(PROTOCOL_VERSION);

    //Open port 开启端口及故障检测
    if (m_portHandler->openPort())
    {
       info_out += "Succeeded to open the port!\n";
//       cout << "Succeeded to open the port!" << endl;
    }
    else
    {
       info_out += "Failed to open the port!\n";
       info_out += "Press any key to terminate...\n";
//       cout << "Failed to open the port!" << endl;
//       cout << "Press any key to terminate..."<<endl;;
       return false;
    }
    // Set port baudrate 设置端口波特率及故障检测
    if (m_portHandler->setBaudRate(BAUDRATE))
    {
       info_out += "Succeeded to change the baudrate!\n";
//       cout << "Succeeded to change the baudrate!" << endl;
    }
    else
    {
       info_out += "Failed to change the baudrate!\n";
       info_out += "Press any key to terminate...\n";
//       cout << "Failed to change the baudrate!" << endl;
//       cout << "Press any key to terminate..." <<endl;
       return false;
    }


    m_goalPositionSyncWrite = boost::make_shared<dynamixel::GroupSyncWrite>(m_portHandler, m_packetHandler, ADDR_PRO_GOAL_POSITION, LEN_PRO_GOAL_POSITION);
    m_positionSyncRead = boost::make_shared<dynamixel::GroupSyncRead>(m_portHandler, m_packetHandler, ADDR_PRO_PRESENT_POSITION, LEN_PRO_PRESENT_POSITION);
    m_loadSyncRead = boost::make_shared<dynamixel::GroupSyncRead>(m_portHandler, m_packetHandler, ADDR_PRO_PRESENT_LOAD, LEN_PRO_PRESENT_LOAD);
    m_velocitySyncRead = boost::make_shared<dynamixel::GroupSyncRead>(m_portHandler, m_packetHandler, ADDR_PRO_PRESENT_VELOCITY, LEN_PRO_PRESENT_VELOCITY);

    return true;
}

bool dxl_motor_xc430_w150t::close_port()//舵机端口关闭
{
    m_portHandler->closePort();
    return true;
}

bool dxl_motor_xc430_w150t::enable_all_torques(unsigned int *ids, int len)//舵机使能
{
    //舵机编号储存
    for (int i =0;i<len;i++){
        m_motor_ids.push_back(ids[i]);
    }


    int dxl_comm_result = COMM_TX_FAIL;               // Communication result
    uint8_t dxl_error = 0;                            // Dynamixel error


    //舵机编号使能及故障检测
    for(vector<int>::iterator it=m_motor_ids.begin();it!=m_motor_ids.end();it++){
        dxl_comm_result = m_packetHandler->write1ByteTxRx(
                    m_portHandler, *it, ADDR_PRO_TORQUE_ENABLE, TORQUE_ENABLE, &dxl_error);

        if (dxl_comm_result != COMM_SUCCESS)
        {
            cout << m_packetHandler->getTxRxResult(dxl_comm_result) << endl;
            return false;
        }
        else if (dxl_error != 0)
        {
            cout << m_packetHandler->getRxPacketError(dxl_error) << endl;
            return false;
        }
        else
        {
            info_out += "Dynamixel# ";
            info_out += to_string(*it);
            info_out += " has been successfully connected\n";
            cout << "Dynamixel# " << *it << " has been successfully connected" <<endl;
        }

    }




    return true;
}

bool dxl_motor_xc430_w150t::disable_all_torques(unsigned int *ids, int len)//舵机去能
{
    //舵机编号储存
    for (int i =0;i<len;i++){
        m_motor_ids.push_back(ids[i]);
    }

    int dxl_comm_result = COMM_TX_FAIL;               // Communication result
    uint8_t dxl_error = 0;

    //舵机编号去能及故障检测
    for (vector<int>::iterator it=m_motor_ids.begin();it!=m_motor_ids.end();it++) {
        dxl_comm_result = m_packetHandler->write1ByteTxRx(
                    m_portHandler,*it, ADDR_PRO_TORQUE_ENABLE, TORQUE_DISABLE, &dxl_error);

        if (dxl_comm_result != COMM_SUCCESS)
        {
            cout << m_packetHandler->getTxRxResult(dxl_comm_result) << endl;
            return false;
        }
        else if (dxl_error != 0)
        {
            cout << m_packetHandler->getRxPacketError(dxl_error) << endl;
            return false;
        }
    }
    return true;
}

//舵机目标位置设置
bool dxl_motor_xc430_w150t::set_motor_goal_position(unsigned int _motor_index, int dxl_goal_position)
{
    bool dxl_addparam_result = false;                 // addParam result

    uint8_t param_goal_position[4];

    //舵机位置分解
    param_goal_position[0] = DXL_LOBYTE(DXL_LOWORD(dxl_goal_position));
    param_goal_position[1] = DXL_HIBYTE(DXL_LOWORD(dxl_goal_position));
    param_goal_position[2] = DXL_LOBYTE(DXL_HIWORD(dxl_goal_position));
    param_goal_position[3] = DXL_HIBYTE(DXL_HIWORD(dxl_goal_position));

    //舵机ID检测
    if(_motor_index >= MAX_MOTOR_ID)
        return false;

    // Add Dynamixel goal position value to the Syncwrite storage 添加ID舵机目标位置至Syncwrite储存
    dxl_addparam_result = m_goalPositionSyncWrite->addParam(_motor_index, param_goal_position);
    if (dxl_addparam_result != true)
    {
      cout << "[ID:" << _motor_index << " ] groupSyncWrite addparam failed" << endl;
      return 0;
    }

    return true;
}

bool dxl_motor_xc430_w150t::go2position()//舵机移动至目标位置
{
    int dxl_comm_result = COMM_TX_FAIL;               // Communication result

    // Syncwrite goal position 写入目标位置并发送
    dxl_comm_result = m_goalPositionSyncWrite->txPacket();
    if (dxl_comm_result != COMM_SUCCESS)
        cout << "MyTest: " << m_packetHandler->getTxRxResult(dxl_comm_result) << endl;

    // Clear syncwrite parameter storage 清空写入参数
    m_goalPositionSyncWrite->clearParam();
    return true;
}

//读取舵机当前位置
bool dxl_motor_xc430_w150t::get_motor_position(std::map<unsigned int, int32_t> &_motor_positions)
{
    int dxl_comm_result = COMM_TX_FAIL;
    uint8_t dxl_error = 0;
    bool dxl_getdata_result = false;
    bool dxl_addparam_result = false;

    //清空读取参数
    m_positionSyncRead->clearParam();

    //addParam for read 添加ID供读取
    for(std::map<unsigned int, int>::iterator it = _motor_positions.begin();
        it != _motor_positions.end(); ++it){
        dxl_addparam_result = m_positionSyncRead->addParam(it->first);
        if (dxl_addparam_result != true)
        {
          cout << it->first << "Position SyncRead addparam failed" << endl;
          return false;
        }
    }

    //  Syncread present position - tx 检测可否读取当前位置信息
    dxl_comm_result = m_positionSyncRead->txRxPacket();
    if (dxl_comm_result != COMM_SUCCESS)
    {
        cout << "get presposi is not  ok" << endl;
        cout << m_packetHandler->getTxRxResult(dxl_comm_result) << endl;
        return false;
    }

     // check - each motor 检测每个舵机的状态
     for(std::map<unsigned int, int>::iterator it = _motor_positions.begin();
         it != _motor_positions.end(); ++it){
         if (m_positionSyncRead->getError(it->first, &dxl_error))
         {
             cout << it->first << m_packetHandler->getRxPacketError(dxl_error) << endl;
             return false;
         }
     }

     //  Read motor position 获得位置信息
     for(std::map<unsigned int, int>::iterator it = _motor_positions.begin();
         it != _motor_positions.end(); ++it){

         //Check if groupsyncread data of Dynamixel is available 检测是否成功获得位置信息
          dxl_getdata_result = m_positionSyncRead->isAvailable(it->first, ADDR_PRO_PRESENT_POSITION, LEN_PRO_PRESENT_POSITION);
          if (dxl_getdata_result != true)
          {
              cout<< it->first << "Position SyncRead getdata failed" << endl;
              return false;
          }
         it->second = m_positionSyncRead->getData(it->first, ADDR_PRO_PRESENT_POSITION, LEN_PRO_PRESENT_POSITION);
     }

     return true;
}

bool dxl_motor_xc430_w150t::get_motor_velocity(std::map<unsigned int, int32_t> &_motor_velocitys)
{
    int dxl_comm_result = COMM_TX_FAIL;
    uint8_t dxl_error = 0;
    bool dxl_getdata_result = false;
    bool dxl_addparam_result = false;

    //清空读取参数
    m_velocitySyncRead->clearParam();

    //addParam for read 添加ID供读取
    for(std::map<unsigned int, int>::iterator it = _motor_velocitys.begin();
        it != _motor_velocitys.end(); ++it){
        dxl_addparam_result = m_velocitySyncRead->addParam(it->first);
        if (dxl_addparam_result != true)
        {
          cout << it->first << "Velocity SyncRead addparam failed" << endl;
          return false;
        }
    }

    //  Syncread present position - tx 检测可否读取当前速度信息
    dxl_comm_result = m_velocitySyncRead->txRxPacket();
    if (dxl_comm_result != COMM_SUCCESS)
    {
        cout << "get presVelocity is not  ok" << endl;
        cout << m_packetHandler->getTxRxResult(dxl_comm_result) << endl;
        return false;
    }

     // check - each motor 检测每个舵机的状态
     for(std::map<unsigned int, int>::iterator it = _motor_velocitys.begin();
         it != _motor_velocitys.end(); ++it){
         if (m_velocitySyncRead->getError(it->first, &dxl_error))
         {
             cout << it->first << m_packetHandler->getRxPacketError(dxl_error) << endl;
             return false;
         }
     }

     //  Read motor velocity 获得速度信息
     for(std::map<unsigned int, int>::iterator it = _motor_velocitys.begin();
         it != _motor_velocitys.end(); ++it){

         //Check if groupsyncread data of Dynamixel is available 检测是否成功获得速度信息
          dxl_getdata_result = m_velocitySyncRead->isAvailable(it->first, ADDR_PRO_PRESENT_VELOCITY, LEN_PRO_PRESENT_VELOCITY);
          if (dxl_getdata_result != true)
          {
              cout<< it->first << "Velocity SyncRead getdata failed" << endl;
              return false;
          }
         it->second = m_velocitySyncRead->getData(it->first, ADDR_PRO_PRESENT_VELOCITY, LEN_PRO_PRESENT_VELOCITY);
     }

    return true;
}

bool dxl_motor_xc430_w150t::get_motor_load(std::map<unsigned int, int16_t> &_motor_loads)
{
    int dxl_comm_result = COMM_TX_FAIL;
        uint8_t dxl_error = 0;
        bool dxl_getdata_result = false;  // addParam result
        bool dxl_addparam_result = false; // addParam result
        //清空读取参数
        m_loadSyncRead->clearParam();

        //  Add the motor id for reading 添加ID供读取
        for(std::map<unsigned int, int16_t>::iterator it = _motor_loads.begin();
            it != _motor_loads.end(); ++it){
            dxl_addparam_result = m_loadSyncRead->addParam(it->first);
            if (dxl_addparam_result != true)
            {
              cout << it->first << "Load SyncRead addparam failed" << endl;
              return false;
            }
        }

        //  Syncread present load - tx 检测可否读取当前力矩信息
        dxl_comm_result = m_loadSyncRead->txRxPacket();
        if (dxl_comm_result != COMM_SUCCESS)
        {
            cout << "get presload is not ok" << endl;
            cout << m_packetHandler->getTxRxResult(dxl_comm_result) << endl;
            return false;
        }


        //  check - each motor 检测每个舵机的状态
         for(std::map<unsigned int, int16_t>::iterator it = _motor_loads.begin();
             it != _motor_loads.end(); ++it){
             if (m_loadSyncRead->getError(it->first, &dxl_error))
             {
                 cout << it->first << m_packetHandler->getRxPacketError(dxl_error) << endl;
                 return false;
             }
         }

        //  Read motor load 获得力矩信息
        for(std::map<unsigned int, int16_t>::iterator it = _motor_loads.begin();
            it != _motor_loads.end(); ++it){

            //Check if loadsyncread data of Dynamixel is available 检测是否成功获得力矩信息
             dxl_getdata_result = m_loadSyncRead->isAvailable(it->first, ADDR_PRO_PRESENT_LOAD, LEN_PRO_PRESENT_LOAD);
             if (dxl_getdata_result != true)
             {
                 cout<< it->first << "Load SyncRead getdata failed" << endl;
                 return false;
             }
            it->second = m_loadSyncRead->getData(it->first, ADDR_PRO_PRESENT_LOAD, LEN_PRO_PRESENT_LOAD);
        }

        return true;
}

