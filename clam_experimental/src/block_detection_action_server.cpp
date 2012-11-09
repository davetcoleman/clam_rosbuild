#include <ros/ros.h>
#include <sensor_msgs/PointCloud2.h>

class BlockDetectionServer
{
private:
    
  ros::NodeHandle nh_;

  ros::Subscriber sub_;

  public:
  BlockDetectionServer(const std::string name) : 
    nh_("~")
  {
    // Load parameters from the server.
    
    std::cout << "BLOCK DETECTION ACTION SERVER" << std::endl;
    
    // Subscribe to point cloud
    std::cout << "PC Subscribed" << std::endl;
    sub_ = nh_.subscribe("/camera/depth_registered/points", 1, &BlockDetectionServer::cloudCb, this);
  }

  void cloudCb ( const sensor_msgs::PointCloud2ConstPtr& msg )
  {
    ROS_INFO("CloudCB");

    std::cout << "cloudCB" << std::endl;
  }

};

int main(int argc, char** argv)
{
  ros::init(argc, argv, "block_detection_action_server");

  BlockDetectionServer server("block_detection");
  ros::spin();

  return 0;
}


