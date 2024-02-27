#ifndef _MECH_PARAMETERS_H
#define _MECH_PARAMETERS_H

#include "RobotBase/specifications/RobotSpecifications.hpp"

namespace Mechanism {
	static constexpr int Intake = 14;
	namespace Shooter {
		static constexpr int Top = 15;
		static constexpr int Bottom = 16;
		namespace Angle {
			static constexpr int Winch = 17;
			static constexpr int Encoder = 19;
			static constexpr auto MagnetOffset = 0.243896_tr;
			static constexpr double MagicNumber = 0;	// Multiplied by the total width of the april tags to return the angle reqired to score
														// Needs to be calculated, TODO
			namespace Preset {
				static constexpr auto MIN = 0.001_tr;
				static constexpr auto SpeakerClose = 0.03_tr;
				static constexpr auto SpeakerFar = 0.0175_tr;
				static constexpr auto MAX = 0.101319_tr;
			}
		}
	}
	namespace Climber {
		static constexpr int Limit = 0;
		static constexpr int Winch = 18;
	}	
}

#endif