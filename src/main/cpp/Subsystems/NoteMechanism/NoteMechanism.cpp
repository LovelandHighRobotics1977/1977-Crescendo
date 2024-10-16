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

void NoteMechanism::AngleShooter(bool override, bool shutdown){
	double tagID = nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumber("tid", -1); 
	if(frc::RobotController::GetTeamNumber() == 1822 || shutdown){
		// Bot is 1822, DO NOT SET SHOOTER ANGLE
	/*}else if(frc::RobotController::GetTeamNumber() == 1977 && !frc::DriverStation::IsAutonomous()){
		m_shooter.setShooterAngle(Mechanism::Shooter::Angle::Preset::MAX);*/
	}else if(override == true || (tagID == -1)){
		// No tag detected or override enabled, set angle to max
		angleMax();
	}else if((tagID == 3) || (tagID == 4)){
		// Red speaker tag detected, run "auto aim computations"
		double distanceToSpeaker = getDistance(652_in);

		angleSet(distanceToSpeaker);

	}else if((tagID = 7) || (tagID == 8)){
        // Blue speaker tag detected, run "auto aim computations"
		double distanceToSpeaker = getDistance(-1.5_in);

		angleSet(distanceToSpeaker);
		
	}else{
		// Unknown Tag Detected, set to max angle

		angleMax();
		
	}
}
//Add use the log to determine at what point the arm moves in a different direction, then add if statements for the limit switch and that distance
double NoteMechanism::getDistance(units::inch_t value){
		/**
		 * This complex function takes the position of the robot, and the speaker detected based on value, calculates the distance to the speaker,
		 * and using the distance and known height differential, uses inverse trig to calculate the angle to the speaker.  
		 * Then, the angle is reduced by 23 degrees to account for the zero angle of the shooter not being at 0 degrees, and sent to the motor
		*/
	return std::sqrt(
			std::pow(units::meter_t{value}.value() - nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumberArray("botpose_wpiblue",{})[0],2) +
			std::pow(units::meter_t{218_in}.value() - nt::NetworkTableInstance::GetDefault().GetTable("limelight")->GetNumberArray("botpose_wpiblue",{})[1],2)
	);
}
void NoteMechanism::angleSet(double dist){
	frc::SmartDashboard::PutNumber("ditance", dist);
	m_shooter.setShooterAngle( units::turn_t{ 
		units::radian_t{ ( std::atan( units::meter_t{ ( 82_in + Mechanism::Shooter::Angle::AutoAim::heightOffset ) }.value() / ( dist )))} - units::radian_t{23_deg}
	});
}

void NoteMechanism::angleMax(){
	m_shooter.setShooterAngle(Mechanism::Shooter::Angle::Preset::MAX);
}

