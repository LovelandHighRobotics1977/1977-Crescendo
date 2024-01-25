#ifndef _SHOOTER_H
#define _SHOOTER_H

#include "headers/Headers.h"

class Shooter : public frc2::SubsystemBase {
	public:
		Shooter();

		void setShooter(double speed);

	private:

		ctre::phoenix6::hardware::TalonFX m_leftShooter{Mechanism::Shooter::Left};
		ctre::phoenix6::hardware::TalonFX m_rightShooter{Mechanism::Shooter::Right};
	    ctre::phoenix6::configs::TalonFXConfiguration shooterMotorConfig{};
	
};

#endif // _SUBSYSTEM_ARM_COMPONENTS_SHOOTER_H