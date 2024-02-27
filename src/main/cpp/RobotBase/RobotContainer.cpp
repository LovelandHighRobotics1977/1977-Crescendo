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

	frc::RobotController::GetCANStatus();
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
	m_noteMechanism.SetDefaultCommand(frc2::RunCommand( [this] { m_noteMechanism.AngleShooter(); } ));
}

void RobotContainer::ConfigureButtonBindings() {
	frc2::Trigger resetGyro([this] { return m_driver.gyro_reset; });
	resetGyro.OnTrue(frc2::InstantCommand( [] {Gyro::GetInstance()->ahrs.Reset();} ).ToPtr());

	frc2::Trigger pickupNote([this] { return m_operator.pickupNote; });
	pickupNote.WhileTrue(m_noteMechanism.PickupNote().ToPtr());

	frc2::Trigger reverseNote([this] { return m_operator.reverseNote; });
	reverseNote.WhileTrue(m_noteMechanism.ReverseNote().ToPtr());

	frc2::Trigger shootNote([this] { return m_operator.shootNote; });
	shootNote.WhileTrue(m_noteMechanism.ShootNote().ToPtr());

	frc2::Trigger openClimber([this] { return m_operator.openClimber; });
	openClimber.WhileTrue(m_climber.OpenClimber().ToPtr());

	frc2::Trigger closeClimber([this] { return m_operator.closeClimber; });
	closeClimber.WhileTrue(m_climber.CloseClimber().ToPtr());
}

void RobotContainer::ConfigureAutonomousChooser() {
	m_chooser.SetDefaultOption("spin", a_test.get());
	m_chooser.AddOption("square", a_square.get());
}

frc2::Command* RobotContainer::GetAutonomousCommand() { 

	return m_chooser.GetSelected(); 
}

void RobotContainer::ConfigureDashboard() {

	cs::UsbCamera DriveCamera = frc::CameraServer::StartAutomaticCapture(0);

	frc::Shuffleboard::GetTab("Autonomous").Add(m_chooser);
	
}