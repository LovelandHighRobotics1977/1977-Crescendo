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
	m_noteMechanism.SetDefaultCommand(frc2::RunCommand( 
		[this] { m_noteMechanism.AngleShooter(false); },
		{&m_noteMechanism}
	));
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
		c_position.AddOption("Amp",1);
		c_position.AddOption("Center",2);
		c_position.AddOption("Source",3);
		frc::Shuffleboard::GetTab("Autonomous").Add(c_position);
		// Type { Falls back to basic if no auto exists }
		c_type.AddOption("Basic",1);
		c_type.AddOption("Run",2);
		c_type.AddOption("Advanced",3);
		c_type.AddOption("Delay",4);
		frc::Shuffleboard::GetTab("Autonomous").Add(c_type);

	// Configure Autonomous Overrides
		// Alliance Override
		c_allianceOverride.SetDefaultOption("--",0);
		c_allianceOverride.AddOption("Red",1);
		c_allianceOverride.AddOption("Blue",2);
		frc::Shuffleboard::GetTab("Autonomous").Add(c_allianceOverride);
		// Score in auto Override
		c_routineOverride.SetDefaultOption("--",0);
		c_routineOverride.AddOption("ONLY RUN",1);
		c_routineOverride.AddOption("ONLY SCORE",2);
		frc::Shuffleboard::GetTab("Autonomous").Add(c_routineOverride);

	// Configure the Master Override
		// Configure the enable toggle
		c_masterOverride.SetDefaultOption("Disabled",false);
		c_masterOverride.AddOption("Enabled",true);
		frc::Shuffleboard::GetTab("Autonomous").Add(c_masterOverride);
		// Configure the master routine selector
		c_masterRoutineSelector.AddOption("OnlyRunNoScore", a_onlyRun.get());
		c_masterRoutineSelector.AddOption("OnlyScoreNoRun", a_onlyScore.get());
	// -------------------------
		c_masterRoutineSelector.AddOption("redCenterBasic", a_redCenterBasic.get());
		c_masterRoutineSelector.AddOption("redCenterRun", a_redCenterRun.get());
		c_masterRoutineSelector.AddOption("redCenterAdvanced", a_redCenterAdvanced.get());

		c_masterRoutineSelector.AddOption("redSourceBasic", a_redSourceBasic.get());
		c_masterRoutineSelector.AddOption("redSourceRun", a_redSourceRun.get()); // Im at the red SOUCE

		c_masterRoutineSelector.AddOption("redAmpBasic", a_redAmpBasic.get());
		c_masterRoutineSelector.AddOption("redAmpRun", a_redAmpRun.get());
	// -------------------------
		c_masterRoutineSelector.AddOption("blueCenterBasic", a_blueCenterBasic.get());
		c_masterRoutineSelector.AddOption("blueCenterRun", a_blueCenterRun.get());
		c_masterRoutineSelector.AddOption("blueCenterAdvanced", a_blueCenterAdvanced.get());
		
		c_masterRoutineSelector.AddOption("blueAmpBasic", a_blueAmpBasic.get());
		c_masterRoutineSelector.AddOption("blueAmpRun", a_blueAmpRun.get());

		c_masterRoutineSelector.AddOption("blueSourceBasic", a_blueSourceBasic.get());
		c_masterRoutineSelector.AddOption("blueSourceRun", a_blueSourceRun.get());
		
		frc::Shuffleboard::GetTab("Autonomous").Add(c_masterRoutineSelector);
}

