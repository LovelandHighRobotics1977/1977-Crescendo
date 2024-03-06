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
					frc2::RunCommand([drive] { drive->Drive({0_fps, -7_fps, 0_deg_per_s, 0});}, {drive}),
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
frc2::CommandPtr AutoRoutine::zone1(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
	return frc2::SequentialCommandGroup(
		drive->ZeroOdometry({0_m, 0_m, 0_deg}),
			frc2::SequentialCommandGroup(
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 1.5_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-5_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-2_fps, -6.5_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),

				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6.5_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(2_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 130_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				drive->ZeroOdometry({0_m,0_m,0_deg})
		)
	).ToPtr();
}
frc2::CommandPtr AutoRoutine::zone2(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
	return frc2::SequentialCommandGroup(
		drive->ZeroOdometry({0_m, 0_m, 0_deg}),
			frc2::SequentialCommandGroup(
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-1_fps, -1_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, -45_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0.5_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-7_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(2_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 130_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				frc2::ParallelRaceGroup(
					//this command is for resetting the gyro
					drive->ZeroOdometry({0_m, 0_m, 0_deg}),
					frc2::WaitCommand(1_s)
				)
		)
	).ToPtr();
}
frc2::CommandPtr AutoRoutine::zone3(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
	return frc2::SequentialCommandGroup(
		drive->ZeroOdometry({0_m, 0_m, 0_deg}),
			frc2::SequentialCommandGroup(
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),			
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-1.5_fps, 1.5_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 45_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),	
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				)
		)
	).ToPtr();
}
frc2::CommandPtr AutoRoutine::zone4(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
    return frc2::SequentialCommandGroup(
        drive->ZeroOdometry({0_m, 0_m, 0_deg}),
            frc2::SequentialCommandGroup(
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::RunCommand([noteMechanism] { noteMechanism->ShootNote();}, {noteMechanism}),
                    frc2::WaitCommand(2_s)
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({0_fps, 1.5_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(1_s)
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({-5_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::RunCommand([noteMechanism] { noteMechanism->PickupNote();}, {noteMechanism}),
                    frc2::WaitCommand(1_s)
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::RunCommand([noteMechanism] { noteMechanism->ShootNote();}, {noteMechanism}),
                    frc2::WaitCommand(2_s)
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({-4_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(1_s)
                ),
                /*frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({0_fps, -5.5_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(1_s)
                ),*/
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({-2_fps, 2_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(1_s)
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({-10_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(1_s)
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
                    //frc2::RunCommand([noteMechanism] { noteMechanism->ShootNote();}, {noteMechanism}),
                    frc2::WaitCommand(2_s)
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 180_deg_per_s, 0, Drivetrain::Movement::Rotate::Around::Center});}, {drive}),
                    frc2::WaitCommand(1_s)
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
                    //this command is for resetting the gyro
                    //frc2::RunCommand([drive]{ drive->gyro}),
                    frc2::WaitCommand(1_s)
                )
        )
    ).ToPtr();
}
