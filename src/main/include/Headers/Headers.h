#ifndef _HEADERS_H
#define _HEADERS_H

/**
 * Copyright (c) FIRST and other WPILib contributors. 
 * Open Source Software; you can modify and/or share it under the terms of 
 * the WPILib BSD license file in the root directory of this project.
*/

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