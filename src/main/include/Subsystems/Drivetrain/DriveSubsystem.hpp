#ifndef _SUBSYSTEM_DRIVE_H
#define _SUBSYSTEM_DRIVE_H

#include "headers/Headers.hpp"
#include "subsystems/Drivetrain/SwerveModule.hpp"

class DriveSubsystem : public frc2::SubsystemBase {
public:
	DriveSubsystem();

	void Periodic() override;

	/**
	 * Drives the robot at given x, y and theta speeds. Speeds range from [-1, 1]
	 * and the linear speeds have no effect on the angular speed.
	 *
	 * @param forward        Speed of the robot in the x direction
	 *                      (forward/backwards).
	 * @param strafe        Speed of the robot in the y direction (sideways).
	 * @param rotate           Angular rate of the robot.
	 * @param fieldRelative Whether the provided x and y speeds are relative to
	 *                      the field.
	 * @param centerOfRotation Center of the robot's rotation ( translation 2d )
	 * @param targetAprilTag Rotate towards the nearest april tag
	 */
	void Drive(DriveData data);
	void SetModuleStates(wpi::array<frc::SwerveModuleState, 4> desiredStates);
	frc2::SequentialCommandGroup ZeroOdometry(frc::Pose2d pose);

	frc::Rotation2d GetHeading();
	frc::Pose2d GetPose();

	frc::SwerveDriveKinematics<4> DriveKinematics{
		frc::Translation2d{Drivetrain::Module::Front::Left::Location},
		frc::Translation2d{Drivetrain::Module::Front::Right::Location},
		frc::Translation2d{Drivetrain::Module::Rear::Left::Location},
		frc::Translation2d{Drivetrain::Module::Rear::Right::Location}
	};

private:

	void ResetOdometry(frc::Pose2d pose);

	SwerveModule m_frontLeft;
	SwerveModule m_frontRight;
	SwerveModule m_rearLeft;
	SwerveModule m_rearRight;

	frc::ChassisSpeeds fieldRelativeSpeeds;
	frc::ChassisSpeeds robotRelativeSpeeds;

	Gyro* gyro = Gyro::GetInstance();

	frc::SwerveDriveOdometry<4> m_odometry;
};

#endif // _SUBSYSTEM_DRIVE_H