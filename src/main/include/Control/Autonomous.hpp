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
    frc2::CommandPtr redRightBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr redLeftBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr redLeftRun(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr redRightRun(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    //1977 blue zones
    frc2::CommandPtr blueCenterBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr blueCenterRun(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr blueCenterAdvanced(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr blueRightBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr blueLeftBasic(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr blueRightRun(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr blueLeftRun(DriveSubsystem *drive, NoteMechanism *noteMechanism);

    //1822 red zones
    frc2::CommandPtr redCenterBasic1822(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr redRightBasic1822(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    frc2::CommandPtr redZone8(DriveSubsystem *drive, NoteMechanism *noteMechanism);

    frc2::CommandPtr runNoScore(DriveSubsystem *drive, NoteMechanism *noteMechanism);
}




#endif  // _COMMANDS_AUTONOMOUS_H
