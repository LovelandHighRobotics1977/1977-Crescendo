#ifndef _ROBOT_SPECIFICATIONS_H
#define _ROBOT_SPECIFICATIONS_H

/**
 *  Per robot Constants 
 * 
 * Define a macro for the specific drivetrain or robot you are using to include only that robots specifications.  
 * 
 * Current Robots:
 * - _FullBotKrakens
 * - _GenericFalconsBot
 */ 
#define _GenericFalconsBot

#if defined(_GenericFalconsBot)
#include "RobotBase/Specifications/GenericFalcons.h"
#elif defined(_FullBotKrakens)
#include "RobotBase/Specifications/FullBotKrakens.h"
#else
#error "No Robot Specified, Please define a robot"
#endif

#endif