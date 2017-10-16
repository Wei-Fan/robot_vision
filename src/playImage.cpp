#include <ros/ros.h>
#include <iostream>

#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <image_transport/image_transport.h>

using namespace cv;
using namespace std;

class PlayImage
{
public:
	PlayImage();
private:
	ros::NodeHandle n;
	ros::Subscriber img_sub;
	ros::Subscriber cam_sub;
	void image_process(Mat img);
	void imageCallback(const sensor_msgs::Image &msg);

};

PlayImage::PlayImage()
{
	cam_sub = n.subscribe("CamImage", 1, &PlayImage::imageCallback, this);//"CamImage"
	img_sub = n.subscribe("/ardrone/image_raw", 1, &PlayImage::imageCallback, this);//
}

void PlayImage::imageCallback(const sensor_msgs::Image &msg)
{
	cv_bridge::CvImagePtr cv_ptr;
	try
	{
		cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
	}
	catch (cv_bridge::Exception& e)
	{
		ROS_ERROR("cv_bridge exception: %s", e.what());
		return;
	}

	image_process(cv_ptr->image);
}

/*void PlayImage::altitudeCallback(const )
{

}*/

void PlayImage::image_process(Mat img)
{
	/*operate Mat directly and save it as a image file*/
	/*Mat edges;
	namedWindow("edges", 1);
	cvtColor(img, edges, CV_BGR2GRAY);
	Canny(edges, edges, 0, 30, 3);
	imshow("edges", edges);*/
	imshow("frame", img);
	if (char(waitKey(1)) == 's')
	{
		imwrite("/home/wade/catkin_ws/src/robot_vision/src/test.jpg", img);
		cout << "I have already save it!" << endl;
		destroyWindow("frame");
	}
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "playImage");
	PlayImage p;
	ros::spin();
	return 0;
}