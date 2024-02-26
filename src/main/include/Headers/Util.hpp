#ifndef _UTIL_H
#define _UTIL_H

#include "Libraries.hpp"

/**
 * Data for driving the robot
 * @param forward Forward movement of the robot in meters/sec.
 * @param strafe Sideways movement of the robot in meters/sec.
 * @param rotate Rotational movement of the robot in degrees/sec
 * @param fieldRelative Is the robot being driven field oriented?
 * @param centerOfRotation Robot center of rotation.
 * @param targetAprilTag Rotate towards the nearest april tag
*/
struct DriveData{
	units::meters_per_second_t forward = 0_mps;
	units::meters_per_second_t strafe = 0_mps;
	units::angular_velocity::degrees_per_second_t rotate = 0_deg_per_s;
	bool fieldRelative = true;
	frc::Translation2d centerOfRotation = frc::Translation2d{0_in,0_in};
	bool targetAprilTag = false;
};

/**
 * Data for updating and resetting odometry
 * @param angle
 * @param rearLeft_Position 
 * @param frontLeft_Position 
 * @param frontRight_Position 
 * @param rearRight_Position 
*/
struct OdometryData{
	frc::Rotation2d angle;
	std::array<frc::SwerveModulePosition,4> positions;
};

struct swerveMotorOutput {
	units::degree_t RawAngle;
	double RawVelocity;
	double PID;
};





#endif // _UTIL_H