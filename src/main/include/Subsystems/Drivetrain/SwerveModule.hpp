#ifndef _SUBSYSTEM_SWERVE_MODULE_H
#define _SUBSYSTEM_SWERVE_MODULE_H

#include "headers/Headers.hpp"

class SwerveModule {
 public:
	SwerveModule(int driveMotorID, int angleMotorID, int angleEncoderID, units::turn_t magnetOffset);

	frc::SwerveModuleState GetState();

	frc::SwerveModulePosition GetPosition();

	void SetDesiredState(const frc::SwerveModuleState& state);

 private:

	ctre::phoenix6::hardware::TalonFX m_driveMotor;
	ctre::phoenix6::configs::TalonFXConfiguration driveMotorConfig{};
	ctre::phoenix6::configs::Slot0Configs driveMotorPID{};
	swerveMotorOutput driveOutput;

	ctre::phoenix6::hardware::TalonFX m_angleMotor;
	ctre::phoenix6::configs::TalonFXConfiguration angleMotorConfig{};
	ctre::phoenix6::configs::Slot0Configs angleMotorPID{};
	swerveMotorOutput angleOutput;

	ctre::phoenix6::hardware::CANcoder m_angleEncoder;
	ctre::phoenix6::configs::MagnetSensorConfigs angleEncoderConfig{};

	frc::SwerveModuleState state;
};

#endif	// _SUBSYSTEM_SWERVE_MODULE_H