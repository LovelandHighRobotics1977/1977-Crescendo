#ifndef _ACTUATOR_H
#define _ACTUATOR_H

#include "headers/Headers.h"

class Actuator : public frc2::SubsystemBase {
	public:
        Actuator();

		void setActuator(double speed);

	private:

		ctre::phoenix6::hardware::TalonFX m_actuatorMotor;
	    ctre::phoenix6::configs::TalonFXConfiguration actuatorMotorConfig{};
		
};

#endif // _SUBSYSTEM_ARM_COMPONENTS_INTAKE_H