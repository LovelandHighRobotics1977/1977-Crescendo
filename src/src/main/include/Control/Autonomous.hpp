#ifndef _COMMANDS_AUTONOMOUS_H
#define _COMMANDS_AUTONOMOUS_H

#include "headers/Headers.hpp"

#include "subsystems/Drivetrain/DriveSubsystem.hpp"
#include "Subsystems/Climber/Climber.hpp"
#include "Subsystems/NoteMechanism/NoteMechanism.hpp"

#include "subsystems/Drivetrain/Commands.hpp"

namespace AutoRoutine {
    frc2::CommandPtr test(DriveSubsystem *drive);
    frc2::CommandPtr square(DriveSubsystem *drive);
    //the center
    frc2::CommandPtr zone1(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    //the right side
    frc2::CommandPtr zone2(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    //the left side
    frc2::CommandPtr zone3(DriveSubsystem *drive, NoteMechanism *noteMechanism);
    //alternative middle position that goes under the stage
    frc2::CommandPtr zone4(DriveSubsystem *drive, NoteMechanism *noteMechanism);
}




#endif  // _COMMANDS_AUTONOMOUS_H
