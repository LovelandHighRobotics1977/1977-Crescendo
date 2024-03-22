#ifndef _ROBOT_CONTAINER_H
#define _ROBOT_CONTAINER_H

#include "Headers/Headers.hpp"
#include "Control/Autonomous.hpp"

class RobotContainer {
	public:
		RobotContainer();

		frc2::Command* GetAutonomousCommand();
		void ConfigureAutonomousChooser();

	private:

	// Configuration functions
		void ConfigureButtonBindings();
		void ConfigureDashboard();
		void ConfigureDefaultCommands();

	// Controllers
		Driver m_driver{TeleoperatedMode::Controller::Ports::Driver};
		Operator m_operator{TeleoperatedMode::Controller::Ports::Operator};

	// Subsystems
		DriveSubsystem m_drive;
		NoteMechanism m_noteMechanism;
		Climber m_climber;

	// Network Tables

		nt::NetworkTableInstance m_networkTable = nt::NetworkTableInstance::GetDefault();

	// Cameras
		

	// Autonomous
		frc::SendableChooser<int> c_position;
		frc::SendableChooser<int> c_type;
		frc::SendableChooser<int> c_allianceOverride;
		frc::SendableChooser<int> c_routineOverride;
		frc::SendableChooser<bool> c_masterOverride;
		frc::SendableChooser<frc2::Command*> c_masterRoutineSelector;

		// Auto routines RED
		frc2::CommandPtr a_redCenterBasic = AutoRoutine::redCenterBasic(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_redCenterRun = AutoRoutine::redCenterRun(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_redCenterAdvanced = AutoRoutine::redCenterAdvanced(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_redSourceBasic = AutoRoutine::redSourceBasic(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_redSourceRun = AutoRoutine::redSourceRun(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_redAmpBasic = AutoRoutine::redAmpBasic(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_redAmpRun = AutoRoutine::redAmpRun(&m_drive, &m_noteMechanism);

		// Auto routines BLUE
		frc2::CommandPtr a_blueCenterBasic = AutoRoutine::blueCenterBasic(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_blueCenterRun = AutoRoutine::blueCenterRun(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_blueCenterAdvanced = AutoRoutine::blueCenterAdvanced(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_blueAmpBasic = AutoRoutine::blueAmpBasic(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_blueAmpRun = AutoRoutine::blueAmpRun(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_blueSourceBasic = AutoRoutine::blueSourceBasic(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_blueSourceRun = AutoRoutine::blueSourceRun(&m_drive, &m_noteMechanism);

		// Auto routines ANY
		frc2::CommandPtr a_onlyRun = AutoRoutine::onlyRun(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_onlyScore = AutoRoutine::onlyScore(&m_drive, &m_noteMechanism);
};

#endif  // _ROBOT_CONTAINER_H