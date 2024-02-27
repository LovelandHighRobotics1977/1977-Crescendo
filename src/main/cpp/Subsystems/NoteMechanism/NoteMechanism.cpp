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
	double tagID = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tid", -1);
    if((tagID == 5) || (tagID == 6)){
        // Amp Tag Detected, set 50% speed for scoring
        return frc2::StartEndCommand(
			[this] { m_shooter.setShooter(-0.5, 1); } , // Might adjust spin value here to fling note in better
			[this] { m_shooter.setShooter(0); } , 
			{&m_shooter}
		);
    }else{
		// Amp Tag Not Detected, set 100% speed for scoring and tactics
		return frc2::StartEndCommand(
			[this] { m_shooter.setShooter(-1, 1); } , 
			[this] { m_shooter.setShooter(0); } , 
			{&m_shooter}
		);
	}
}

frc2::RunCommand NoteMechanism::AngleShooter(){
	return frc2::RunCommand(
		[this] { 
			double tagID = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tid", -1); 
			if(tagID == -1){
				// No tag detected, set to mid angle
				m_shooter.setShooterAngle(Mechanism::Shooter::Angle::Preset::SpeakerClose);
  			}else if((tagID == 3) || (tagID == 4) || (tagID = 7) || (tagID == 8)){
    		    // Speaker Tag Detected, set to distance * magic number
				m_shooter.setShooterAngle(
					units::turn_t{
						nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tlong", Mechanism::Shooter::Angle::Preset::SpeakerClose.value())
						* 
						Mechanism::Shooter::Angle::MagicNumber
				}); 
    		}else if((tagID == 5) || (tagID == 6)){
    		    // Amp Tag Detected, set to max angle for scoring
    		    m_shooter.setShooterAngle(Mechanism::Shooter::Angle::Preset::MAX);
			}else{
				// Unknown Tag Detected, set to mid angle
				m_shooter.setShooterAngle(Mechanism::Shooter::Angle::Preset::SpeakerClose);
			}
		},
		{&m_shooter}
	);
}