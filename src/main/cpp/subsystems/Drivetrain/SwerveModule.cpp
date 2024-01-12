// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "subsystems/Drivetrain/SwerveModule.h"
#include "headers/Headers.h"

SwerveModule::SwerveModule(const int driveMotorID,     const int angleMotorID,       const int angleEncoderID, double magnetOffset)
					  : m_driveMotor{driveMotorID}, m_angleMotor{angleMotorID}, m_angleEncoder{angleEncoderID} {

	driveMotorConfig.Slot0.WithKP(Drivetrain::Swerve::PID::Motor::Drive::P);
	driveMotorConfig.Slot0.WithKI(Drivetrain::Swerve::PID::Motor::Drive::I);
	driveMotorConfig.Slot0.WithKD(Drivetrain::Swerve::PID::Motor::Drive::D);
	driveMotorConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Brake);
	driveMotorConfig.Feedback.WithFeedbackSensorSource(ctre::phoenix6::signals::FeedbackSensorSourceValue::RotorSensor);
	m_driveMotor.GetConfigurator().Apply(driveMotorConfig);

	angleMotorConfig.Slot0.WithKP(Drivetrain::Swerve::PID::Motor::Angle::P);
	angleMotorConfig.Slot0.WithKI(Drivetrain::Swerve::PID::Motor::Angle::I);
	angleMotorConfig.Slot0.WithKD(Drivetrain::Swerve::PID::Motor::Angle::D);
	angleMotorConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Brake);
	angleMotorConfig.Feedback.WithRotorToSensorRatio(Drivetrain::Swerve::Motor::Angle::gear_ratio);
	angleMotorConfig.Feedback.WithSensorToMechanismRatio(1);
	angleMotorConfig.Feedback.WithFusedCANcoder(m_angleEncoder);
	angleMotorConfig.ClosedLoopGeneral.ContinuousWrap = true;
	m_angleMotor.GetConfigurator().Apply(angleMotorConfig);

	angleEncoderConfig.WithMagnetOffset(magnetOffset);
	angleEncoderConfig.WithAbsoluteSensorRange(ctre::phoenix6::signals::AbsoluteSensorRangeValue::Unsigned_0To1);
	m_angleEncoder.GetConfigurator().Apply(angleEncoderConfig);

	m_turningPIDController.EnableContinuousInput(0_deg, 360_deg);
}

frc::SwerveModuleState SwerveModule::GetState() {
	return {
		(m_driveMotor.GetVelocity().GetValue().value() * Drivetrain::Swerve::Motor::Drive::distance_per_rotation)/1_s,
		units::degree_t{m_angleEncoder.GetAbsolutePosition().GetValue()}
	};
}

frc::SwerveModulePosition SwerveModule::GetPosition() {
	return {
		m_driveMotor.GetPosition().GetValue().value() * Drivetrain::Swerve::Motor::Drive::distance_per_rotation,
		units::degree_t{m_angleEncoder.GetAbsolutePosition().GetValue()}
	};
}

void SwerveModule::SetDesiredState(const frc::SwerveModuleState& referenceState, bool usePID) {
	// Optimize the reference state to avoid spinning further than 90 degrees
	state = frc::SwerveModuleState::Optimize(referenceState, units::degree_t{m_angleEncoder.GetAbsolutePosition().GetValue()});

	// Calculate the drive output from the drive PID controller.
	driveOutput.PID = m_drivePIDController.Calculate(((m_driveMotor.GetVelocity().GetValue().value() * Drivetrain::Swerve::Motor::Drive::distance_per_rotation)/1_s).value(), state.speed.value());
	driveOutput.RawVelocity = (state.speed / Drivetrain::Movement::Maximum::Linear::Velocity).value();

	// Calculate the turning motor output from the turning PID controller.
	angleOutput.PID = m_turningPIDController.Calculate(units::degree_t{m_angleEncoder.GetAbsolutePosition().GetValue()}, state.angle.Degrees());
	angleOutput.RawAngle = state.angle.Degrees();
	
	// Send encoder values to the dashboard
	switch(m_angleEncoder.GetDeviceID()){
		case Drivetrain::Swerve::Module::Front::Right::Encoder: frc::SmartDashboard::PutNumber("FR Angle", m_angleEncoder.GetAbsolutePosition().GetValue().value()); break;
		case Drivetrain::Swerve::Module::Rear::Right::Encoder: frc::SmartDashboard::PutNumber("RR Angle", m_angleEncoder.GetAbsolutePosition().GetValue().value()); break;
		case Drivetrain::Swerve::Module::Rear::Left::Encoder: frc::SmartDashboard::PutNumber("RL Angle", m_angleEncoder.GetAbsolutePosition().GetValue().value()); break;
		case Drivetrain::Swerve::Module::Front::Left::Encoder: frc::SmartDashboard::PutNumber("FL Angle", m_angleEncoder.GetAbsolutePosition().GetValue().value()); break;
	}

	// Set the motor outputs.
	
	if(usePID){
		m_driveMotor.Set(driveOutput.PID);
		m_angleMotor.Set(-angleOutput.PID);
	}else{
		m_driveMotor.Set(driveOutput.RawVelocity);
		m_angleMotor.SetPosition(angleOutput.RawAngle);
	}
}