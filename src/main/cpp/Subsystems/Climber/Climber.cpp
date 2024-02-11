#include "subsystems/Climber/Climber.h"

Climber::Climber() {}

frc2::StartEndCommand Climber::OpenClimber(){
	return frc2::StartEndCommand(
		[this] { m_actuator.setActuator(-1); } , 
        [this] { m_actuator.setActuator(0); } , 
		{&m_actuator}
	);
}

frc2::FunctionalCommand Climber::CloseClimber(){
	return frc2::FunctionalCommand(
		[this] { m_actuator.setActuator(1); } ,
		[this] { m_actuator.setActuator(1); } ,
		[this] (bool interrupted) { m_actuator.setActuator(0); } ,
		[this] { return !m_angleLimitSwitch.Get(); } ,
		{&m_actuator}
	);
}
