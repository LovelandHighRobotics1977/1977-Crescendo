#include "commands/Autonomous.h"

frc2::CommandPtr AutoRoutine::fireCubeOnly(DriveSubsystem *drive, CubeArmSubsystem *arm) {
	return frc2::SequentialCommandGroup(
		drive->ZeroOdometry({0_m, 0_m, 0_deg})
	).ToPtr();
}

frc2::CommandPtr AutoRoutine::Red::DriveForward(DriveSubsystem *drive, CubeArmSubsystem *arm) {
	return frc2::SequentialCommandGroup(
		drive->ZeroOdometry({48_ft, 14_ft, 180_deg})
	).ToPtr();
}

frc2::CommandPtr AutoRoutine::Red::MidBalance(DriveSubsystem *drive, CubeArmSubsystem *arm) {
	return frc2::SequentialCommandGroup(
		drive->ZeroOdometry({48_ft, 8.4_ft, 180_deg})
	).ToPtr();
}