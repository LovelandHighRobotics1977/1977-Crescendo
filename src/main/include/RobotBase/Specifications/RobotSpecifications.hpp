#ifndef _ROBOT_SPECIFICATIONS_H
#define _ROBOT_SPECIFICATIONS_H

/**
 *  Per robot Constants 
 * 
 * Define a macro for the specific drivetrain or robot you are using to include only that robots specifications.  
 * 
 * Current Robots:
 * - _1977Comp
 * - _1822Comp
 */ 
#define _1977Comp

#if defined(_1977Comp)
#include "RobotBase/Specifications/1977Comp.hpp"
#elif defined(_1822Comp)
#include "RobotBase/Specifications/1822Comp.hpp"
#elif defined(_Extra)
#include "RobotBase/Specifications/ExtraBot.hpp" //Team 1977, torn down bot
#else
#error "No Robot Specified, Please define a robot"
#endif

#endif