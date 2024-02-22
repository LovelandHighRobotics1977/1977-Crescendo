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
}



#endif  // _COMMANDS_AUTONOMOUS_H
