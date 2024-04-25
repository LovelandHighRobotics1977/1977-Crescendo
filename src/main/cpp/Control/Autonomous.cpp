#include "Control/Autonomous.hpp"
#include vector;

/*
Run : Shoot once and skedaddle ( In center : goes under the stage )
Basic : Shoot once, pickup and shoot, and skedaddle ( ONLY WORKS ON CENTER )
Advanced 
: Score as much as possible while still exiting ( ONLY WORKS ON CENTER ) ( UNRELIABLE )
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

#define Hold 0
#define Pickup 1
#define Shoot 2
#define Seconds *1


void convertCode(std::vector<float> routine){
	for(int i = 0; i < routine.size(); i+6){

		//different actions based on whether the note is being picked up, shot, or nothing
		if(routine[i] == 1){
			frc2::RunCommand([drive] { drive->Drive({routine[i+1], routine[i+2], routine[i+3], routine[i+4]});}, {drive}),
			noteMechanism->PickupNote(),
		frc2::WaitCommand(routine[i+5]);
		}else if(routine[i] == 2){
			frc2::RunCommand([drive] { drive->Drive({routine[i+1], routine[i+2], routine[i+3], routine[i+4]});}, {drive}),
			noteMechanism->ShootNote(),
		frc2::WaitCommand(routine[i+5]);
		}else{
			frc2::RunCommand([drive] { drive->Drive({routine[i+1], routine[i+2], routine[i+3], routine[i+4]});}, {drive}),
			frc2::WaitCommand(routine[i+5]);
		}

	}



/*
The below case statements operate on 6 parameters at a time, based on if the
robot is shooting a note, picking up, or holding (doing nothing), on the speed 
and direction, angle of rotation, and duration (seconds)
*/

std::vector<float> code;

