// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include "Headers/Libraries.h"
#include "Headers/Util.h"

namespace Drivetrain {
	namespace Measurements {
		namespace Frame {
			static constexpr auto width = 26_in;
			static constexpr auto length = 26_in;
		}
		namespace Gyroscope {
			static constexpr auto xPosition = 8_in;
			static constexpr auto yPosition = 0_in;
		}
		namespace Wheel {
			static constexpr auto radius = 2_in;
			static constexpr auto offset = 2.625_in;
			static constexpr auto circumference = (2 * radius) * M_PI;
		}
		namespace Circle {
			static const auto Radius = units::foot_t{std::hypot(((Frame::length/2)-Wheel::offset).value(), ((Frame::length/2)-Wheel::offset).value())};
			static const auto Circumference = (2 * Radius) * M_PI;
		}
	}
	namespace Module {
		namespace Motor {
			namespace Drive {
				static constexpr double max_rpm = 6380;
				static constexpr double gear_ratio = 6.75;
				static constexpr double encoder_cpr = 2048;
				static constexpr double output_rps = ( ( max_rpm / 60 ) / gear_ratio);
				static const auto distance_per_pulse = ((Measurements::Wheel::circumference) / (gear_ratio * encoder_cpr));
				static const auto distance_per_rotation = units::meter_t{distance_per_pulse * encoder_cpr};
				namespace PID {
					static constexpr double S = 0;
					static constexpr double V = 0;
					static constexpr double A = 0;
					static constexpr double P = 1;
					static constexpr double I = 0;
					static constexpr double D = 0.1;
					namespace Controller {
						static constexpr double P = 1;
						static constexpr double I = 0;
						static constexpr double D = 0;
					}
				}
			}
			namespace Angle {
				static constexpr double max_rpm = 6380;
				static constexpr double gear_ratio = 150/7;
				static constexpr double encoder_cpr = 4096;
				static constexpr double output_rps = ( ( max_rpm / 60 ) / gear_ratio);
				static constexpr auto distance_per_pulse = units::radian_t{((2 * M_PI) / (encoder_cpr))};
				static const auto distance_per_rotation = units::degree_t{distance_per_pulse * encoder_cpr};
				namespace PID {
					static constexpr double S = 0;
					static constexpr double V = 0;
					static constexpr double A = 0;
					static constexpr double P = 1.7;
					static constexpr double I = 0.0016;
					static constexpr double D = 160;
					namespace Controller {
						static constexpr double P = 0.005;
						static constexpr double I = 0.001;
						static constexpr double D = 0;
					}
				}
			}
		}
		namespace Front {
			namespace Left {
				static constexpr int Drive = 11;
				static constexpr int Angle = 12;
				static constexpr int Encoder = 13;
				static constexpr double MagnetOffset = 360 - 210.762;
				static const frc::Translation2d Location = {
					( + (((Measurements::Frame::length)/2) - Measurements::Wheel::offset)) - Measurements::Gyroscope::xPosition,
					( + (((Measurements::Frame::width)/2) - Measurements::Wheel::offset)) - Measurements::Gyroscope::yPosition
				};
			}
			namespace Right {
				static constexpr int Drive = 2;
				static constexpr int Angle = 3;
				static constexpr int Encoder = 4;
				static constexpr double MagnetOffset = 360 - 112.859;
				static const frc::Translation2d Location = {
					( + (((Measurements::Frame::length)/2) - Measurements::Wheel::offset)) - Measurements::Gyroscope::xPosition,
					( - (((Measurements::Frame::width)/2) + Measurements::Wheel::offset)) - Measurements::Gyroscope::yPosition
				};
			}
		}
		namespace Rear {
			namespace Left {
				static constexpr int Drive = 8;
				static constexpr int Angle = 9;
				static constexpr int Encoder = 10;
				static constexpr double MagnetOffset = 360 - 250.609;
				static const frc::Translation2d Location = {
					( - (((Measurements::Frame::length)/2) + Measurements::Wheel::offset)) - Measurements::Gyroscope::xPosition,
					( + (((Measurements::Frame::width)/2) - Measurements::Wheel::offset)) - Measurements::Gyroscope::yPosition
				};
			}
			namespace Right {
				static constexpr int Drive = 5;
				static constexpr int Angle = 6;
				static constexpr int Encoder = 7;
				static constexpr double MagnetOffset = 360 - 258.398;
				static const frc::Translation2d Location = {
					( - (((Measurements::Frame::length)/2) + Measurements::Wheel::offset)) - Measurements::Gyroscope::xPosition,
					( - (((Measurements::Frame::width)/2) + Measurements::Wheel::offset)) - Measurements::Gyroscope::yPosition
				};
			}
		}
	}
	namespace Movement {
		namespace Maximum {
			namespace Linear {
				// ~ 16 feet per second
				static const auto Velocity = ( units::foot_t{ Measurements::Wheel::circumference } * Module::Motor::Drive::output_rps ) / 1_s;
				static const auto Acceleration = Velocity / 1_s;
			}
			namespace Angular {
				// ~ 773 degrees per second
				static const auto Velocity = units::degrees_per_second_t{( 360 * ( Linear::Velocity / Measurements::Circle::Circumference ) ).value()};
				static const auto Acceleration = Velocity / 1_s;
			}
		}
		namespace Rotate {
			namespace Preset {
				static const units::degrees_per_second_t None = 0_deg_per_s;  						//  0 degrees per second
				static const units::degrees_per_second_t Slow =  Maximum::Angular::Velocity / 3;	//  260 degrees per second
				static const units::degrees_per_second_t Medium = Maximum::Angular::Velocity / 2;	//  370 degrees per second
				static const units::degrees_per_second_t Fast = Maximum::Angular::Velocity;  		//  770 degrees per second
			}
			namespace Around {
				static constexpr frc::Translation2d Center = { - Measurements::Gyroscope::xPosition , - Measurements::Gyroscope::yPosition };   						//  position of the center of the robot
			}
		}
	}
}

namespace Mechanism {
	namespace Intake {
		static constexpr int ID = 14;
	}
}

namespace AutonomousMode {
    namespace Parameter {
		namespace Linear {
			static const auto Velocity = Drivetrain::Movement::Maximum::Linear::Velocity / 5;
			static const auto Acceleration = Drivetrain::Movement::Maximum::Linear::Acceleration;
		}
		namespace Angular {
			static const auto Velocity = Drivetrain::Movement::Maximum::Angular::Velocity;
			static const auto Acceleration = Drivetrain::Movement::Maximum::Angular::Acceleration;
		}
	}
	namespace Controller {
		namespace Proportional {
			static constexpr double Forward = 0.1;
			static constexpr double Strafe = 0.1;
			static constexpr double Rotate = 0.1;
		}
		namespace Constraint {
			static const frc::TrapezoidProfile<units::radians>::Constraints Rotate{
				units::radians_per_second_t{Parameter::Angular::Velocity},
				units::radians_per_second_squared_t{Parameter::Angular::Acceleration}
			};
		}
	}
}

namespace TeleoperatedMode {
	namespace Parameter {
		namespace Linear {
			// Max horizontal velocity of ~16 feet per second
			static const auto Velocity = Drivetrain::Movement::Maximum::Linear::Velocity;
		}
		namespace Angular {
			// Max rotational velocity of ~773 degrees per second
			static const auto Velocity = Drivetrain::Movement::Maximum::Angular::Velocity;
		}
	}
	namespace Controller {
		namespace Ports {
			static constexpr int Driver = 0;
			static constexpr int Operator = 1;
		}
	}
}

#endif // CONSTANTS_H