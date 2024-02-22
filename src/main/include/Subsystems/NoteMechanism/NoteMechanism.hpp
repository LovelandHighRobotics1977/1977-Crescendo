#ifndef _NOTE_MECHANIMS_H
#define _NOTE_MECHANISM_H

#include "headers/Headers.hpp"
#include "Intake.hpp"
#include "Shooter.hpp"

class NoteMechanism : public frc2::SubsystemBase {
	public:
		NoteMechanism();

		frc2::StartEndCommand PickupNote();
		frc2::StartEndCommand ReverseNote();
		frc2::StartEndCommand ShootNote();

		frc2::FunctionalCommand RaiseShooter();
		frc2::StartEndCommand LowerShooter();


	private:

        Intake m_intake;
		Shooter m_shooter;

		frc::DigitalInput m_angleLimitSwitch{Mechanism::Shooter::Limit};

};

#endif // _NOTE_MECHANISM_H