#ifndef _MECH_PARAMETERS_H
#define _MECH_PARAMETERS_H

#include "RobotBase/specifications/RobotSpecifications.h"

namespace Mechanism {
	static constexpr int Intake = 14;
	namespace Shooter {
		static constexpr int Right = 15;
		static constexpr int Left = 16;
		static constexpr int Angle = 17;
	}
	static constexpr int Climber = 18;
}

#endif