#ifndef _ROBOT_CONTAINER_H
#define _ROBOT_CONTAINER_H

#include "Headers/Headers.hpp"
#include "Control/Autonomous.hpp"

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
		Climber m_climber;

	// Network Tables

		nt::NetworkTableInstance m_networkTable = nt::NetworkTableInstance::GetDefault();

	// Cameras
		

	// Autonomous
		frc::SendableChooser<frc2::Command*> m_chooser;

		// Auto routines
		//1977 auto routines red
		frc2::CommandPtr a_redCenterBasic = AutoRoutine::redCenterBasic(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_redCenterRun = AutoRoutine::redCenterRun(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_redCenterAdvanced = AutoRoutine::redCenterAdvanced(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_redRightBasic = AutoRoutine::redRightBasic(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_redLeftBasic = AutoRoutine::redLeftBasic(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_redLeftRun = AutoRoutine::redLeftRun(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_redRightRun = AutoRoutine::redRightRun(&m_drive, &m_noteMechanism);

		//1977auto routines blue

		frc2::CommandPtr a_blueCenterBasic = AutoRoutine::blueCenterBasic(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_blueCenterRun = AutoRoutine::blueCenterRun(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_blueCenterAdvanced = AutoRoutine::blueCenterAdvanced(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_blueRightBasic = AutoRoutine::blueRightBasic(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_blueLeftBasic = AutoRoutine::blueLeftBasic(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_blueRightRun = AutoRoutine::blueRightRun(&m_drive, &m_noteMechanism);

		//1822 auto routines red

		frc2::CommandPtr a_redCenterBasic1822 = AutoRoutine::redCenterBasic1822(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_redRightBasic1822 = AutoRoutine::redRightBasic1822(&m_drive, &m_noteMechanism);
		frc2::CommandPtr a_redZone8 = AutoRoutine::redZone8(&m_drive, &m_noteMechanism);
		//Any bot auto routines
		frc2::CommandPtr a_runNoScore = AutoRoutine::runNoScore(&m_drive, &m_noteMechanism);
};

#endif  // _ROBOT_CONTAINER_H