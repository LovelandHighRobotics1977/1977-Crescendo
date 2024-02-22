#ifndef _SHOOTER_H
#define _SHOOTER_H

#include "headers/Headers.hpp"

class Shooter : public frc2::SubsystemBase {
	public:
		Shooter();

		/**
		 * Sets the speed of the shooter motors
		 * @param speed The speed of the shooter [ -1 -> 1 ] with -1 being full reverse and 1 being full forward
		 * @param spin The spin of the shooter [ 0 -> 1 ] with 0 being full widdershins and 1 being no spin.  Defaults to 1
		*/
		void setShooter(double speed, double spin = 1);

		void setShooterAngle(double angle);

	private:

		ctre::phoenix6::hardware::TalonFX m_leftShooter{Mechanism::Shooter::Left};
		ctre::phoenix6::hardware::TalonFX m_rightShooter{Mechanism::Shooter::Right};
		ctre::phoenix6::hardware::TalonFX m_shooterAngle{Mechanism::Shooter::Angle};
	    ctre::phoenix6::configs::TalonFXConfiguration shooterMotorConfig{};
	
};

#endif // _SUBSYSTEM_ARM_COMPONENTS_SHOOTER_H