#ifndef _CONTROLLERS_H
#define _CONTROLLERS_H

#include "Headers/Libraries.h"

#include "RobotBase/Specifications/Constants.h"

class Driver : public frc2::SubsystemBase {
	public:

		Driver(const int port):m_Joystick{port}{};

		bool field_relative;

		bool gyro_reset;

		bool trigger_one;
		bool trigger_two;

		bool coast_mode_toggle;

		double throttle;

		double forward;
		double strafe;  
		double rotate;

		

		/**
		 * Update the controller variables 
		 * @attention Each control scheme is defined in this function
		 * @note Automaically chooses the control scheme based on the joystick name
		*/
		void update(){

			// Control Scheme Definitions
			if(m_Joystick.GetName() == std::string{"X52 H.O.T.A.S."}){
				field_relative = !m_Joystick.GetRawButton(6);

				gyro_reset = m_Joystick.GetRawButton(2);

				trigger_one = m_Joystick.GetRawButton(1);
				trigger_two = m_Joystick.GetRawButton(15);

				coast_mode_toggle = m_Joystick.GetRawButton(5);

				throttle = (-m_Joystick.GetZ() + 1) / 2;

				forward = m_Joystick.GetY();
				strafe = -m_Joystick.GetX();
				rotate = m_Joystick.GetRawAxis(5);
			}

			if(m_Joystick.GetName() == std::string{"Extreme 3D pro"}){
				field_relative = !m_Joystick.GetRawButton(2);

				gyro_reset = m_Joystick.GetRawButton(3);

				trigger_one = m_Joystick.GetRawButton(1);
				trigger_two = m_Joystick.GetRawButton(15);

				coast_mode_toggle = m_Joystick.GetRawButton(4);

				throttle = (-m_Joystick.GetThrottle() + 1) / 2;

				forward = m_Joystick.GetY();
				strafe = -m_Joystick.GetX();
				rotate = m_Joystick.GetTwist();
			}

			// Controller values and optimizations

			forward = (-m_forwardLimiter.Calculate(frc::ApplyDeadband(forward, forward_deadzone)) * throttle);
			strafe = (-m_strafeLimiter.Calculate(frc::ApplyDeadband(strafe, strafe_deadzone)) * throttle);
			
			if(trigger_one && !trigger_two){
				rotate = 0.75 * (-m_rotateLimiter.Calculate(frc::ApplyDeadband(rotate, rotate_deadzone)) * sqrt(throttle));
			}else if(trigger_one && trigger_two){
				rotate = (-m_rotateLimiter.Calculate(frc::ApplyDeadband(rotate, rotate_deadzone)) * sqrt(throttle));
			}else{
				rotate = 0.4 * (-m_rotateLimiter.Calculate(frc::ApplyDeadband(rotate, rotate_deadzone)) * sqrt(throttle));
			}
		}

		private:
			frc::Joystick m_Joystick;

			frc::SlewRateLimiter<units::dimensionless::scalar> m_forwardLimiter{3 / 1_s};
			frc::SlewRateLimiter<units::dimensionless::scalar> m_strafeLimiter{3 / 1_s};
			frc::SlewRateLimiter<units::dimensionless::scalar> m_rotateLimiter{3 / 1_s};

			double forward_deadzone = 0.05;
			double strafe_deadzone = 0.05;
			double rotate_deadzone = 0.1;
	};

class Operator : public frc2::SubsystemBase {
	public:

		Operator(const int port):m_XboxController{port}{};

		bool pickupNote;
		bool shootNote;

		void update(){
			pickupNote = m_XboxController.GetAButton();
			shootNote = m_XboxController.GetBButton();
		}
		
	private:
		frc::XboxController m_XboxController;
};

#endif // _CONTROLLERS_H