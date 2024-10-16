#ifndef _CLIMBER_H
#define _CLIMBER_H

#include "headers/Headers.hpp"
#include "Subsystems/Climber/Actuator.hpp"

class Climber : public frc2::SubsystemBase {
	public:
		Climber();

		frc2::StartEndCommand OpenClimber();
		frc2::FunctionalCommand CloseClimber();
		
	private:

        Actuator m_actuator;

		frc::DigitalInput m_angleLimitSwitch{Mechanism::Climber::Limit};

};

#endif // _NOTE_MECHANISM_H