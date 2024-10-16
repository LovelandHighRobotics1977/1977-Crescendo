#include "Control/Autonomous.hpp"
//In the future, pose estimation will be used to determine the location and accuracy for auto
/*
Run : Shoot once and skedaddle ( In center : goes under the stage )
Basic : Shoot once, pickup and shoot, and skedaddle ( ONLY WORKS ON CENTER )
Advanced : Score as much as possible while still exiting ( ONLY WORKS ON CENTER ) ( UNRELIABLE )
Delay : Shoot, Wait 3 seconds, Do most advanced auto
Maximum : Score as much as possible ( CANNOT EXIT ) ( ONLY WORKS ON CENTER )
*/

/* example auto routine

sets the auto routine name and devices to be used.  In this case, it is named smapleAuto, and will
use the drivetrain and note mechanism:
frc2::CommandPtr AutoRoutine::sampleAuto(DriveSubsystem *drive, NoteMechanism *noteMechanism) {

	This tells the auto routine to complete all of the actions in order
    return frc2::SequentialCommandGroup(

		This will reset the gyro
        drive->ZeroOdometry({0_m, 0_m, 0_deg}),

            frc2::SequentialCommandGroup(

				This will have the bot immediately stop:
				frc2::InstantCommand([drive] { drive->Drive({});}),

				This will have the bot shoot a note, which takes around 0.5 seconds:
				noteMechanism->ShootNote()

				//This will set a function to be called
				frc2::ParallelRaceGroup(

					In this case, the function is to drive, which is determined by (forwards/backwards, left/right, rotation, and orientation base):
                    frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),

					This line will have the robot pick up a note while driving:
                    frc2::RunCommand([noteMechanism] { noteMechanism->PickupNote();}, {noteMechanism}),

					//This line will have the robot wait for the amount of time specified.  Normally, 1 second is enough:
                    frc2::WaitCommand(1_s)
                ),

				frc2::ParallelRaceGroup(

					//this command will reset the gyro
					//Be sure to stop the robot before hand, using the instant command
					drive->ZeroOdometry({0_m, 0_m, 0_deg}),

                    frc2::WaitCommand(1_s)

                ) Last line doesn't need a comma
			)
	).ToPtr();
}
*/

