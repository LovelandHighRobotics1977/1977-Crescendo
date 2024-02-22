#include "subsystems/NoteMechanism/Shooter.hpp"

Shooter::Shooter(){
	shooterMotorConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Coast);
    m_leftShooter.GetConfigurator().Apply(shooterMotorConfig);
    m_rightShooter.GetConfigurator().Apply(shooterMotorConfig);

    shooterMotorConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Brake);
    m_shooterAngle.GetConfigurator().Apply(shooterMotorConfig);
}

void Shooter::setShooter(double speed, double spin){
	m_leftShooter.Set(speed * spin);
    m_rightShooter.Set(-speed);
}

void Shooter::setShooterAngle(double angle){
    m_shooterAngle.Set(angle);
}