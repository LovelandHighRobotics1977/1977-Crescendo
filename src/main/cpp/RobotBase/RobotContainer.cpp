// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotBase/RobotContainer.hpp"
#include "headers/Headers.hpp"

RobotContainer::RobotContainer() {
	ConfigureAutonomousChooser();
	ConfigureDashboard();
	ConfigureButtonBindings();
	ConfigureDefaultCommands();
}

void RobotContainer::ConfigureDefaultCommands() {
	m_driver.SetDefaultCommand(frc2::RunCommand( [this] { m_driver.update(); } , {&m_driver} ));
	m_operator.SetDefaultCommand(frc2::RunCommand( [this] { m_operator.update(); } , {&m_operator} ));
	m_drive.SetDefaultCommand(frc2::RunCommand( 
		[this] { m_drive.Drive({ 
			m_driver.forward * Drivetrain::Movement::Maximum::Linear::Velocity, 
			m_driver.strafe * Drivetrain::Movement::Maximum::Linear::Velocity, 
			m_driver.rotate * Drivetrain::Movement::Maximum::Angular::Velocity, 
			m_driver.field_relative,
			Drivetrain::Movement::Rotate::Around::Center,
			m_driver.coast_mode_toggle });}, 
		{&m_drive}
	));
	/*m_noteMechanism.SetDefaultCommand(frc2::RunCommand( 
		[this] { m_noteMechanism.AngleShooter(); },
		{&m_noteMechanism}
	));*/
}

void RobotContainer::ConfigureButtonBindings() {
	frc2::Trigger resetGyro([this] { return m_driver.gyro_reset; });
	resetGyro.OnTrue(frc2::InstantCommand( [] {Gyro::GetInstance()->ahrs.Reset();} ).ToPtr());

	frc2::Trigger pickupNote([this] { return m_operator.pickupNote; });
	pickupNote.WhileTrue(m_noteMechanism.PickupNote().ToPtr());

	frc2::Trigger reverseNote([this] { return m_operator.reverseNote; });
	reverseNote.WhileTrue(m_noteMechanism.ReverseNote().ToPtr());

	frc2::Trigger shootNote([this] { return m_operator.shootNote; });
	shootNote.OnTrue(m_noteMechanism.ShootNote().ToPtr());

	frc2::Trigger openClimber([this] { return m_operator.openClimber; });
	openClimber.WhileTrue(m_climber.OpenClimber().ToPtr());

	frc2::Trigger closeClimber([this] { return m_operator.closeClimber; });
	closeClimber.WhileTrue(m_climber.CloseClimber().ToPtr());
}

