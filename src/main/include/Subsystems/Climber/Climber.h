#ifndef _CLIMBER_H
#define _CLIMBER_H

#include "headers/Headers.h"
#include "Subsystems/Climber/Actuator.h"

class Climber : public frc2::SubsystemBase {
	public:
		Climber();

		frc2::StartEndCommand OpenClimber();
		frc2::StartEndCommand CloseClimber();

	private:

        Actuator m_actuator;

};

#endif // _NOTE_MECHANISM_H