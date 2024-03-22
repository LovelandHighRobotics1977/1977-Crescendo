#ifndef _COMMANDS_AUTONOMOUS_H
#define _COMMANDS_AUTONOMOUS_H

#include "headers/Headers.hpp"

#include "subsystems/Drivetrain/DriveSubsystem.hpp"
#include "Subsystems/Climber/Climber.hpp"
#include "Subsystems/NoteMechanism/NoteMechanism.hpp"

#include "subsystems/Drivetrain/Commands.hpp"

namespace AutoRoutine {
    //1977 red zones
    frc2::CommandPtr redCenterBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr redCenterRun(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr redCenterAdvanced(DriveSubsystem *drive, NoteMechanism *noteMechanism);

    frc2::CommandPtr redSourceBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr redSourceRun(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr redAmpBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr redAmpRun(DriveSubsystem *drive, NoteMechanism *noteMechanism);

    //1977 blue zones
    frc2::CommandPtr blueCenterBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr blueCenterRun(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr blueCenterAdvanced(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr blueAmpBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr blueAmpRun(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr blueSourceBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr blueSourceRun(DriveSubsystem *drive, NoteMechanism *noteMechanism);

    frc2::CommandPtr onlyScore(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr onlyRun(DriveSubsystem *drive, NoteMechanism *noteMechanism);
}




#endif  // _COMMANDS_AUTONOMOUS_H