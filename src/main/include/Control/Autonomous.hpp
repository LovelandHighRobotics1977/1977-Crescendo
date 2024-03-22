#ifndef _COMMANDS_AUTONOMOUS_H
#define _COMMANDS_AUTONOMOUS_H

#include "headers/Headers.hpp"

#include "subsystems/Drivetrain/DriveSubsystem.hpp"
#include "Subsystems/Climber/Climber.hpp"
#include "Subsystems/NoteMechanism/NoteMechanism.hpp"

#include "subsystems/Drivetrain/Commands.hpp"

/*
Run : Shoot once and skedaddle ( In center : goes under the stage )
Basic : Shoot once, pickup and shoot, and skedaddle ( ONLY WORKS ON CENTER )
Advanced : Score as much as possible while still exiting ( ONLY WORKS ON CENTER ) ( UNRELIABLE )
Delay : Shoot, Wait 3 seconds, Do most advanced auto
Maximum : Score as much as possible ( CANNOT EXIT ) ( ONLY WORKS ON CENTER )
*/

namespace AutoRoutine {
    //1977 red zones
    frc2::CommandPtr redCenterBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr redCenterRun(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr redCenterAdvanced(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr redCenterDelay(DriveSubsystem *drive, NoteMechanism *noteMechanism);

    frc2::CommandPtr redSourceBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr redSourceRun(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr redSourceDelay(DriveSubsystem *drive, NoteMechanism *noteMechanism);

    frc2::CommandPtr redAmpBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr redAmpRun(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr redAmpDelay(DriveSubsystem *drive, NoteMechanism *noteMechanism);


    //1977 blue zones
    frc2::CommandPtr blueCenterBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr blueCenterRun(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr blueCenterAdvanced(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr blueCenterDelay(DriveSubsystem *drive, NoteMechanism *noteMechanism);

    frc2::CommandPtr blueAmpBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr blueAmpRun(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr blueAmpDelay(DriveSubsystem *drive, NoteMechanism *noteMechanism);

    frc2::CommandPtr blueSourceBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr blueSourceRun(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr blueSourceDelay(DriveSubsystem *drive, NoteMechanism *noteMechanism);

    frc2::CommandPtr onlyScore(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr onlyRun(DriveSubsystem *drive, NoteMechanism *noteMechanism);
}




#endif  // _COMMANDS_AUTONOMOUS_H