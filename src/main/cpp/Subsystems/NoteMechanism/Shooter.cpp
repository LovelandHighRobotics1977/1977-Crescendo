#include "subsystems/NoteMechanism/Shooter.hpp"

Shooter::Shooter(){
	shooterMotorConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Coast);
    m_leftShooter.GetConfigurator().Apply(shooterMotorConfig);
    m_rightShooter.GetConfigurator().Apply(shooterMotorConfig);

    angleEncoderConfig.MagnetSensor.WithMagnetOffset(-.242676);
    angleEncoderConfig.MagnetSensor.WithAbsoluteSensorRange(ctre::phoenix6::signals::AbsoluteSensorRangeValue::Unsigned_0To1);
    angleEncoderConfig.MagnetSensor.WithSensorDirection(ctre::phoenix6::signals::SensorDirectionValue::Clockwise_Positive);
    m_shooterAngleEncoder.GetConfigurator().Apply(angleEncoderConfig);

    angleMotorConfig.Slot0.kP = 100;
    angleMotorConfig.MotorOutput.WithNeutralMode(ctre::phoenix6::signals::NeutralModeValue::Coast);
    angleMotorConfig.Feedback.WithRemoteCANcoder(m_shooterAngleEncoder);
    angleMotorConfig.MotorOutput.Inverted = true;
    m_shooterAngle.GetConfigurator().Apply(angleMotorConfig);
}

void Shooter::setShooter(double speed, double spin){
	m_leftShooter.Set(speed * spin);
    m_rightShooter.Set(-speed);
}

void Shooter::setShooterAngle(units::turn_t angle){
    m_shooterAngle.SetControl(ctre::phoenix6::controls::PositionDutyCycle{angle});
}