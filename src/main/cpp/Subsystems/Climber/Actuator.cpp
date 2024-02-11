#include "subsystems/Climber/Actuator.h"

Actuator::Actuator() : m_actuatorMotor{Mechanism::Climber::Winch}{
    actuatorMotorConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Brake);
    actuatorMotorConfig.MotorOutput.WithInverted(ctre::phoenix6::signals::InvertedValue::CounterClockwise_Positive);
    m_actuatorMotor.GetConfigurator().Apply(actuatorMotorConfig);
}

void Actuator::setActuator(double speed){
	m_actuatorMotor.Set(speed);
}