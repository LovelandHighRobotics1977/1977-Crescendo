#ifndef _HEADERS_H
#define _HEADERS_H

// Project Info, contains credits, license, and other important stuffs
// I don't care Dean. This is staying and you can cry about it.  
#include "ProjectInfo.hpp"

// Libraries ( very important )
#include "Libraries.hpp"

// Controllers and control schemes
#include "Control/Controllers.hpp" 

// Custom defined utility structs and functions ( nice and useful )
#include "Util.hpp" 

// Singleton classes to prevent duplicates of objects
#include "Subsystems/Devices/Devices.hpp"

// Robot specifications, ROBOT SPECIFIC
// Select the specific robot in the RobotSpecifications.h file
#include "RobotBase/Specifications/RobotSpecifications.hpp"

// Robot parameters, NOT robot specific
#include "RobotBase/Parameters/RobotParameters.hpp"

#endif  // _HEADERS_H