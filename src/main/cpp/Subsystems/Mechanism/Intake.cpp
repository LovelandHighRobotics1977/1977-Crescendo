#include "subsystems/Mechanism/Intake.h"

Intake::Intake() : m_intakeMotor{Mechanism::Intake::ID}{
	intakeMotorConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Brake);
    intakeMotorConfig.MotorOutput.WithInverted(ctre::phoenix6::signals::InvertedValue::CounterClockwise_Positive);
    m_intakeMotor.GetConfigurator().Apply(intakeMotorConfig);
}

void Intake::setIntake(double speed){
	m_intakeMotor.Set(speed);
}