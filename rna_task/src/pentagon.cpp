#include "ros/ros.h"
#include "geometry_msgs/Twist.h"

using namespace std;

ros::Publisher vel_pub;

const double pi=3.14159265359;

void go(double speed);
void turn(double ang_speed);
double d2r(double degrees);

int main(int argc, char **argv)
{
    ros::init(argc, argv, "pentagon");
    ros::NodeHandle node;
    vel_pub=node.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);

    double speed, ang_speed;

    ros::Rate loop_rate(10);
    ROS_INFO("\n\n\n***********START TESTING******************\n");

    for(int i=0;i<5;i++)
    {
        go(0.4);
        ang_speed=d2r(14.4);
        turn(ang_speed);
    }

    ros::spin();

    return 0;
}

void go(double speed)
{
    geometry_msgs::Twist vel_msg;

    vel_msg.linear.x=speed;

    vel_msg.linear.y=0;
    vel_msg.linear.z=0;
    vel_msg.angular.x=0;
    vel_msg.angular.y=0;
    vel_msg.angular.z=0;

    double t0=ros::Time::now().toSec(),t1;

    ros::Rate loop_rate(100);
    do
    {
        vel_pub.publish(vel_msg);
        t1=ros::Time::now().toSec();
        ros::spinOnce();
        loop_rate.sleep();
    }while(t1-t0<5);
    vel_msg.linear.x=0;
    vel_pub.publish(vel_msg);
}

void turn(double speed)
{
    geometry_msgs::Twist vel_msg;

    vel_msg.linear.x=0;
    vel_msg.linear.y=0;
    vel_msg.linear.z=0;
    vel_msg.angular.x=0;
    vel_msg.angular.y=0;

    vel_msg.angular.z=speed;

    double t0=ros::Time::now().toSec(),t1;

    ros::Rate loop_rate(100);
    do
    {
        vel_pub.publish(vel_msg);
        t1=ros::Time::now().toSec();
        ros::spinOnce();
        loop_rate.sleep();
    }while(t1-t0<5);
    vel_msg.angular.z=0;
    vel_pub.publish(vel_msg);
}

double d2r(double degrees)
{
    return((pi*degrees)/180.0);
}
