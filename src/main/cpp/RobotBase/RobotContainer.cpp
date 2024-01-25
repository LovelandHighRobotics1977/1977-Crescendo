// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "RobotBase/RobotContainer.h"
#include "headers/Headers.h"

RobotContainer::RobotContainer() {
	ConfigureAutonomousChooser();
	ConfigureDashboard();
	ConfigureButtonBindings();
	ConfigureDefaultCommands();
}

void RobotContainer::ConfigureDefaultCommands() {
	m_driver.SetDefaultCommand(frc2::RunCommand( [this] { m_driver.update(); } , {&m_driver} ));
	m_operator.SetDefaultCommand(frc2::RunCommand( [this] { m_operator.update(); } , {&m_operator} ));
	/*
	m_drive.SetDefaultCommand(frc2::RunCommand( 
		[this] { m_drive.Drive({ 
			m_driver.forward * Drivetrain::Movement::Maximum::Linear::Velocity, 
			m_driver.strafe * Drivetrain::Movement::Maximum::Linear::Velocity, 
			m_driver.rotate * Drivetrain::Movement::Maximum::Angular::Velocity, 
			m_driver.field_relative,
			Drivetrain::Movement::Rotate::Around::Center });}, 
		{&m_drive}
	));
	*/
}

void RobotContainer::ConfigureButtonBindings() {
	frc2::Trigger resetGyro([this] { return m_driver.gyro_reset; });
	resetGyro.OnTrue(frc2::InstantCommand( [] {Gyro::GetInstance()->ahrs.Reset();} ).ToPtr());

	frc2::Trigger pickupNote([this] { return m_operator.shootNote; });
	pickupNote.WhileTrue(m_noteMechanism.ShootNote().ToPtr());
}

void RobotContainer::ConfigureAutonomousChooser() {
	//m_chooser.SetDefaultOption("test", a_test.get());
}

frc2::Command* RobotContainer::GetAutonomousCommand() { 
	return m_chooser.GetSelected(); 
}

void RobotContainer::ConfigureDashboard() {
	/*
	#define DASHBOARD frc::Shuffleboard::GetTab("Data")
	#define AUTO_DASHBOARD frc::Shuffleboard::GetTab("Autonomous")
	#define TELE_DASHBOARD frc::Shuffleboard::GetTab("Teleoperated")
	#define DIAGNOSTICS_DASHBOARD frc::Shuffleboard::GetTab("Diagnostics")

	AUTO_DASHBOARD.Add(m_chooser);

	DIAGNOSTICS_DASHBOARD.Add(PDH::GetInstance()->m_PDH);
	DIAGNOSTICS_DASHBOARD.Add(Field2d::GetInstance()->m_field);

	TELE_DASHBOARD.AddDouble("Time Remaining", [] { return ( 150 - (frc::Timer().Get().value()) ); });

	TELE_DASHBOARD.AddDouble("Throttle", [this] { return m_driver.throttle; });
	*/

	
}