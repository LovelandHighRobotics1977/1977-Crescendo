#ifndef _HEADERS_H
#define _HEADERS_H

// Project Info, contains credits, license, and other important stuffs
#include "ProjectInfo.h"

// Libraries ( very important )
#include "Libraries.h"

// Controllers and control schemes
#include "Control/Controllers.h" 

// Custom defined utility structs and functions ( nice and useful )
#include "Util.h" 

// Singleton classes to prevent duplicates of objects
#include "Subsystems/Devices/Devices.h"

// Robot specifications, ROBOT SPECIFIC
// Select the specific robot in the RobotSpecifications.h file
#include "RobotBase/Specifications/RobotSpecifications.h"

// Robot parameters, NOT robot specific
#include "RobotBase/Parameters/RobotParameters.h"

#endif  // _HEADERS_H