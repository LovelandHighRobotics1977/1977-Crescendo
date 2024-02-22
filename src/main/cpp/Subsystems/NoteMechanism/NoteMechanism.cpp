#include "subsystems/NoteMechanism/NoteMechanism.hpp"

NoteMechanism::NoteMechanism(){}

frc2::StartEndCommand NoteMechanism::PickupNote(){
	return frc2::StartEndCommand(
		[this] { m_intake.setIntake(-0.5); } , 
		[this] { m_intake.setIntake(0); } , 
		{&m_intake}
	);
}

frc2::StartEndCommand NoteMechanism::ReverseNote(){
	return frc2::StartEndCommand(
		[this] { m_intake.setIntake(0.4); m_shooter.setShooter(0.2, 1); } ,
		[this] { m_intake.setIntake(0); m_shooter.setShooter(0); } ,
		{&m_intake}
	);
}

frc2::StartEndCommand NoteMechanism::ShootNote(){
	return frc2::StartEndCommand(
		[this] { m_shooter.setShooter(-1, 1); } , 
		[this] { m_shooter.setShooter(0); } , 
		{&m_shooter}
	);
}

frc2::FunctionalCommand NoteMechanism::RaiseShooter(){
	return frc2::FunctionalCommand(
		[this] { m_shooter.setShooterAngle(-1); } ,
		[this] { m_shooter.setShooterAngle(-1); } ,
		[this] (bool interrupted) { m_shooter.setShooterAngle(0); } ,
		[this] { return !m_angleLimitSwitch.Get(); } ,
		{&m_shooter}
	);
}

frc2::StartEndCommand NoteMechanism::LowerShooter(){
	return frc2::StartEndCommand(
		[this] { m_shooter.setShooterAngle(1); } ,
		[this] { m_shooter.setShooterAngle(0); } ,
		{&m_shooter}
	);
}