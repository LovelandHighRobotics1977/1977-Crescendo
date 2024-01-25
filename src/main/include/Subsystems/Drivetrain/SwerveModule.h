// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#ifndef _SUBSYSTEM_SWERVE_MODULE_H
#define _SUBSYSTEM_SWERVE_MODULE_H

#include "headers/Headers.h"

class SwerveModule {
 public:
	SwerveModule(int driveMotorID, int angleMotorID, int angleEncoderID, double magnetOffset);

	frc::SwerveModuleState GetState();

	frc::SwerveModulePosition GetPosition();

	void SetDesiredState(const frc::SwerveModuleState& state, bool Teleop = true);

 private:

	ctre::phoenix6::hardware::TalonFX m_driveMotor;
	ctre::phoenix6::configs::TalonFXConfiguration driveMotorConfig{};
	swerveMotorOutput driveOutput;
	frc::PIDController m_drivePIDController{
		Drivetrain::Module::Motor::Drive::PID::Controller::P, 
		Drivetrain::Module::Motor::Drive::PID::Controller::I,
		Drivetrain::Module::Motor::Drive::PID::Controller::D
	};

	ctre::phoenix6::hardware::TalonFX m_angleMotor;
	ctre::phoenix6::configs::TalonFXConfiguration angleMotorConfig{};
	swerveMotorOutput angleOutput;
	frc::ProfiledPIDController<units::degrees> m_turningPIDController{
		Drivetrain::Module::Motor::Angle::PID::Controller::P, 
		Drivetrain::Module::Motor::Angle::PID::Controller::I,
		Drivetrain::Module::Motor::Angle::PID::Controller::D,
		{Drivetrain::Movement::Maximum::Angular::Velocity*10, Drivetrain::Movement::Maximum::Angular::Acceleration*10}
	};

	ctre::phoenix6::hardware::CANcoder m_angleEncoder;
	ctre::phoenix6::configs::MagnetSensorConfigs angleEncoderConfig{};

	frc::SwerveModuleState state;
};

#endif	// _SUBSYSTEM_SWERVE_MODULE_H