// CENTER AUTO ROUTINES
frc2::CommandPtr AutoRoutine::redCenterBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
	return frc2::SequentialCommandGroup(
		drive->ZeroOdometry({0_m, 0_m, 0_deg}),
			frc2::SequentialCommandGroup(
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 1_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				frc2::ParallelRaceGroup(
					noteMechanism->PickupNote(),
					frc2::WaitCommand(0.25_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({6_fps, -1_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote()
				/*frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-1.5_fps, -3_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(2_s)
				),

				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6.5_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(2_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});})
				*/
		)
	).ToPtr();
}
frc2::CommandPtr AutoRoutine::redCenterRun(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
    return frc2::SequentialCommandGroup(
        drive->ZeroOdometry({0_m, 0_m, 0_deg}),
            frc2::SequentialCommandGroup(
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),	
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({0_fps, 1.25_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(1_s)
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::RunCommand([noteMechanism] { noteMechanism->PickupNote();}, {noteMechanism}),
                    frc2::WaitCommand(1_s)
                ),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				frc2::ParallelRaceGroup(
					noteMechanism->PickupNote(),
					frc2::WaitCommand(0.25_s)
				),
				noteMechanism->ShootNote(),	
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({-4_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(1_s)
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({-2_fps, 2_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(1_s)
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({-5_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(2_s)
                ),
				frc2::InstantCommand([drive] { drive->Drive({});})

        )
    ).ToPtr();
}
frc2::CommandPtr AutoRoutine::redCenterAdvanced(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
    return frc2::SequentialCommandGroup(
        drive->ZeroOdometry({0_m, 0_m, 0_deg}),
            frc2::SequentialCommandGroup(
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 4_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-5_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 40_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(0.5_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				frc2::ParallelRaceGroup(
					frc2::WaitCommand(0.5_s)
				),

				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({4_fps, -3.5_fps, -25_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-4_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				frc2::ParallelRaceGroup(
					noteMechanism->PickupNote(),
					frc2::WaitCommand(0.5_s)
				),
				frc2::ParallelRaceGroup(
					frc2::WaitCommand(0.75_s)
				),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({4_fps, -3.5_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-4_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				frc2::ParallelRaceGroup(
					noteMechanism->PickupNote(),
					frc2::WaitCommand(0.5_s)
				),
				frc2::ParallelRaceGroup(
					frc2::WaitCommand(0.75_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, -25_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 25_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(2_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});})
			)
	).ToPtr();
}
frc2::CommandPtr AutoRoutine::redCenterDelay(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
    return frc2::SequentialCommandGroup(
        drive->ZeroOdometry({0_m, 0_m, 0_deg}),
            frc2::SequentialCommandGroup(
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(3_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 2_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-5_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 40_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(0.5_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				frc2::ParallelRaceGroup(
					frc2::WaitCommand(0.5_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({4_fps, -3.5_fps, -25_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-4_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				frc2::ParallelRaceGroup(
					noteMechanism->PickupNote(),
					frc2::WaitCommand(0.5_s)
				),
				frc2::ParallelRaceGroup(
					frc2::WaitCommand(0.75_s)
				),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({4_fps, -3.5_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-4_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				frc2::ParallelRaceGroup(
					noteMechanism->PickupNote(),
					frc2::WaitCommand(0.5_s)
				),
				frc2::ParallelRaceGroup(
					frc2::WaitCommand(0.75_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, -25_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 25_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(2_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});})
			)
	).ToPtr();
}

frc2::CommandPtr AutoRoutine::blueCenterBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
	return frc2::SequentialCommandGroup(
		drive->ZeroOdometry({0_m, 0_m, 0_deg}),
			frc2::SequentialCommandGroup(
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, -1.5_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				frc2::ParallelRaceGroup(
					noteMechanism->PickupNote(),
					frc2::WaitCommand(0.25_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({6_fps, 1.5_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote()
				/*frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-1.5_fps, 2.5_fps, -10_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(2_s)
				),

				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6.5_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(2_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});})
				*/
		)
	).ToPtr();
}
frc2::CommandPtr AutoRoutine::blueCenterRun(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
    return frc2::SequentialCommandGroup(
        drive->ZeroOdometry({0_m, 0_m, 0_deg}),
            frc2::SequentialCommandGroup(
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),	
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({0_fps, -1.5_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(1_s)
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({-5_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::RunCommand([noteMechanism] { noteMechanism->PickupNote();}, {noteMechanism}),
                    frc2::WaitCommand(1_s)
                ),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),	
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({-4_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(1_s)
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({-2_fps, -2_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(1_s)
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({-10_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(1_s)
                ),
				frc2::InstantCommand([drive] { drive->Drive({});})
        )
    ).ToPtr();
}
frc2::CommandPtr AutoRoutine::blueCenterAdvanced(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
    return frc2::SequentialCommandGroup(
        drive->ZeroOdometry({0_m, 0_m, 0_deg}),
            frc2::SequentialCommandGroup(
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, -4.5_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, -40_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(0.5_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				frc2::ParallelRaceGroup(
					frc2::WaitCommand(0.5_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({4_fps, 4.5_fps, 25_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-4_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				frc2::ParallelRaceGroup(
					noteMechanism->PickupNote(),
					frc2::WaitCommand(0.5_s)
				),
				frc2::ParallelRaceGroup(
					frc2::WaitCommand(0.75_s)
				),


				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({4_fps, 5_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-4_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				frc2::ParallelRaceGroup(
					noteMechanism->PickupNote(),
					frc2::WaitCommand(0.4_s)

				),
				frc2::ParallelRaceGroup(
					frc2::WaitCommand(0.75_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 25_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, -50_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(0.5_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 2_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(2_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});})
			)
	).ToPtr();
}
frc2::CommandPtr AutoRoutine::blueCenterDelay(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
    return frc2::SequentialCommandGroup(
        drive->ZeroOdometry({0_m, 0_m, 0_deg}),
            frc2::SequentialCommandGroup(
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(3_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, -4.5_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, -40_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(0.5_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				frc2::ParallelRaceGroup(
					frc2::WaitCommand(0.5_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({4_fps, 4.5_fps, 25_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-4_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				frc2::ParallelRaceGroup(
					noteMechanism->PickupNote(),
					frc2::WaitCommand(0.5_s)
				),
				frc2::ParallelRaceGroup(
					frc2::WaitCommand(0.75_s)
				),


				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({4_fps, 5_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-4_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				frc2::ParallelRaceGroup(
					noteMechanism->PickupNote(),
					frc2::WaitCommand(0.4_s)

				),
				frc2::ParallelRaceGroup(
					frc2::WaitCommand(0.75_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 25_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, -50_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(0.5_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 2_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(2_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});})
			)
	).ToPtr();
}



// AMP AUTO ROUTINES
frc2::CommandPtr AutoRoutine::redAmpBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
    return frc2::SequentialCommandGroup(
        drive->ZeroOdometry({0_m, 0_m, 0_deg}),
            frc2::SequentialCommandGroup(
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),			
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-1.5_fps, -1.5_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, -55_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({7.5_fps, 1.5_fps, 55_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote()
				/*frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(2_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});})
				*/
			)
	).ToPtr();
}
frc2::CommandPtr AutoRoutine::redAmpRun(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
    return frc2::SequentialCommandGroup(
        drive->ZeroOdometry({0_m, 0_m, 0_deg}),
            frc2::SequentialCommandGroup(
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),			
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-1.5_fps, -0.5_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 50_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				drive->ZeroOdometry({0_m, 0_m, 0_deg}),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-7_fps, 0_fps, -8_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(3_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});})
			)
	).ToPtr();
}
frc2::CommandPtr AutoRoutine::redAmpDelay(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
    return frc2::SequentialCommandGroup(
        drive->ZeroOdometry({0_m, 0_m, 0_deg}),
            frc2::SequentialCommandGroup(
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),			
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(3_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-1.5_fps, -0.5_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 50_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				drive->ZeroOdometry({0_m, 0_m, 0_deg}),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-7_fps, 0_fps, -8_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(3_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});})
			)
	).ToPtr();
}

frc2::CommandPtr AutoRoutine::blueAmpBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
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
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 55_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 2_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-4_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({5.5_fps, -3.5_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote()	
				/*frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, -6_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(2_s)
				)*/
		)
	).ToPtr();
}
frc2::CommandPtr AutoRoutine::blueAmpRun(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
    return frc2::SequentialCommandGroup(
        drive->ZeroOdometry({0_m, 0_m, 0_deg}),
            frc2::SequentialCommandGroup(
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),			
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-1.5_fps, -0.5_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, -50_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				drive->ZeroOdometry({0_m, 0_m, 0_deg}),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-7_fps, 0_fps, -8_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(3_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});})			
			)
	).ToPtr();
}
frc2::CommandPtr AutoRoutine::blueAmpDelay(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
    return frc2::SequentialCommandGroup(
        drive->ZeroOdometry({0_m, 0_m, 0_deg}),
            frc2::SequentialCommandGroup(
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),			
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(3_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-1.5_fps, -0.5_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, -50_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				drive->ZeroOdometry({0_m, 0_m, 0_deg}),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-7_fps, 0_fps, -8_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(3_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});})
			)
	).ToPtr();
}

// SOURCE AUTO ROUTINES
frc2::CommandPtr AutoRoutine::redSourceBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
	return frc2::SequentialCommandGroup(
		drive->ZeroOdometry({0_m, 0_m, 0_deg}),
			frc2::SequentialCommandGroup(
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),			
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-1.5_fps, -1.5_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, -55_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, -2_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-4_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({5.5_fps, 3.5_fps, 55_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote()
				/*frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 6_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(2_s)
				)*/
		)
	).ToPtr();
}
frc2::CommandPtr AutoRoutine::redSourceRun(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
    return frc2::SequentialCommandGroup(
        drive->ZeroOdometry({0_m, 0_m, 0_deg}),
            frc2::SequentialCommandGroup(
                frc2::InstantCommand([drive] { drive->Drive({});}),
                noteMechanism->ShootNote(),            
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({-1.5_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(1_s)
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, -60_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(1_s) 
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({0_fps, 5_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(2_s) 
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, -10_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(3_s) 
                ),
				frc2::InstantCommand([drive] { drive->Drive({});})
            )
    ).ToPtr();
}
frc2::CommandPtr AutoRoutine::redSourceDelay(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
    return frc2::SequentialCommandGroup(
        drive->ZeroOdometry({0_m, 0_m, 0_deg}),
            frc2::SequentialCommandGroup(
                frc2::InstantCommand([drive] { drive->Drive({});}),
                noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(3_s)
                ),            
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({-1.5_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(1_s)
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, -60_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(1_s) 
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({0_fps, 4_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(2_s) 
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, -10_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(3_s) 
                ),
                frc2::InstantCommand([drive] { drive->Drive({});})
            )
    ).ToPtr();
}

frc2::CommandPtr AutoRoutine::blueSourceBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
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
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 55_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({7.5_fps, -1.5_fps, -55_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote()
				/*frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(2_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});})*/
			)
	).ToPtr();
}
frc2::CommandPtr AutoRoutine::blueSourceRun(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
    return frc2::SequentialCommandGroup(
        drive->ZeroOdometry({0_m, 0_m, 0_deg}),
            frc2::SequentialCommandGroup(
                frc2::InstantCommand([drive] { drive->Drive({});}),
                noteMechanism->ShootNote(),            
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({-1.5_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(1_s)
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 60_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(1_s) 
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({0_fps, -5_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(2_s) 
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({-7_fps, 0_fps, -3_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(3_s) 
                ),
				frc2::InstantCommand([drive] { drive->Drive({});})
            )
    ).ToPtr();
}
frc2::CommandPtr AutoRoutine::blueSourceDelay(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
    return frc2::SequentialCommandGroup(
        drive->ZeroOdometry({0_m, 0_m, 0_deg}),
            frc2::SequentialCommandGroup(
                frc2::InstantCommand([drive] { drive->Drive({});}),
                noteMechanism->ShootNote(),  
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(3_s)
                ),          
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({-1.5_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(1_s)
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 60_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(1_s) 
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({0_fps, -5_fps, 0_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(2_s) 
                ),
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({-7_fps, 0_fps, -3_deg_per_s, 0});}, {drive}),
                    frc2::WaitCommand(3_s) 
                ),
				frc2::InstantCommand([drive] { drive->Drive({});})
            )
    ).ToPtr();
}

// ANY POSITION ROUTINES
frc2::CommandPtr AutoRoutine::onlyScore(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
    return frc2::SequentialCommandGroup(
        drive->ZeroOdometry({0_m, 0_m, 0_deg}),
            frc2::SequentialCommandGroup(
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote()
			)
	).ToPtr();
}

frc2::CommandPtr AutoRoutine::onlyRun(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
	return frc2::SequentialCommandGroup(
		drive->ZeroOdometry({0_m, 0_m, 0_deg}),
			frc2::SequentialCommandGroup(
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(3_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 150_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});})
			)
	).ToPtr();
}

// UwU :3
// Salem & Wyllow