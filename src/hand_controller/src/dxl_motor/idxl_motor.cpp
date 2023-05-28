#include <dxl_motor/idxl_motor.h>

#include "dxl_motor_xc430_w150t.h"
//#include "dxl_motor_mx106.h"

#include <boost/make_shared.hpp>

idxl_motor::idxl_motor()
{

}

boost::shared_ptr<idxl_motor> idxl_motor::get_new_motor(MotorType _type)
{
    switch (_type) {
    case MotorType_DynamixelXC430_W150T:
        return boost::make_shared<dxl_motor_xc430_w150t>();
//    case MotorType_DynamixelMX106:
//        return boost::make_shared<dxl_motor_mx106>();

    default:
        break;

    }
    return boost::make_shared<dxl_motor_xc430_w150t>();
}
