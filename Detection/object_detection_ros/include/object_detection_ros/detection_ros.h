#ifndef DETECTION_ROS_H
#define DETECTION_ROS_H

#include "ros/ros.h"

#include "particle_filter.h"

#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include "sailboat_message/Sensor_msg.h"
//#include <opencv2/contrib/contrib.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "object_detection_ros/detection.h"
#include "cmath"
//#include <eigen3/Eigen/Dense>
#include <Eigen/Core>
#include <Eigen/Dense>


#define IMG_WIDTH 1296
#define IMG_HEIGHT 964


using namespace Eigen;
using namespace Eigen::internal;
using namespace Eigen::Architecture;
// using Eigen::MatrixXd;
using namespace std;

class DetectionRos{
public:
    ros::NodeHandle nh;
    ros::Subscriber sub_image;
    ros::Subscriber gps;
    image_transport::ImageTransport it;
    image_transport::Publisher pub_img_edge;
    image_transport::Publisher pub_img_dst;

    //DetectionRos(ros::NodeHandle _comm_nh);
    DetectionRos();
    ~DetectionRos();
    void roll_pitch_yaw_to_R(Vector3d E,Matrix3d &R);
    void detection_cb(const sensor_msgs::ImageConstPtr& img_in);
    void sensor_cb(const sailboat_message::Sensor_msg::ConstPtr& msg);
private:
    
    
    double posX;
    double posY;
    double pitch;
    double roll;
    double yaw;

    ParticleFilter *particleFilter;
    
    double f;

    double ball_r;

    int Num_ball;

    
};

#endif