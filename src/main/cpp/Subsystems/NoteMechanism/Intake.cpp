#include "subsystems/NoteMechanism/Intake.h"

Intake::Intake() : m_intakeMotor{Mechanism::Intake}{
    intakeMotorConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Coast);
    intakeMotorConfig.MotorOutput.WithInverted(ctre::phoenix6::signals::InvertedValue::CounterClockwise_Positive);
    intakeMotorConfig.CurrentLimits.WithSupplyCurrentLimit(20);
    m_intakeMotor.GetConfigurator().Apply(intakeMotorConfig);
}

void Intake::setIntake(double speed){
	m_intakeMotor.Set(speed);
}