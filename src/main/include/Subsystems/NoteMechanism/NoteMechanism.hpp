#ifndef _NOTE_MECHANIMS_H
#define _NOTE_MECHANISM_H

#include "headers/Headers.hpp"
#include "Intake.hpp"
#include "Shooter.hpp"
#include "Control/Controllers.hpp"
class NoteMechanism : public frc2::SubsystemBase {
	public:
		NoteMechanism();

		frc2::StartEndCommand PickupNote();
		frc2::StartEndCommand ReverseNote();
		frc2::SequentialCommandGroup ShootNote();

		void AngleShooter(); // Should be run as a default command.  The driver will not have to adjust shooter angle.  

	private:

        Intake m_intake;
		Shooter m_shooter;

};

#endif // _NOTE_MECHANISM_H