#include <ros/ros.h>
#include <iostream>
#include <stdio.h>

#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
	ros::init(argc, argv, "graspImage");
	ros::NodeHandle n;
	ros::Publisher img_pub = n.advertise<sensor_msgs::Image>("CamImage", 1000);
	ros::Rate rate(10);

	/*read image data from Cam*/	
	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		cerr << "Cannot open a cam~" << endl;
		return -1;
	}

	while (ros::ok())
	{
		/*get Mat from Cam*/
		Mat frame;
		cap >> frame;
		if (frame.empty())
		{
			break;
		}

		/*Use CvBridge to convert Mat to ROS Image Message*/
		cv_bridge::CvImage img_bridge;
		sensor_msgs::Image img_msg;

		std_msgs::Header header;
		//header.seq = counter;
		header.stamp  = ros::Time::now();
		img_bridge = cv_bridge::CvImage(header, sensor_msgs::image_encodings::BGR8, frame);
		img_bridge.toImageMsg(img_msg);
		img_pub.publish(img_msg);

		ros::spinOnce();
		rate.sleep();
	}

	return 0;
}
