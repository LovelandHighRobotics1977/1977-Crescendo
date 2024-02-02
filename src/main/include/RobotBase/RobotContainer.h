#ifndef _ROBOT_CONTAINER_H
#define _ROBOT_CONTAINER_H

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
		DriveSubsystem m_drive;
		NoteMechanism m_noteMechanism;

	// Network Tables

	// Cameras

	// Autonomous
		frc::SendableChooser<frc2::Command*> m_chooser;

		// Auto routines
		frc2::CommandPtr a_test = AutoRoutine::test(&m_drive);
		frc2::CommandPtr a_square = AutoRoutine::square(&m_drive);
};

#endif  // _ROBOT_CONTAINER_H