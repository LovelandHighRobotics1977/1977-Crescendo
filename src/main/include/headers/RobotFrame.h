#include "Libraries.h"
#include "Util.h"

/*
		  Y

	RL	  |		FL
		  |
	  G    ---->	X

	RR			FR



*/

namespace Drivetrain {
	namespace Measurements {
		namespace Frame {
			static constexpr auto width = 26_in;
			static constexpr auto length = 26_in;
		}
		namespace Gyroscope {
			static constexpr auto xPosition = -10_in;
			static constexpr auto yPosition = 0_in;
		}
		namespace Distance {
			static const auto gyroToFront = Frame::length - units::math::abs(Gyroscope::xPosition);
			static const auto gyroToRear = gyroToFront - Frame::length;
			static const auto gyroToLeft = Frame::width - units::math::abs(Gyroscope::yPosition);
			static const auto gyroToRight = gyroToLeft - Frame::width;
		}
	}
	namespace Swerve {
		namespace Wheel {
			static constexpr auto radius = 2_in;
			static constexpr auto offset = 2.625_in;
		}
		namespace Module {
			namespace Front {
				namespace Left {
					static constexpr int drive = 0;
					static constexpr int angle = 0;
					static constexpr int encoder = 0;
					static constexpr double MagnetOffset = 0;
					static const frc::Translation2d location = {
						Measurements::Distance::gyroToFront - Wheel::offset,
						Measurements::Distance::gyroToLeft - Wheel::offset
					};
				}
				namespace Right {
					static constexpr int drive = 0;
					static constexpr int angle = 0;
					static constexpr int encoder = 0;
					static constexpr double MagnetOffset = 0;
					static const frc::Translation2d location = {
						Measurements::Distance::gyroToFront - Wheel::offset,
						Measurements::Distance::gyroToRight + Wheel::offset
					};
				}
			}
			namespace Rear {
				namespace Left {
					static constexpr int drive = 0;
					static constexpr int angle = 0;
					static constexpr int encoder = 0;
					static constexpr double MagnetOffset = 0;
					static const frc::Translation2d location = {
						Measurements::Distance::gyroToRear + Wheel::offset,
						Measurements::Distance::gyroToLeft - Wheel::offset
					};
				}
				namespace Right {
					static constexpr int drive = 0;
					static constexpr int angle = 0;
					static constexpr int encoder = 0;
					static constexpr double magnetOffset = 0;
					static const frc::Translation2d location = {
						Measurements::Distance::gyroToRear + Wheel::offset,
						Measurements::Distance::gyroToRight + Wheel::offset
					};
				}
			}
		}
		namespace Motor {
			namespace Drive {
				namespace Physical {
					static constexpr double max_rpm = 6380;
					static constexpr double gear_ratio = 6.75;
					static constexpr double encoder_cpr = 2048;
					static const auto distance_per_pulse = (((2 * Wheel::radius) * M_PI) / (gear_ratio * encoder_cpr));
					namespace PID {
						static constexpr double P = 0.001;
						static constexpr double I = 0;
						static constexpr double D = 0.005;
						static constexpr double F = 1;
					}
				}
				namespace Controller {
					static constexpr double P = 1;
					static constexpr double I = 0;
					static constexpr double D = 0;
				}
			}
			namespace Angle {
				namespace Physical {
					static constexpr double max_rpm = 6380;
					static constexpr double gear_ratio = 150/7;
					static constexpr double encoder_cpr = 4096;
					static constexpr auto distance_per_pulse = units::radian_t{((2 * M_PI) / (encoder_cpr))};
					namespace PID {
						static constexpr double P = 1.7;
						static constexpr double I = 0.0016;
						static constexpr double D = 160;
						static constexpr double F = 0;
					}
				}
				namespace Controller {
					static constexpr double P = 0.005;
					static constexpr double I = 0.001;
					static constexpr double D = 0;
				}
			}
		}
	}
	namespace Movement {
		
	}
}