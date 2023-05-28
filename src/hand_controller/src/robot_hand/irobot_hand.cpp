#include <robot_hand/irobot_hand.h>

#include "dxl_hand.h"

#include <boost/make_shared.hpp>

//#include "ros/ros.h"
//#include "sensor_msgs/JointState.h"

irobot_hand::irobot_hand()
{

}

boost::shared_ptr<irobot_hand> irobot_hand::get_new_hand()
{
    return boost::make_shared<dxl_hand>();
}
