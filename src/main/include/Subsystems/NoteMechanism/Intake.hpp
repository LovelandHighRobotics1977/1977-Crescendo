#ifndef _INTAKE_H
#define _INTAKE_H

#include "headers/Headers.hpp"

class Intake : public frc2::SubsystemBase {
	public:
		Intake();

		void setIntake(double speed);

	private:

		ctre::phoenix6::hardware::TalonFX m_intakeMotor;
	    ctre::phoenix6::configs::TalonFXConfiguration intakeMotorConfig{};
		
};

#endif // _SUBSYSTEM_ARM_COMPONENTS_INTAKE_H