#include "Visitor.h"

class Doctor : public Visitor
{
	protected:
		bool healResident;
		int health;
		int boredom;
		int hunger;
		
		//goal pose and orientation
		double goal_x;
		double goal_y;
		double px;
		double py;
		double goal_angle;

		bool running;
		bool isSet;

		//current pose and orientation of the robot
		double cur_angle;

		int cc; //current_checkpoint = 0;

		bool is_called; 

		std::pair<double,bool> goal_pair;
		std::pair<double, double> ret;	


	public:
		void StageOdom_callback(nav_msgs::Odometry msg);
		void StageLaser_callback(sensor_msgs::LaserScan msg);
		int run(int argc, char **argv);

		double calc_goal_angle(double goal_x, double goal_y, double cur_angle, double px, double py);
		std::pair<double, double> move(double goal_x, double goal_y, double cur_angle, double goal_angle, double px, double py);
		void randomCheckpointCallback(const ros::TimerEvent&);

		void residentStatusCallback(se306_project1::ResidentMsg msg);
		void medicationCallback(const ros::TimerEvent&);

		// Restores health of the resident
		//void restore_Health()
		
};
