#include "ros/ros.h"
#include "simple_arm/GoToPosition.h"
#include <std_msgs/Float64.h>

// Global joint publisher variables
ros::Publisher joint1_pub, joint2_pub;

// This function checks and clamps the joint angles to a sage zone
std::vector<float> clamp_at_boundary(float requested_j1, float requested_j2)
{
  // Define clamped joint angles and assign them to the requested node 
  float clamped_j1 = requested_j1;
  float clamped_j2 = requested_j2;

  // Get min and max joint parameters and assign them to their respective variables
  float min_j1, max_j1, min_j2, max_j2;
  // Assign a new node handle since we have no access to the main one
  ros::NodeHandle n2;
  // Get node name
  std::string node_nam = ros::this_node::getName();
  // Get joints min and max parameters
  n2.getParam(node_name + "/min_joint_1_angle", min_j1);
  n2.getParam(node_name + "/max_joint_1_angle", max_j1);
  n2.getParam(node_name + "/min_joint_2_angle", min_j2);
  n2.getParam(node_name + "/max_joint_2_angle", max_j2);

  // Check if joint 1 falls in the safe zone, otherwise clamp it 
  if (requsted_j1 < min_j1 || requsted_j1 > max_j1) {
    clamped_j1 = std::min(std::max(requested_j1, min_j1), max_j1);
    ROS_WARN("j1 is out of bounds, valid range (%1.2f,%1.2f), clamping to %1.2f", min_j1, max_j1, clamped_j1);
  }
  // Check if joint 2 falls in the safe zone, otherwise clamp it 
  if (requsted_j2 < min_j2 || requsted_j2 > max_j2) {
    clamped_j2 = std::min(std::max(requested_j2, min_j2), max_j2);
    ROS_WARN("j2 is out of bounds, valid range (%1.2f,%1.2f), clamping to %1.2f", min_j2, max_j2, clamped_j2);
  }

  // Stored clamped joint angles in a clamped_data vector
  std::vector<float> clamped_data = { clamped_j1, clamped_j2 };

  return clamped_data;
}

// This callback function executes whenever a safe_move service is requested
bool handle_safe_move_request(simple_arm::GoToPosition::Request& req, simple_arm::GoToPosition::Response& res)
{
  ROS_INFO("GoToPositionRequest receiver - j1:%1.2f, j2:%1.2f, (float)req.joint_1, (float)req.joint_2);





}
