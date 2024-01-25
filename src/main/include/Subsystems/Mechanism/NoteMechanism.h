#ifndef _NOTE_MECHANIMS_H
#define _NOTE_MECHANISM_H

#include "headers/Headers.h"
#include "Intake.h"
#include "Shooter.h"

class NoteMechanism : public frc2::SubsystemBase {
	public:
		NoteMechanism();

		//frc2::StartEndCommand PickupNote();
		frc2::StartEndCommand ShootNote();


	private:

        //Intake m_intake;
		Shooter m_shooter;

};

#endif // _NOTE_MECHANISM_H