void switchStatement(std::string runType){

std::vector getAuto(std::string AutoName){
	switch(AutoName){
		case 'redCenterBasic': return 		std::vector<float>{Shoot,0,0,0,0, 1 Seconds, 	Hold,0,1,0,0, 1 Seconds, 		Pickup,-6,0,0,0, 1 Seconds, 		Pickup,0,0,0,0, 0.25 Seconds, 	Shoot,0,0,0,0, 0.75 Seconds, 	Hold,-1.5,-3,0,0, 2 Seconds, 	Pickup,-6.5,0,0,0, 2 Seconds};
		case 'redCenterRun': return 		std::vector<float>{Shoot,0,0,0,0, 1 Seconds, 	Hold,0,1.25,0,0, 1 Seconds, 	Pickup,-6,0,0,0, 1 Seconds, 		Pickup,0,0,0,0, 0.25 Seconds, 	Hold,-4,0,0, 0,1 Seconds, 		Hold,-2,2,0,0, 1 Seconds, 		Hold,-5,0,0,0, 2 Seconds };
		case 'redCenterAdvanced': return 	std::vector<float>{Shoot,0,0,0,0, 1 Seconds, 	Hold,0,2,0,0, 1 Seconds, 		Pickup,-5,0,0,0, 1 Seconds, 		Hold,0,0,0,0, 0 Seconds, 		Pickup,0,0,40,0, 0.5 Seconds, 	Hold,0,0,0,0, 0.5 Seconds, 		Hold,4,-3.5,-25,0, 1 Seconds,	Pickup,-4,0,0,0, 1 Seconds, 		Pickup,0,0,0,0, 0.5 Seconds, 	Shoot,0,0,0,0, 0.75 Seconds, 	Hold,4,-3.5,0,0, 1 Seconds, 		Pickup,-4,0,0,0, 1 Seconds, 		Pickup,0,0,0,0, 0.5S Seconds, 	Hold,0,0,0,0, 0.75 Seconds, 		Hold,0,0,-25,0, 1 Seconds, 		Shoot,0,0,0,0, 0.75 Seconds, 	Hold,-6,0,25,0, 1 Seconds, 			Hold,-6,0,0,0, 2 Seconds, 		Hold,0,0,0,0,0.25 Seconds};
		case 'redCenterDelay': return		std::vector<float>{Shoot,0,0,0,0, 1 Seconds, 	Hold,0,0,0,0, 3 Seconds, 		Hold,0,2,0,0, 1 Seconds, 			Pickup,-5,0,0,0, 1 Seconds,		Pickup,0,0,40,0, 0.5 Seconds, 	Hold,0,0,0,0, 0.5 Seconds, 		Shoot,0,0,0,0, 0.75, 			Hold,4,-3.5,-25,0, 1 Seconds,		Pickup, -4,0,0,0, 1 Seconds, 	Pickup,0,0,0,0, 0.5 Seconds, 	Hold,0,0,0,0, 0.75 Seconds, 		Hold,0,0,-25,0, 1 Seconds, 			Shoot,0,0,0,0, 0.75 Seconds, 	Hold,-6,0,25,0, 1 Seconds,			Hold,-6,0,0,0, 2 Seconds, 		Hold,0,0,0,0,0.25 Seconds};
		case 'blueCenterBasic': return		std::vector<float>{Shoot,0,0,0,0, 1 Seconds,	Hold,0,-1.5,0,0, 1 Seconds, 	Pickup,-6,0,0,0, 1 Seconds,			Pickup,0,0,0,0, 0.25 Seconds,	Shoot,0,0,0,0,0.75 Seconds,		Hold,-1.5,2.5,-10,0, 2 Seconds,	Pickup,-6.5,0,0,0, 2 Seconds, 	Hold,0,0,0,0, 0.25 Seconds};
		case 'blueCenterRun': return		std::vector<float>{Shoot,0,0,0,0, 1 Seconds,	Hold,0,-1.5,0,0, 1 Seconds,		Pickup,-5,0,0,0, 1 Seconds,			Shoot,0,0,0,0, 0.75 Seconds,	Hold,-4,0,0,0, 1 Seconds,		Hold,-2,-2,0,0, 1 Seconds,		Hold,-10,0,0,0, 1 Seconds,		Hold,0,0,0,0, 0.25 Seconds};
		case 'blueCenterAdvanced': return	std::vector<float>{Shoot,0,0,0,0, 1 Seconds,	Hold,0,-4.5,0,0, 1 Seconds,		Pickup,-6,0,0,0, 1 Seconds,			Hold,0,0,0,0, 0.75 Seconds,		Pickup,0,0,-40,0, 0.5 Seconds,	Hold,0,0,0,0, 0.5 Seconds, 		Shoot,0,0,0,0, 0.75 Seconds,	Hold,4,4.5,25,0, 1 Seconds,			Pickup,-4,0,0,0, 1 Seconds,		Pickup,0,0,0,0, 0.5 Seconds,	Shoot,0,0,0,0, 0.75 Seconds,		Hold, 4,5,0,0, 1 Seconds,			Pickup,-4,0,0,0, 1 Seconds,		Pickup,0,0,0,0, 0.4 Seconds,		Hold,0,0,0,0, 0.75 Seconds,		Hold,0,0,25,0, 1 Seconds,		Shoot,0,0,0,0,0.75 Seconds,			Hold,0,0,-50,0, 0.5 Seconds,	Hold, -6,2,0,0, 2 Seconds, 		Hold,0,0,0,0, 0.25 Seconds};
		case 'blueCenterDlay': return		std::vector<float>{Shoot,0,0,0,0, 1 Seconds,	Hold,0,0,0,0, 3 Seconds,		Hold,0,-4.5,0,0, 1 Seconds,			Pickup,-6,0,0,0, 1 Seconds,		Hold,0,0,0,0 0.25 Seconds,		Pickup,0,0,-40,0, 0.5 Seconds,	Hold,0,0,0,0, 0.5 Seconds,		Shoot,0,0,0,0, 0.75 Seconds,		Hold,4,4.5,25,0, 1 Seconds,		Pickup,-4,0,0,0, 1 Seconds,		Pickup,0,0,0,0, 0.5 Seconds, 		Hold,0,0,0,0, 0.75 Seconds, 		Shoot,0,0,0,0, 0.75 Seconds,	Hold,4,5,0,0, 1 Seconds,			Pickup,-4,0,0,0, 1 Seconds,		Hold,0,0,0,0, 0.25 Seconds,		Pickup,0,0,0,0, 0.4 Seconds,		Hold,0,0,0, 0.75 Seconds,		Hold,0,0,25,0, 1 Seconds,		Shoot,0,0,0,0, 0.75 Seconds,		Hold,0,0,-50,0, 0.5 Seconds,		Hold,-6,0,0,0, 1 Seconds,	Hold,-6,2,0,0, 2 Seconds, Hold,0,0,0,0, 0.25 Seconds};
		
		case 'redAmpBasic': return			std::vector<float>{Shoot,0,0,0,0, 1 Seconds,	Hold,-1.5,-1.5,0,0, 1 Seconds,	Hold,0,0,-55,0, 1 Seconds,			Pickup,-6,0,0,0, 1 Seconds,		Shoot,0,0,0,0, 0.75 Seconds,	Hold,-6,0,0,0, 2 Seconds,		Hold,0,0,0,0, 0.25 Seconds};
		case 'redAmpRun': return			std::vector<float>{Shoot,0,0,0,0, 1 Seconds,	Hold,-1.5,-0.5,0,0, 1 Seconds,	Hold,0,0,50,0, 1 Seconds,			Hold,-7,0,-8,0, 3 Seconds,		Hold,0,0,0,0, 0.25 Seconds};
		case 'redAmpDelay': return			std::vector<float>{Shoot,0,0,0,0, 1 Seconds,	Hold,0,0,0,0, 3 Seconds,		Hold,-1.5,-0.5,0,0, 1 Seconds,		Hold,0,0,50,0, 1 Seconds,		Hold,-7,0,-8,0, 3 Seconds,		Hold,0,0,0,0, 0.25 Seconds};
		case 'blueAmpBasic': return			std::vector<float>{Shoot,0,0,0,0, 1 Seconds,	Hold, -1.5,1.5,0,0, 1 Seconds,	Hold,0,0,55,0, 1 Seconds,			Hold,0,2,0,0, 1 Seconds,		Pickup,-4,0,0,0,1 Seconds,		Shoot,0,0,0,0, 0.75 Seconds,	Hold,0,-6,0,0, 1 Seconds,		Hold,-6,0,0,0, 2 Seconds, Hold,0,0,0,0, 0.25 Seconds};
		case 'blueAmpRun': return			std::vector<float>{Shoot,0,0,0,0, 1 Seconds,	Hold,-1.5,-0.5,0,0, 1 Seconds,	Hold,0,0,-50,0, 1 Seconds,			Hold,-7,0,-8,0, 3 Seconds,		Hold,0,0,0,0, 0.25 Seconds};
		case 'blueAmpDelay': return			std::vector<float>{Shoot,0,0,0,0, 1 Seconds,	Hold,0,0,0,0, 3 Seconds,		Hold,-1.5,-0.5,0,0, 1 Seconds,		Hold,0,0,-50,0, 1 Seconds,		Hold,-7,0,-8,0, 3 Seconds,		Hold,0,0,0,0, 0.25 Seconds};
		case 'redSourceBasic': return		std::vector<float>{Shoot,0,0,0,0, 1 Seconds,	Hold,-1.5,-1.5,0,0, 1 Seconds,	Hold,0,0,-55,0, 1 Seconds,			Hold,0,-2,0,0, 1 Seconds,		Pickup,-4,0,0,0, 1 Seconds,		Shoot,0,0,0,0, 0.75 Seconds,	Hold,0,6,0,0, 1 Seconds,		Hold,-6,0,0,0, 2 Seconds, Hold,0,0,0,0, 0.25 Seconds};
		case 'redSourceRun': return			std::vector<float>{Shoot,0,0,0,0, 1 Seconds,	Hold,-1.5,0,0,0, 1 Seconds,		Hold,0,0,-60,0, 1 Seconds,			Hold,0,5,0,0, 2 Seconds,		Hold,-6,0,-10,0, 3 Seconds, 	Hold,0,0,0,0, 0.25 Seconds};
		case 'redSourceDelay': return		std::vector<float>{Shoot,0,0,0,0, 1 Seconds,	Hold,0,0,0,0, 3 Seconds,		Hold,-1.5,0,0,0, 1 Seconds,			Hold,0,0,-60,0, 1 Seconds,		Hold,0,4,0,0, 2 Seconds,		Hold,-6,0,-10,0, 3 Seconds,		Hold,0,0,0,0, 0.25 Seconds};
		case 'blueSourceBasic': return		std::vector<float>{Shoot,0,0,0,0, 1 Seconds,	Hold,-1.5,1.5,0,0, 1 Seconds,	Hold,0,0,55,0, 1 Seconds,			Pickup,-6,0,0,0, 1 Seconds,		Shoot,0,0,0,0, 0.75 Seconds,	Hold,-6,0,0,0, 2 Seconds,		Hold,0,0,0,0, 0.25 Seconds};
		case 'blueSourceRun': return		std::vector<float>{Shoot,0,0,0,0, 1 Seconds,	Hold,-1.5,0,0,0, 1 Seconds,		Hold,0,0,60,0, 1 Seconds,			Hold,0,-5,0,0, 2 Seconds,		Hold,-7,0,-3,0, 3 Seconds,		Hold,0,0,0,0, 0.25 Seconds};
		case 'blueSourceDelay': return		std::vector<float>{Shoot,0,0,0,0, 1 Seconds,	Hold,0,0,0,0, 3 Seconds,		Hold,-1.5,0,0,0, 1 Seconds,			Hold,0,0,60,0, 1 Seconds,		Hold,0,-5,0,0, 2 Seconds,		Hold,-7,0,-3,0, 3 Seconds, Hold,0,0,0,0, 0.25 Seconds};
		case 'onlyScore': return			std::vector<float>{Shoot,0,0,0,0, 1 Seconds,	Hold,0,0,0,0, 0.25 Seconds};
		case 'onlyRun': return				std::vector<float>{Hold,6,0,0,0, 3 Seconds, 	Hold,0,0,150,0, 1 Seconds, 		Hold,0,0,0,0, 0.25 Seconds};
		}
	}	

		convertCode(getAuto('redCenterAdvanced'));
}

}

// UwU :3
// Salem & Wyllow