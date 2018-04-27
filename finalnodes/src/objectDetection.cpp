#include <ros/ros.h>
#include <logical_camera_plugin/logicalImage.h>
#include <tf/transform_datatypes.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <geometry_msgs/Pose2D.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <angles/angles.h>
#include <map>


using namespace std;

geometry_msgs::Pose2D TreasureRobotPose;

struct treasureChest{

  map <string, pair<float, float> > chest;

  treasureChest(){}

void addTreasure(string id, float x, float y){
    if(chest.count(id)){
      ROS_INFO_STREAM("We already got that treasure my dude");
    }
    else{

      chest.insert(make_pair(id, make_pair (x,y)));

    }
  }

};

treasureChest tc;

void sawTreasure(const logical_camera_plugin::logicalImage msg) {


  geometry_msgs::Quaternion q;
  q.x = msg.pose_rot_x;
  q.y = msg.pose_rot_y;
  q.z = msg.pose_rot_z;
  q.w = msg.pose_rot_w;

  double roll, pitch, yaw;
  tf::Matrix3x3(q).getRPY(roll, pitch, yaw);

  ROS_INFO_STREAM(yaw);

}

int main(int argc, char** argv) {
  ros::init(argc, argv, "detectObjects");
  ros::NodeHandle nh;

  ros::Rate rate(20);

  ros::Subscriber sub = nh.subscribe<logical_camera_plugin::logicalImage>("/objectsDetected", 1000, sawTreasure);
//ros::Subscriber subAMCL = nh.subscribe("/amcl_pose", 1000, &amclMessageReceived);


  while (ros::ok()) {
    ros::spinOnce();
  }

}
