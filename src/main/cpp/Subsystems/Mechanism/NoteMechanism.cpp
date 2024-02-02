#include "subsystems/Mechanism/NoteMechanism.h"

NoteMechanism::NoteMechanism(){}

frc2::StartEndCommand NoteMechanism::PickupNote(){
	return frc2::StartEndCommand(
		[this] { m_intake.setIntake(-1); } , 
		[this] { m_intake.setIntake(0); } , 
		{&m_intake}
	);
}

frc2::StartEndCommand NoteMechanism::ShootNote(){
	return frc2::StartEndCommand(
		[this] { m_shooter.setShooter(1, 0.9); } , 
		[this] { m_shooter.setShooter(0); } , 
		{&m_shooter}
	);
}
