// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotContainer.h"
#include "headers/Headers.h"
#include "subsystems/DriveSubsystem.h"

void RobotContainer::ConfigureAutonomousChooser() {

	
	if(frc::DriverStation::GetAlliance() >= 0){
		// Any autonomous routines added here will be available to any alliance
		m_chooser.SetDefaultOption("Only fire a cube", a_fireCubeOnly.get());
	}

	if(frc::DriverStation::GetAlliance() == frc::DriverStation::kRed){
		m_chooser.AddOption("Drive Forward 3 Meters", a_red_driveForward.get());
	}
	if(frc::DriverStation::GetAlliance() == frc::DriverStation::kBlue){

	}
}

void RobotContainer::ConfigureDashboard() {
	#define DASHBOARD frc::Shuffleboard::GetTab("Data")
	#define AUTO_DASHBOARD frc::Shuffleboard::GetTab("Autonomous")
	#define TELE_DASHBOARD frc::Shuffleboard::GetTab("Teleoperated")
	#define DIAGNOSTICS_DASHBOARD frc::Shuffleboard::GetTab("Diagnostics")

	frc::Timer().Restart();

	/*

	r_driveCam = frc::CameraServer::StartAutomaticCapture(0);
	r_driveCam.SetPixelFormat(cs::VideoMode::PixelFormat::kYUYV);
	
	*/

	AUTO_DASHBOARD.Add(m_chooser);

	DIAGNOSTICS_DASHBOARD.Add(PDH::GetInstance()->m_PDH);
	DIAGNOSTICS_DASHBOARD.Add(Field2d::GetInstance()->m_field);

	TELE_DASHBOARD.AddDouble("Time Remaining", [] { return ( 150 - frc::Timer().Get().value() ); });

	TELE_DASHBOARD.AddDouble("Throttle", [this] { return m_driver.throttle; });
}

void RobotContainer::ConfigureDefaultCommands() {
	m_driver.SetDefaultCommand(frc2::RunCommand( [this] { m_driver.update(); } , {&m_driver} ));
	m_operator.SetDefaultCommand(frc2::RunCommand( [this] { m_operator.update(); } , {&m_operator} ));
	m_CubeArm.SetDefaultCommand(frc2::RunCommand( [this] { m_CubeArm.setTarget(m_operator.speed); } , {&m_CubeArm} ));
	m_drive.SetDefaultCommand(frc2::RunCommand( 
		[this] { m_drive.Drive({ 
			m_driver.forward * Drivetrain::Movement::Maximum::Linear::Velocity, 
			m_driver.strafe * Drivetrain::Movement::Maximum::Linear::Velocity, 
			m_driver.rotate * Drivetrain::Movement::Maximum::Angular::Velocity, 
			m_driver.field_relative,
			Drivetrain::Movement::Rotate::Around::Center });}, 
		{&m_drive}
	));
}

void RobotContainer::ConfigureButtonBindings() {
	frc2::Trigger resetGyro([this] { return m_driver.gyro_reset; });
	resetGyro.OnTrue(frc2::InstantCommand( [] {Gyro::GetInstance()->ahrs.Reset();} ).ToPtr());

	frc2::Trigger bullshitMode([this] { return m_driver.coast_mode_toggle; });
	bullshitMode.OnTrue(frc2::InstantCommand( [this] { m_drive.SetNeutralMode(NeutralMode::Coast); }).ToPtr());
	bullshitMode.OnFalse(frc2::InstantCommand( [this] { m_drive.SetNeutralMode(NeutralMode::Brake); }).ToPtr());
	
	frc2::Trigger shootEnable([this] { return (m_operator.shootEnable); });
	shootEnable.WhileTrue(m_CubeArm.ShootCube().ToPtr());

	frc2::Trigger pickupEnable([this] { return (m_operator.pickupEnable); });
	pickupEnable.WhileTrue(m_CubeArm.PickupCube().ToPtr());

	frc2::Trigger raiseArm([this] { return m_operator.angle_up; });
	raiseArm.WhileTrue(m_CubeArm.RaiseArm().ToPtr());

	frc2::Trigger lowerArm([this] { return m_operator.angle_down; });
	lowerArm.WhileTrue(m_CubeArm.LowerArm().ToPtr());
}

RobotContainer::RobotContainer() {
	ConfigureAutonomousChooser();
	ConfigureDashboard();
	ConfigureButtonBindings();
	ConfigureDefaultCommands();
}

frc2::Command* RobotContainer::GetAutonomousCommand() { 
	return m_chooser.GetSelected(); 
}