// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Drivetrain/SwerveModule.h"
#include "headers/Headers.h"

SwerveModule::SwerveModule(const int driveMotorID,     const int angleMotorID,       const int angleEncoderID, units::turn_t magnetOffset)
					  : m_driveMotor{driveMotorID}, m_angleMotor{angleMotorID}, m_angleEncoder{angleEncoderID} {

	driveMotorPID.kS = Drivetrain::Module::Motor::Drive::PID::S;
	driveMotorPID.kV = Drivetrain::Module::Motor::Drive::PID::V;
	driveMotorPID.kA = Drivetrain::Module::Motor::Drive::PID::A;
	driveMotorPID.kP = Drivetrain::Module::Motor::Drive::PID::P;
	driveMotorPID.kI = Drivetrain::Module::Motor::Drive::PID::I;
	driveMotorPID.kD = Drivetrain::Module::Motor::Drive::PID::D;
	driveMotorConfig.WithSlot0(driveMotorPID);
	driveMotorConfig.MotorOutput.Inverted = true;
	driveMotorConfig.MotorOutput.NeutralMode = ctre::phoenix6::signals::NeutralModeValue::Brake;
	driveMotorConfig.Feedback.WithFeedbackSensorSource(ctre::phoenix6::signals::FeedbackSensorSourceValue::RotorSensor);
	m_driveMotor.GetConfigurator().Apply(driveMotorConfig);

	angleMotorPID.kS = Drivetrain::Module::Motor::Angle::PID::S;
	angleMotorPID.kV = Drivetrain::Module::Motor::Angle::PID::V;
	angleMotorPID.kA = Drivetrain::Module::Motor::Angle::PID::A;
	angleMotorPID.kP = Drivetrain::Module::Motor::Angle::PID::P;
	angleMotorPID.kI = Drivetrain::Module::Motor::Angle::PID::I;
	angleMotorPID.kD = Drivetrain::Module::Motor::Angle::PID::D;
	angleMotorConfig.WithSlot0(angleMotorPID);
	angleMotorConfig.MotorOutput.NeutralMode = ctre::phoenix6::signals::NeutralModeValue::Brake;
	angleMotorConfig.Feedback.WithRemoteCANcoder(m_angleEncoder);
	angleMotorConfig.Feedback.SensorToMechanismRatio = 1;
	angleMotorConfig.MotorOutput.Inverted = false;
	angleMotorConfig.ClosedLoopGeneral.ContinuousWrap = true;
	m_angleMotor.GetConfigurator().Apply(angleMotorConfig);

	angleEncoderConfig.MagnetOffset = 1 - magnetOffset.value();
	angleEncoderConfig.AbsoluteSensorRange = ctre::phoenix6::signals::AbsoluteSensorRangeValue::Unsigned_0To1;
	m_angleEncoder.GetConfigurator().Apply(angleEncoderConfig);
}

frc::SwerveModuleState SwerveModule::GetState() {
	return {
		-(m_driveMotor.GetVelocity().GetValue().value() * Drivetrain::Module::Motor::Drive::distance_per_rotation)/1_s,
		units::degree_t{m_angleEncoder.GetAbsolutePosition().GetValue()}
	};
}

frc::SwerveModulePosition SwerveModule::GetPosition() {
	return {
		-m_driveMotor.GetPosition().GetValue().value() * Drivetrain::Module::Motor::Drive::distance_per_rotation,
		units::degree_t{m_angleEncoder.GetAbsolutePosition().GetValue()}
	};
}

void SwerveModule::SetDesiredState(const frc::SwerveModuleState& referenceState) {

	// Optimize the reference state to avoid spinning further than 90 degrees
	state = frc::SwerveModuleState::Optimize(referenceState, units::degree_t{m_angleEncoder.GetAbsolutePosition().GetValue()});
	
	// Set the motor outputs.
	m_angleMotor.SetControl(ctre::phoenix6::controls::PositionDutyCycle{units::turn_t{state.angle.Degrees()}});
	m_driveMotor.Set((state.speed / Drivetrain::Movement::Maximum::Linear::Velocity).value());
}