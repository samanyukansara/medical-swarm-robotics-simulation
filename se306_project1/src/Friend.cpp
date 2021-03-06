#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <sensor_msgs/LaserScan.h>
#include <sstream>
#include "math.h"
#include "Friend.h"
#include "se306_project1/ResidentMsg.h"
#include "time_conversion.hpp"

/**
*	@brief Causes the friend to visit the resident, as based on a timer.
*	@param The timer that calls this callback automatically generates a TimerEvent.
*	@param startTimme The hour to start the periodic visits
*	@param endTime The hour to end the periodic visits.
*	@remarks If start time and end time are unnecessary, they can be removed
*/
void Friend::friendsDoneCallback(const ros::TimerEvent&){
	move("Friend1Origin");
}

/**
*	@brief Callback function that unpacks and processes resident status messages.
*	Friend should subscribe to the ResidentMsg topic in order for this callback to be called. ResidentMsg is published by the Resident.
*	@param msg A custom ResidentMsg message that contains information about the resident's current status.
*/
void Friend::delegate(se306_project1::ResidentMsg msg) {

	if (msg.state == "emergency") {
		emergency = true; // required variable if timing/scheduling is done within this class
	}
	if (msg.state == "friends") { // resident state when it needs friends to converse with
		move("Friend1Sofa");
	}
}

/**
*	@brief Main function for the Friend process.
*	Controls node setup and periodic events.
*/
int Friend::run(int argc, char *argv[])
{
	ROS_INFO("move");

	/* -- Initialisation -- */
	
	//You must call ros::init() first of all. ros::init() function needs to see argc and argv. The third argument is the name of the node
	ros::init(argc, argv, "Friend");

	//NodeHandle is the main access point to communicate with ros.
	ros::NodeHandle n;

	ros::Rate loop_rate(10);


	/* -- Publish / Subscribe -- */

	//advertise() function will tell ROS that you want to publish on a given topic_
	//to stage
	ros::Publisher RobotNode_stage_pub = n.advertise<geometry_msgs::Twist>("robot_7/cmd_vel",1000);

	//publish message to Resident once conversation is over
	ros::Publisher friend_pub = n.advertise<std_msgs::String>("visitorConvo",1000);

	//subscribe to listen to messages coming from stage
	ros::Subscriber StageOdo_sub = n.subscribe("robot_7/odom",1000, &Agent::StageOdom_callback, dynamic_cast<Agent*>(this));

	//custom Resident subscriber to "resident/state"
	ros::Subscriber resident_sub = n.subscribe<se306_project1::ResidentMsg>("residentStatus",1000, &Friend::delegate, this);

	// Periodic callback
	int friendsDone = time_conversion::simHoursToRealSecs(11.5);
	ros::Timer friendsDoneTimer = n.createTimer(ros::Duration(friendsDone), &Friend::friendsDoneCallback, this);

	////messages
	//velocity of this RobotNode
	geometry_msgs::Twist RobotNode_cmdvel;


	while (ros::ok())
	{
		//messages to stage
		RobotNode_cmdvel.linear.x = linear_x;
		RobotNode_cmdvel.angular.z = angular_z;
			
		//publish the message
		RobotNode_stage_pub.publish(RobotNode_cmdvel);

		// publish message to Resident once this Visitor has finished conversing

		
		ros::spinOnce();
		loop_rate.sleep();
	}

	return 0;
}
	
/**
*	@brief Redirects to main function (run()) of the node.
*/
int main(int argc, char *argv[]) {
	Friend *a = new Friend();
	a->Friend::run(argc, argv);
}
