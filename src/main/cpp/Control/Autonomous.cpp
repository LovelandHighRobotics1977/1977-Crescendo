#include "Control/Autonomous.hpp"

frc2::CommandPtr AutoRoutine::test(DriveSubsystem *drive) {
	return frc2::SequentialCommandGroup(
		drive->ZeroOdometry({0_m, 0_m, 0_deg}),
		frc2::RepeatCommand(
			frc2::SequentialCommandGroup(
				frc2::ParallelRaceGroup(
					frc2::RunCommand(
						[drive] { drive->Drive({ 
						0_mps, 
						0_mps, 
						45_deg_per_s, 
						0,
						Drivetrain::Movement::Rotate::Around::Center });}
					),
					frc2::WaitCommand(3_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand(
						[drive] { drive->Drive({ 
						0_mps, 
						0_mps, 
						-45_deg_per_s, 
						0,
						Drivetrain::Movement::Rotate::Around::Center });}
					),
					frc2::WaitCommand(3_s)
				)
			)
		)
	).ToPtr();
}

frc2::CommandPtr AutoRoutine::square(DriveSubsystem *drive) {
	return frc2::SequentialCommandGroup(
		drive->ZeroOdometry({0_m, 0_m, 0_deg}),
		frc2::RepeatCommand(
			frc2::SequentialCommandGroup(
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 6_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, -6_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, -6_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 6_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				)
			)
		)
	).ToPtr();
}