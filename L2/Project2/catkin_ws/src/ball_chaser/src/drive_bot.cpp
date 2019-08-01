#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"

// ROS::Publisher motor command
ros::Publisher motor_command_publisher;

bool handle_driver_request(ball_chaser::DriveToTarget::Request& req, ball_chaser::DriveToTarget::Response& res)
{
  ROS_INFO("DriveToTargetRequest receiver - linear x: %1.2f, angular z: %1.2f", (float)req.linear_x, (float)req.angular_z);
  
  // Create a motor_command object of type geometry_msgs
  geometry_msgs::Twist motor_command;
  
  // Set wheel velocities
  motor_command.linear.x = req.linear_x;
  motor_command.angular.z = req.angular_z;

  // Publish angle command to drive the robot
  motor_command_publisher.publish(motor_command);

  res.msg_feedback = "Velocities for wheel - linear x: " + std::to_string(req.linear_x) + " angular z: " + std::to_string(req.angular_z);

  ROS_INFO_STRAM(res.msg);
  return true;


}


int main(int argc,char** argv)
{
  //Initialize ROS node
  ros::init(argc, argv, "drive_robot");

  // Create ROS handle object
  ros::NodeHandle n;

  // Inform ROS master that we will be publishing a message of type geometry::msgs::Twist on the robot actuating topic with a queue size 10
  motor_command_publisher = n.advertise<geometry_msgs::Twist>("cmd/vel", 10);

  // Define a driver service 
  ros::ServiceServer service = n.advertiseService("/ball_chaser/robot_driver", handle_driver_request);
  ROS_INFO("Robot is ready to move, give move request ...");

  // Handle ROS communication events
  ros::spin();
  
  return 0;

}
