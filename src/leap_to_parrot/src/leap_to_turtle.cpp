#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Point.h"
#include "leap_motion/leapros.h"
#include <iostream>
using namespace std;

struct palmPose{
	float x;
	float y;
	float z;
}palmPoseData;	

struct ypr{
	float x;
	float y;
	float z;
}yprData;


void leapYPRCallback(const leap_motion::leapros &yprLeap){
	yprData.x = yprLeap.ypr.x;
	yprData.y = yprLeap.ypr.y;
	yprData.z = yprLeap.ypr.z;
}

void leapPalmCallback(const geometry_msgs::Point &palmPoseLeap){
	palmPoseData.x = palmPoseLeap.x;
	palmPoseData.y = palmPoseLeap.y;
	palmPoseData.z = palmPoseLeap.z;
}


int main(int argc, char **argv){
	ros::init(argc, argv, "leap_subcribe_and_publish");
	ros::NodeHandle n;

	geometry_msgs::Twist geoTwistMsg;

	ros::Publisher twist_pub = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1000);
	ros::Subscriber leap_ypr_sub = n.subscribe("/leapmotion/data", 1000, leapYPRCallback);
	//ros::Subscriber leap_palm_sub = n.subscribe("/leapmotion/data", 1000, leapPalmCallback);

	ros::Rate loop_rate(10);

	while(ros::ok()){

		/*
		For turtle, only need linear x, and angular z, from -2 to 2
		*/

		geoTwistMsg.linear.x = -yprData.y/30;
		cout << "Linear x value " << geoTwistMsg.linear.x << endl;
		geoTwistMsg.linear.y = 0;
		geoTwistMsg.linear.z = 0;
		geoTwistMsg.angular.x = 0;
		geoTwistMsg.angular.y = 0;
		geoTwistMsg.angular.z = yprData.x/120;
		cout << "Angular z value " << geoTwistMsg.angular.z << endl;
		twist_pub.publish(geoTwistMsg);

		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}