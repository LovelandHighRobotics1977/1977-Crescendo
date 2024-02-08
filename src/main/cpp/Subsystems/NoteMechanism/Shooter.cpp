#include "subsystems/NoteMechanism/Shooter.h"

Shooter::Shooter(){
	shooterMotorConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Coast);
    m_leftShooter.GetConfigurator().Apply(shooterMotorConfig);
    m_rightShooter.GetConfigurator().Apply(shooterMotorConfig);
}

void Shooter::setShooter(double speed, double spin){
	m_leftShooter.Set(speed * spin);
    m_rightShooter.Set(-speed);
}