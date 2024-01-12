#include "commands/Autonomous.h"

frc2::CommandPtr AutoRoutine::test(DriveSubsystem *drive) {
	return frc2::SequentialCommandGroup(
		drive->ZeroOdometry({0_m, 0_m, 0_deg})
	).ToPtr();
}