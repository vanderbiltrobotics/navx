#include "AHRS.h"
#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "sensor_msgs/MagneticField.h"

#include <cmath>

const uint8_t RATE = 100;
const float degToRad = M_PI / 180;

int main(int argc, char** argv)
{
    ros::init(argc, argv, "navx_node");
    ros::NodeHandle nh;
    ros::Publisher imu_pub = nh.advertise<sensor_msgs::Imu>("imu/data_raw", RATE);
    ros::Publisher mag_pub = nh.advertise<sensor_msgs::MagneticField>("imu/mag", RATE);
    ros::Rate period(RATE);

    AHRS navx = AHRS("/dev/ttyACM0", AHRS::SerialDataType::kRawData, RATE);
    sensor_msgs::Imu imu;
    sensor_msgs::MagneticField mag;

    // fill and send message
    while (ros::ok()) {
        // header
        imu.header.frame_id = "imu";

        // linear acceleration
        imu.linear_acceleration.x = navx.GetRawAccelX();
        imu.linear_acceleration.y = navx.GetRawAccelY();
        imu.linear_acceleration.z = navx.GetRawAccelZ();

        // angular velocity
        imu.angular_velocity.x = navx.GetRawGyroX() * degToRad;
        imu.angular_velocity.y = navx.GetRawGyroY() * degToRad;
        imu.angular_velocity.z = navx.GetRawGyroZ() * degToRad;

        // magnetic field
        mag.magnetic_field.x = navx.GetRawMagX();
        mag.magnetic_field.y = navx.GetRawMagY();
        mag.magnetic_field.z = navx.GetRawMagZ();

        imu_pub.publish(imu);
        mag_pub.publish(mag);
        ros::spinOnce();
        period.sleep();
    }
    return 0;
}