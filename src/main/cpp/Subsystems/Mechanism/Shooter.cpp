#include "subsystems/Mechanism/Shooter.h"

Shooter::Shooter(){
	shooterMotorConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Coast);
    m_leftShooter.GetConfigurator().Apply(shooterMotorConfig);
    m_rightShooter.GetConfigurator().Apply(shooterMotorConfig);
}

void Shooter::setShooter(double speed){
	m_leftShooter.Set(speed);
    m_rightShooter.Set(-speed);
}