// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#ifndef ROBOTCONTAINER_H
#define ROBOTCONTAINER_H

#include "Headers/Headers.h"
#include "Subsystems/Drivetrain/DriveSubsystem.h"
#include "Subsystems/Mechanism/NoteMechanism.h"
#include "Control/Autonomous.h"

class RobotContainer {
	public:
		RobotContainer();

		frc2::Command* GetAutonomousCommand();

	private:

	// Configuration functions
		void ConfigureButtonBindings();
		void ConfigureAutonomousChooser();
		void ConfigureDashboard();
		void ConfigureDefaultCommands();

	// Controllers
		Driver m_driver{TeleoperatedMode::Controller::Ports::Driver};
		Operator m_operator{TeleoperatedMode::Controller::Ports::Operator};

	// Subsystems
		//DriveSubsystem m_drive;
		NoteMechanism m_noteMechanism;

	// Network Tables

	// Cameras

	// Autonomous
		frc::SendableChooser<frc2::Command*> m_chooser;

		// Auto routines
		//frc2::CommandPtr a_test = AutoRoutine::test(&m_drive);
};

#endif  // ROBOTCONTAINER_H