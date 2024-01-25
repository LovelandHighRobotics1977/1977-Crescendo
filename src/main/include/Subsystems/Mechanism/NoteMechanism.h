#ifndef _NOTE_MECHANIMS_H
#define _NOTE_MECHANISM_H

#include "headers/Headers.h"
#include "Intake.h"

class NoteMechanism : public frc2::SubsystemBase {
	public:
		NoteMechanism();

		frc2::StartEndCommand PickupNote();


	private:

        Intake m_intake;

};

#endif // _NOTE_MECHANISM_H