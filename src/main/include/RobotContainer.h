// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#ifndef ROBOTCONTAINER_H
#define ROBOTCONTAINER_H

#include "commands/Autonomous.h"
#include "headers/Headers.h"
#include "subsystems/Drivetrain/DriveSubsystem.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the Robot periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
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
		DriveSubsystem m_drive;

		// Cameras
		cs::UsbCamera r_driveCam;
		cs::UsbCamera r_armCam;
		cs::VideoSink r_camServer;

	// Network Tables

	// Autonomous

		// Routine selector on dashboard
		frc::SendableChooser<frc2::Command*> m_chooser;

		// Auto routines
		frc2::CommandPtr a_test = AutoRoutine::test(&m_drive);
};

#endif  // ROBOTCONTAINER_H