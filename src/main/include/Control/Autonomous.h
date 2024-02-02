#ifndef _COMMANDS_AUTONOMOUS_H
#define _COMMANDS_AUTONOMOUS_H

#include "headers/Headers.h"

#include "subsystems/Drivetrain/DriveSubsystem.h"

#include "subsystems/Drivetrain/Commands.h"

namespace AutoRoutine {
    frc2::CommandPtr test(DriveSubsystem *drive);
    frc2::CommandPtr square(DriveSubsystem *drive);
}



#endif  // _COMMANDS_AUTONOMOUS_H
