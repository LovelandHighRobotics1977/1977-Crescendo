#ifndef _AUTO_PARAMETERS_H
#define _AUTO_PARAMETERS_H

#include "RobotBase/specifications/RobotSpecifications.hpp"

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

#endif