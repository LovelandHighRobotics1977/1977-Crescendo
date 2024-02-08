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
 * 
 * Robots salem wants:
 * - _KrakenOne                     (kraken x60s)
 * - _KrakenTwo                     (kraken x60s)
 * - _Programming (Salem's swerve)  (kraken x60s drive, falcons angle)
 */ 
#define _FullBotKrakens

#if defined(_GenericFalconsBot)
#include "RobotBase/Specifications/GenericFalcons.h"
#elif defined(_FullBotKrakens)
#include "RobotBase/Specifications/FullBotKrakens.h"
#elif defined(_KrakenOne)
#include "RobotBase/Specifications/KrakenOne.h"
#elif defined(_KrakenTwo)
#include "RobotBase/Specifications/KrakenTwo.h"
#elif defined(_Programming)
#include "RobotBase/Specifications/Programming.h"
#else
#error "No Robot Specified, Please define a robot"
#endif

#endif