// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Subsystems/Drivetrain/DriveSubsystem.hpp"
#include "Headers/Headers.hpp"

DriveSubsystem::DriveSubsystem()
   :m_frontLeft{Drivetrain::Module::Front::Left::Drive,
				Drivetrain::Module::Front::Left::Angle,
				Drivetrain::Module::Front::Left::Encoder,
				Drivetrain::Module::Front::Left::MagnetOffset,},

	m_frontRight{Drivetrain::Module::Front::Right::Drive,
				 Drivetrain::Module::Front::Right::Angle,
				 Drivetrain::Module::Front::Right::Encoder,
				 Drivetrain::Module::Front::Right::MagnetOffset,},

	m_rearLeft{Drivetrain::Module::Rear::Left::Drive,
			   Drivetrain::Module::Rear::Left::Angle,
			   Drivetrain::Module::Rear::Left::Encoder,
			   Drivetrain::Module::Rear::Left::MagnetOffset,},

	m_rearRight{Drivetrain::Module::Rear::Right::Drive,
				Drivetrain::Module::Rear::Right::Angle,
				Drivetrain::Module::Rear::Right::Encoder,
				Drivetrain::Module::Rear::Right::MagnetOffset,},

	m_odometry{DriveKinematics,
				DriveSubsystem::GetHeading(),
				{m_frontLeft.GetPosition(), m_frontRight.GetPosition(),
				m_rearLeft.GetPosition(), m_rearRight.GetPosition()},
				frc::Pose2d{}} {}

void DriveSubsystem::Periodic() {
	OdometryData data;

	data.angle = DriveSubsystem::GetHeading();

	data.positions[0] = m_frontLeft.GetPosition();
	data.positions[1] = m_frontRight.GetPosition();
	data.positions[2] = m_rearLeft.GetPosition();
	data.positions[3] = m_rearRight.GetPosition();

	m_odometry.Update(data.angle, data.positions);

	Field2d::GetInstance()->m_field.SetRobotPose(m_odometry.GetPose());
}

void DriveSubsystem::Drive(DriveData data) {
	if(data.targetAprilTag){
		fieldRelativeSpeeds = frc::ChassisSpeeds::FromFieldRelativeSpeeds(frc::ChassisSpeeds{data.forward, -data.strafe, -2.5_deg_per_s * nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tx",0.0)}, DriveSubsystem::GetHeading());
	}else{
		fieldRelativeSpeeds = frc::ChassisSpeeds::FromFieldRelativeSpeeds(frc::ChassisSpeeds{data.forward, -data.strafe, data.rotate}, DriveSubsystem::GetHeading());
		robotRelativeSpeeds = frc::ChassisSpeeds{data.forward, -data.strafe, data.rotate};
	}

	auto chosenSpeeds = data.fieldRelative ? fieldRelativeSpeeds : robotRelativeSpeeds;

	auto states = DriveKinematics.ToSwerveModuleStates(chosenSpeeds, data.centerOfRotation);

	DriveKinematics.DesaturateWheelSpeeds(&states, TeleoperatedMode::Parameter::Linear::Velocity);

	auto [fl, fr, rl, rr] = states;
	
	m_frontLeft.SetDesiredState(fl);
	m_frontRight.SetDesiredState(fr);
	m_rearLeft.SetDesiredState(rl);
	m_rearRight.SetDesiredState(rr);

}

void DriveSubsystem::SetModuleStates(wpi::array<frc::SwerveModuleState, 4> desiredStates) {

	DriveKinematics.DesaturateWheelSpeeds(&desiredStates, AutonomousMode::Parameter::Linear::Velocity);

	m_frontLeft.SetDesiredState(desiredStates[0]);
	m_frontRight.SetDesiredState(desiredStates[1]);
	m_rearLeft.SetDesiredState(desiredStates[2]);
	m_rearRight.SetDesiredState(desiredStates[3]);
}

frc::Rotation2d DriveSubsystem::GetHeading(){
	switch(frc::DriverStation::GetAlliance().value()){
		case frc::DriverStation::kRed:
			return units::degree_t{-Gyro::GetInstance()->ahrs.GetYaw()};
			break;

		case frc::DriverStation::kBlue:
			return units::degree_t{180 - Gyro::GetInstance()->ahrs.GetYaw()};
			break;

		default:
			return units::degree_t{180 - Gyro::GetInstance()->ahrs.GetYaw()};
			break;
	}
}

frc2::SequentialCommandGroup DriveSubsystem::ZeroOdometry(frc::Pose2d pose) {
	return frc2::SequentialCommandGroup(
		frc2::InstantCommand( [this] {Gyro::GetInstance()->ahrs.Reset();} ),
		frc2::InstantCommand( [this, pose] { DriveSubsystem::ResetOdometry(pose); } )
	);
}

frc::Pose2d DriveSubsystem::GetPose() {
	return m_odometry.GetPose();
}

void DriveSubsystem::ResetOdometry(frc::Pose2d pose) {
	OdometryData data;

	data.angle = DriveSubsystem::GetHeading();

	data.positions[0] = m_frontLeft.GetPosition();
	data.positions[1] = m_frontRight.GetPosition();
	data.positions[2] = m_rearLeft.GetPosition();
	data.positions[3] = m_rearRight.GetPosition();

	m_odometry.ResetPosition(data.angle, data.positions, pose);
}