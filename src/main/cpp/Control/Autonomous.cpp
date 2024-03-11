#include "Control/Autonomous.hpp"


//example auto routine
/*

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


//1977 red auto routines
frc2::CommandPtr AutoRoutine::redCenterBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
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
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				frc2::ParallelRaceGroup(
					noteMechanism->PickupNote(),
					frc2::WaitCommand(0.25_s)
				),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-1.5_fps, -3_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(2_s)
				),

				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6.5_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(2_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 150_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				drive->ZeroOdometry({0_m,0_m,0_deg})
		)
	).ToPtr();
}
//Has the bot score 2 times and go under the stage to exit.  Not technically a run, but it is the closest we have for center
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
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 150_deg_per_s, 0});}, {drive}),
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
frc2::CommandPtr AutoRoutine::redCenterAdvanced(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
    return frc2::SequentialCommandGroup(
        drive->ZeroOdometry({0_m, 0_m, 0_deg}),
            frc2::SequentialCommandGroup(
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 5.75_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-5.7_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				frc2::ParallelRaceGroup(
					noteMechanism->PickupNote(),
					frc2::WaitCommand(0.5_s)
				),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({5_fps, -5.2_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-5_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				frc2::ParallelRaceGroup(
					noteMechanism->PickupNote(),
					frc2::WaitCommand(0.4_s)
				),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({5_fps, -5_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-5_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				frc2::ParallelRaceGroup(
					noteMechanism->PickupNote(),
					frc2::WaitCommand(0.25_s)
				),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, -2_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(3_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 150_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				drive->ZeroOdometry({0_m,0_m,0_deg})
			)
	).ToPtr();
}
//1977 left side
//To be Tested
//The basics are able to be used for both bots

frc2::CommandPtr AutoRoutine::redLeftBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
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
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(2_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 130_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				drive->ZeroOdometry({0_m,0_m,0_deg})
			)
	).ToPtr();
}
//Do not try yet, must be improved
//1977 left side
frc2::CommandPtr AutoRoutine::redRightBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
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
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),	
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 6_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(2_s)
				)
		)
	).ToPtr();
}

frc2::CommandPtr AutoRoutine::redLeftRun(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
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
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 55_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, -2_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(3_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, -1_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 130_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				drive->ZeroOdometry({0_m,0_m,0_deg})
			)
	).ToPtr();
}

frc2::CommandPtr AutoRoutine::redRightRun(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
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
					frc2::RunCommand([drive] { drive->Drive({0_fps, -4_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(2_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(3_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 1_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 130_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				drive->ZeroOdometry({0_m,0_m,0_deg})
			)
	).ToPtr();
}

//1977 blue

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
					frc2::RunCommand([drive] { drive->Drive({-5_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-2_fps, 6.5_fps, 0_deg_per_s, 0});}, {drive}),
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
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),	
                frc2::ParallelRaceGroup(
                    frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 180_deg_per_s, 0});}, {drive}),
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
frc2::CommandPtr AutoRoutine::blueCenterAdvanced(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
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
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({2_fps, -4_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-2_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({2_fps, -8_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-2_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(2_s)
				)
			)
	).ToPtr();
}
//1977 right side
//To be Tested
frc2::CommandPtr AutoRoutine::blueLeftBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
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
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(2_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 130_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				drive->ZeroOdometry({0_m,0_m,0_deg})
			)
	).ToPtr();
}
//Do not try yet, must be improved
//1977 left side
frc2::CommandPtr AutoRoutine::blueRightBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
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
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),	
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, -6_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(2_s)
				)
		)
	).ToPtr();
}
frc2::CommandPtr AutoRoutine::blueRightRun(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
    return frc2::SequentialCommandGroup(
        drive->ZeroOdometry({0_m, 0_m, 0_deg}),
            frc2::SequentialCommandGroup(
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote()
			)
	).ToPtr();
}


//All of the following functions are for the 1822 bot



//1822 auto in center
frc2::CommandPtr AutoRoutine::redCenterBasic1822(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
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
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, -1.5_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({5_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote(),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, -2_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					noteMechanism->PickupNote(),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({0_fps, 0_fps, 150_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				drive->ZeroOdometry({0_m,0_m,0_deg})
			)
	).ToPtr();
}
//This is for 1822 in right posipion
frc2::CommandPtr AutoRoutine::redRightBasic1822(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
    return frc2::SequentialCommandGroup(
        drive->ZeroOdometry({0_m, 0_m, 0_deg}),
            frc2::SequentialCommandGroup(
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote()
			)
	).ToPtr();
}
//Score once, then leave
/*frc2::CommandPtr AutoRoutine::redLeftRun1822(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
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
					frc2::RunCommand([drive] { drive->Drive({0_fps, -6_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(1_s)
				),
				frc2::ParallelRaceGroup(
					frc2::RunCommand([drive] { drive->Drive({-6_fps, 0_fps, 0_deg_per_s, 0});}, {drive}),
					frc2::WaitCommand(2_s)
				),
				frc2::InstantCommand([drive] { drive->Drive({});}),
				drive->ZeroOdometry({0_m,0_m,0_deg})
			)
	).ToPtr();
}*/
//Skeleton base
frc2::CommandPtr AutoRoutine::redZone8(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
    return frc2::SequentialCommandGroup(
        drive->ZeroOdometry({0_m, 0_m, 0_deg}),
            frc2::SequentialCommandGroup(
				frc2::InstantCommand([drive] { drive->Drive({});}),
				noteMechanism->ShootNote()
			)
	).ToPtr();
}

//any bot, no score, stay out of the way
frc2::CommandPtr AutoRoutine::runNoScore(DriveSubsystem *drive, NoteMechanism *noteMechanism) {
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
				frc2::InstantCommand([drive] { drive->Drive({});}),
				drive->ZeroOdometry({0_m,0_m,0_deg})
			)
	).ToPtr();
}