void RobotContainer::ConfigureAutonomousChooser() {

	// Configure Autonomous Selection
		// Position
		c_position.AddOption("Left",1);
		c_position.AddOption("Center",2);
		c_position.AddOption("Right",3);
		frc::Shuffleboard::GetTab("Autonomous").Add(c_position);
		// Type { Falls back to basic if no auto exists }
		c_type.AddOption("Basic",1);
		c_type.AddOption("Run",2);
		c_type.AddOption("Advanced",3);
		frc::Shuffleboard::GetTab("Autonomous").Add(c_type);

	// Configure Autonomous Overrides
		// Alliance Override
		c_allianceOverride.SetDefaultOption("--",0);
		c_allianceOverride.AddOption("Red",1);
		c_allianceOverride.AddOption("Blue",2);
		frc::Shuffleboard::GetTab("Autonomous").Add(c_allianceOverride);
		// Score in auto Override
		c_noScoreJustRun.SetDefaultOption("--",false);
		c_noScoreJustRun.AddOption("Run w/ no score",true);
		frc::Shuffleboard::GetTab("Autonomous").Add(c_noScoreJustRun);

	// Configure the Master Override
		// Configure the enable toggle
		c_masterOverride.SetDefaultOption("Disabled",false);
		c_masterOverride.AddOption("Enabled",true);
		frc::Shuffleboard::GetTab("Autonomous").Add(c_masterOverride);
		// Configure the master routine selector
		c_masterRoutineSelector.AddOption("runNoScore", a_runNoScore.get());
		c_masterRoutineSelector.AddOption("redZone8", a_redZone8.get());
	// -------------------------
		c_masterRoutineSelector.AddOption("redCenterBasic1822", a_redCenterBasic1822.get());
		c_masterRoutineSelector.AddOption("redRightBasic1822", a_redRightBasic1822.get());
	// -------------------------
		c_masterRoutineSelector.AddOption("redCenterBasic", a_redCenterBasic.get());
		c_masterRoutineSelector.AddOption("redCenterRun", a_redCenterRun.get());
		c_masterRoutineSelector.AddOption("redCenterAdvanced", a_redCenterAdvanced.get());

		c_masterRoutineSelector.AddOption("redRightBasic", a_redRightBasic.get());
		c_masterRoutineSelector.AddOption("redRightRun", a_redRightRun.get());

		c_masterRoutineSelector.AddOption("redLeftBasic", a_redLeftBasic.get());
		c_masterRoutineSelector.AddOption("redLeftRun", a_redLeftRun.get());
	// -------------------------
		c_masterRoutineSelector.AddOption("blueCenterBasic", a_blueCenterBasic.get());
		c_masterRoutineSelector.AddOption("blueCenterRun", a_blueCenterRun.get());
		c_masterRoutineSelector.AddOption("blueCenterAdvanced", a_blueCenterAdvanced.get());
		
		c_masterRoutineSelector.AddOption("blueRightBasic", a_blueRightBasic.get());
		c_masterRoutineSelector.AddOption("blueRightRun", a_blueRightRun.get());

		c_masterRoutineSelector.AddOption("blueLeftBasic", a_blueLeftBasic.get());
		c_masterRoutineSelector.AddOption("blueLeftRun", a_blueLeftRun.get());
		
		frc::Shuffleboard::GetTab("Autonomous").Add(c_masterRoutineSelector);
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
	if(c_masterOverride.GetSelected()){
		std::cout<<"USING MASTER OVERRIDE"<<std::endl;
		return c_masterRoutineSelector.GetSelected();
	}else if(c_noScoreJustRun.GetSelected()){
		std::cout<<"USING SCORE OVERRIDE"<<std::endl;
		return a_runNoScore.get();
	}else if((frc::DriverStation::GetAlliance() == frc::DriverStation::Alliance::kRed && c_allianceOverride.GetSelected() != 2) || c_allianceOverride.GetSelected() == 1) {
		// RED alliance autonomous
		switch(c_position.GetSelected()){
			case 1: /* Left */ switch(c_type.GetSelected()){
				case 1: /* Basic */ std::cout<<"RED LEFT BASIC"<<std::endl; return a_redLeftBasic.get();
				case 2: /* Run */ std::cout<<"RED LEFT RUN"<<std::endl; return a_redLeftRun.get();
				case 3: /* Advanced */ std::cout<<"RED LEFT BASIC ( ADVANCED )"<<std::endl; return a_redLeftBasic.get();
			}
			case 2: /* Center */ switch(c_type.GetSelected()){
				case 1: /* Basic */ std::cout<<"RED CENTER BASIC"<<std::endl; return a_redCenterBasic.get();
				case 2: /* Run */ std::cout<<"RED CENTER RUN"<<std::endl; return a_redCenterRun.get();
				case 3: /* Advanced */ std::cout<<"RED CENTER ADVANCED"<<std::endl; return a_redCenterAdvanced.get();
			}
			case 3: /* Right */ switch(c_type.GetSelected()){
				case 1: /* Basic */ std::cout<<"RED RIGHT BASIC"<<std::endl; return a_redRightBasic.get();
				case 2: /* Run */ std::cout<<"RED RIGHT RUN"<<std::endl; return a_redRightRun.get();
				case 3: /* Advanced */ std::cout<<"RED RIGHT BASIC ( ADVANCED )"<<std::endl; return a_redRightBasic.get();
			}
		}
	}else if((frc::DriverStation::GetAlliance() == frc::DriverStation::Alliance::kBlue && c_allianceOverride.GetSelected() != 1) || c_allianceOverride.GetSelected() == 2) {
		// BLUE alliance autonomous
		switch(c_position.GetSelected()){
			case 1: /* Left */ switch(c_type.GetSelected()){
				case 1: /* Basic */ std::cout<<"BLUE LEFT BASIC"<<std::endl; return a_blueLeftBasic.get();
				case 2: /* Run */ std::cout<<"BLUE LEFT RUN"<<std::endl; return a_blueLeftRun.get();
				case 3: /* Advanced */ std::cout<<"BLUE LEFT BASIC ( ADVANCED )"<<std::endl; return a_blueLeftBasic.get();
			}
			case 2: /* Center */ switch(c_type.GetSelected()){
				case 1: /* Basic */ std::cout<<"BLUE CENTER BASIC"<<std::endl; return a_blueCenterBasic.get();
				case 2: /* Run */ std::cout<<"BLUE CENTER RUN"<<std::endl; return a_blueCenterRun.get();
				case 3: /* Advanced */ std::cout<<"BLUE CENTER ADVANCED"<<std::endl; return a_blueCenterAdvanced.get();
			}
			case 3: /* Right */ switch(c_type.GetSelected()){
				case 1: /* Basic */ std::cout<<"BLUE RIGHT BASIC"<<std::endl; return a_blueRightBasic.get();
				case 2: /* Run */ std::cout<<"BLUE RIGHT RUN"<<std::endl; return a_blueRightRun.get();
				case 3: /* Advanced */ std::cout<<"BLUE RIGHT BASIC ( ADVANCED )"<<std::endl; return a_blueRightBasic.get();
			}
		}
	}
}

void RobotContainer::ConfigureDashboard() {

	cs::UsbCamera DriveCamera = frc::CameraServer::StartAutomaticCapture(0);

}