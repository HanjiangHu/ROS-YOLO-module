/*
 * ros_yolo_test.cpp
 *
 *  Created on: Jan 4, 2018
 *      Author: HU HANJIANG
 */

#include <ros/ros.h>
#include <ros/package.h>
#include <std_msgs/String.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>

#include <iostream>
#include <vector>
#include <sstream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "test_detector.h"



const std::string RECEIVE_IMG_TOPIC_NAME = "/camera/rgb/image_raw";
const std::string PUBLISH_RET_TOPIC_NAME = "/yolo_ret";

char * cfgdata = const_cast<char*>(("/home/huhanjiang/catkin_ws/src/ros_yolo/data/voc.data"));
char * cfg = const_cast<char*>(("/home/huhanjiang/catkin_ws/src/ros_yolo/data/tiny-yolo-voc.cfg"));
char * weights = const_cast<char*>(("/home/huhanjiang/catkin_ws/src/ros_yolo/data/tiny-yolo-voc.weights"));
char * image_test = const_cast<char*>(("/home/huhanjiang/catkin_ws/src/ros_yolo/data/rgb.png"));
ros::Publisher gPublisher;

void publishRet(char *datacfg, char *cfgfile, char *weightfile, char *filename);
void imageCallback(const sensor_msgs::ImageConstPtr& msg) {
    try {
        cv_bridge::CvImagePtr cv_ptr = cv_bridge::toCvCopy(msg, "bgr8");
        cv::imwrite("/home/huhanjiang/catkin_ws/src/ros_yolo/data/rgb.png", cv_ptr->image);
        
        //std::cout<<"hhh"<<std::endl;
        publishRet(cfgdata,cfg,weights ,image_test);
		
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}

// TODO: Define a msg or create a service
// Try to receive : $rostopic echo /yolo_ret
void publishRet(char *datacfg, char *cfgfile, char *weightfile, char *filename)  {
    detection test = detector1(datacfg,cfgfile,weightfile ,filename,0.24,0.5,0,0);
    std_msgs::String msg;
    std::stringstream ss;
    int i,j;
    ss << test.num << '\n';
        for(i = 0;i < test.num;i++){
            for(j = 0; j < test.classes; ++j){
            if ((test.probs[i][j] > .24) && (test.probs[i][j] < 1.0) && (typeid(test.probs[i][j]) == typeid(float))){
                ss << test.names[j] << '\t' << test.probs[i][j] <<'\t' << test.pos[i].x <<'\t' <<test.pos[i].y << '\t' <<test.pos[i].w << '\t' <<test.pos[i].h << '\n';
            }
        }
        }
    msg.data = ss.str();
    gPublisher.publish(msg);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "ros_yolo_test");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    // To receive an image from the topic, PUBLISH_RET_TOPIC_NAME
    image_transport::Subscriber sub = it.subscribe(RECEIVE_IMG_TOPIC_NAME, 1, imageCallback);//订阅
	gPublisher = nh.advertise<std_msgs::String>(PUBLISH_RET_TOPIC_NAME, 1);
    //const std::string ROOT_SAMPLE = ros::package::getPath("ros_yolo");
    /*char * cfgdata_path = const_cast<char*>(("/home/huhanjiang/catkin_ws/src/ros_yolo/data/coco.data"));
    char * cfg_path = const_cast<char*>(("/home/huhanjiang/catkin_ws/src/ros_yolo/data/yolo.cfg"));
    char * weights_path = const_cast<char*>(("/home/huhanjiang/catkin_ws/src/ros_yolo/data/yolo.weights"));
    char * image_path = const_cast<char*>(("/home/huhanjiang/catkin_ws/src/ros_yolo/data/dog.jpg"));*/
    /*detector_test(cfgdata_path,cfg_path,weights_path ,image_path,0.24,0.5,0,0);*///仅测试节点
    //publishRet(cfgdata_path,cfg_path,weights_path ,image_path);//仅测试发布

    ros::spin();
    ros::shutdown();
    return 0;
}
