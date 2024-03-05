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
		[this] { m_intake.setIntake(0.4); m_shooter.setShooter(-0.2); } ,
		[this] { m_intake.setIntake(0); m_shooter.setShooter(0); } ,
		{&m_intake}
	);
}

frc2::SequentialCommandGroup NoteMechanism::ShootNote(){
	return frc2::SequentialCommandGroup(
		frc2::ParallelRaceGroup(
			frc2::RunCommand([this] { m_shooter.setShooter(1); }),
			frc2::WaitCommand(0.4_s)
		),
		frc2::ParallelRaceGroup(
			NoteMechanism::PickupNote(),
			frc2::WaitCommand(0.5_s)
		),
		frc2::InstantCommand([this] { m_shooter.setShooter(0); })
	);
}

void NoteMechanism::AngleShooter(){
	double tagID = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tid", -1); 
	if((tagID == 3) || (tagID == 4) || (tagID = 7) || (tagID == 8)){
        // Speaker Tag Detected, set to distance formula
		m_shooter.setShooterAngle(
			units::turn_t{
				(
					0.0012 * 
					nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tlong", Mechanism::Shooter::Angle::Preset::SpeakerClose.value())
				) -
				0.0146
			}
		);
		
    }else if((tagID == 5) || (tagID == 6)){
        // Amp Tag Detected, set to max angle for scoring
        m_shooter.setShooterAngle(Mechanism::Shooter::Angle::Preset::MAX);
	}else{
		// Unknown Tag Detected, set to mid angle
		m_shooter.setShooterAngle(Mechanism::Shooter::Angle::Preset::SpeakerClose);
	}
}