frc2::Command* RobotContainer::GetAutonomousCommand() {
	if(c_masterOverride.GetSelected()){
		std::cout<<"USING MASTER OVERRIDE"<<std::endl;
		return c_masterRoutineSelector.GetSelected();
	}else if(c_routineOverride.GetSelected()){
		std::cout<<"USING ROUTINE OVERRIDE"<<std::endl; switch(c_routineOverride.GetSelected()){
			case 1: /* Only Run */ std::cout<<"USING ONLY RUN OVERRIDE"<<std::endl; return a_onlyRun.get();
			case 2: /* Only Score */ std::cout<<"USING ONLY SCORE OVERRIDE"<<std::endl; return a_onlyScore.get();
		}
	}else if((frc::DriverStation::GetAlliance() == frc::DriverStation::Alliance::kRed && c_allianceOverride.GetSelected() != 2) || c_allianceOverride.GetSelected() == 1) {
		// RED alliance autonomous
		switch(c_position.GetSelected()){
			case 1: /* Amp */ switch(c_type.GetSelected()){
				case 1: /* Basic */ std::cout<<"RED AMP BASIC"<<std::endl; return a_redAmpBasic.get();
				case 2: /* Run */ std::cout<<"RED AMP RUN"<<std::endl; return a_redAmpRun.get();
				case 3: /* Advanced */ std::cout<<"RED AMP BASIC ( ADVANCED )"<<std::endl; return a_redAmpBasic.get();
				case 4: /* Delay */ std::cout<<"RED AMP BASIC ( DELAY )"<<std::endl; return a_redAmpBasic.get();
			}
			case 2: /* Center */ switch(c_type.GetSelected()){
				case 1: /* Basic */ std::cout<<"RED CENTER BASIC"<<std::endl; return a_redCenterBasic.get();
				case 2: /* Run */ std::cout<<"RED CENTER RUN"<<std::endl; return a_redCenterRun.get();
				case 3: /* Advanced */ std::cout<<"RED CENTER ADVANCED"<<std::endl; return a_redCenterAdvanced.get();
				case 4: /* Delay */ std::cout<<"RED CENTER BASIC ( DELAY )"<<std::endl; return a_redCenterBasic.get();
			}
			case 3: /* Source */ switch(c_type.GetSelected()){
				case 1: /* Basic */ std::cout<<"RED SOURCE BASIC"<<std::endl; return a_redSourceBasic.get();
				case 2: /* Run */ std::cout<<"RED SOURCE RUN"<<std::endl; return a_redSourceRun.get();
				case 3: /* Advanced */ std::cout<<"RED SOURCE BASIC ( ADVANCED )"<<std::endl; return a_redSourceBasic.get();
				case 4: /* Delay */ std::cout<<"RED SOURCE BASIC ( DELAY )"<<std::endl; return a_redSourceBasic.get();
			}
		}
	}else if((frc::DriverStation::GetAlliance() == frc::DriverStation::Alliance::kBlue && c_allianceOverride.GetSelected() != 1) || c_allianceOverride.GetSelected() == 2) {
		// BLUE alliance autonomous
		switch(c_position.GetSelected()){
			case 1: /* Amp */ switch(c_type.GetSelected()){
				case 1: /* Basic */ std::cout<<"BLUE AMP BASIC"<<std::endl; return a_blueAmpBasic.get();
				case 2: /* Run */ std::cout<<"BLUE AMP RUN"<<std::endl; return a_blueAmpRun.get();
				case 3: /* Advanced */ std::cout<<"BLUE AMP BASIC ( ADVANCED )"<<std::endl; return a_blueAmpBasic.get();
				case 4: /* Delay */ std::cout<<"BLUE AMP BASIC ( DELAY )"<<std::endl; return a_blueAmpBasic.get();
			}
			case 2: /* Center */ switch(c_type.GetSelected()){
				case 1: /* Basic */ std::cout<<"BLUE CENTER BASIC"<<std::endl; return a_blueCenterBasic.get();
				case 2: /* Run */ std::cout<<"BLUE CENTER RUN"<<std::endl; return a_blueCenterRun.get();
				case 3: /* Advanced */ std::cout<<"BLUE CENTER ADVANCED"<<std::endl; return a_blueCenterAdvanced.get();
				case 4: /* Delay */ std::cout<<"BLUE CENTER BASIC ( DELAY )"<<std::endl; return a_blueCenterBasic.get();
			}
			case 3: /* Source */ switch(c_type.GetSelected()){
				case 1: /* Basic */ std::cout<<"BLUE SOURCE BASIC"<<std::endl; return a_blueSourceBasic.get();
				case 2: /* Run */ std::cout<<"BLUE SOURCE RUN"<<std::endl; return a_blueSourceRun.get();
				case 3: /* Advanced */ std::cout<<"BLUE SOURCE BASIC ( ADVANCED )"<<std::endl; return a_blueSourceBasic.get();
				case 4: /* Delay */ std::cout<<"BLUE SOURCE BASIC ( DELAY )"<<std::endl; return a_blueSourceBasic.get();
			}
		}
	}
}

void RobotContainer::ConfigureDashboard() {

	cs::UsbCamera DriveCamera = frc::CameraServer::StartAutomaticCapture(0);

}