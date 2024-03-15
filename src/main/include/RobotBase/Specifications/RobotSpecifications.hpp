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
 * - _1822bot
 * 
 * Robots salem wants:
 * - _KrakenOne                     (kraken x60s)
 * - _KrakenTwo                     (kraken x60s)
 * 
 * - _Programming (Salem's swerve)  (kraken x60s drive, falcons angle)
 */ 
#define _SalemsBot

#if defined(_GenericFalconsBot)
#include "RobotBase/Specifications/GenericFalcons.hpp"
#elif defined(_FullBotKrakens)
#include "RobotBase/Specifications/FullBotKrakens.hpp"
#elif defined(_1822bot)
#include "RobotBase/Specifications/1822bot.hpp"
#elif defined(_SalemsBot)
#include "RobotBase/Specifications/SalemsBot.hpp"
#else
#error "No Robot Specified, Please define a robot"
#endif

#endif