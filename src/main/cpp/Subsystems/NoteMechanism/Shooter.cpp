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

void Shooter::setShooter(double speed){
	m_leftShooter.Set(speed * .75);   // bottom
    m_rightShooter.Set(-speed * .75);     // top
}

void Shooter::setShooterAngle(units::turn_t angle){
    m_shooterAngle.SetControl(ctre::phoenix6::controls::PositionDutyCycle{
        max(Mechanism::Shooter::Angle::Preset::MIN, min(angle, Mechanism::Shooter::Angle::Preset::MAX))
    });
}