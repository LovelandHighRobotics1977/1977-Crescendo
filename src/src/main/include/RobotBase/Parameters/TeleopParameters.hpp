#ifndef _TELEOP_PARAMETERS_H
#define _TELEPOP_PARAMETERS_H

#include "RobotBase/specifications/RobotSpecifications.hpp"

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

#endif