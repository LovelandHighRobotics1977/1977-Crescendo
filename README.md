Robot code for the 2024 FRC game Crecendo

This is the known working code, should be used as a base.

> [!WARNING]  
> This code WILL be overwritten at some point, and is subject to random-ass changes on a whim
> > IE: when I forget which branch I'm on

---

# Resources

Swerve Kinematics on Desmos:

https://www.desmos.com/calculator/myakquqqoo

---

Control Scheme ( ish )

https://docs.google.com/drawings/d/1p3c9jcidOoOzF_-JU_dmr4nJALmn3ofQrwjj6wKX1FM/edit?usp=sharing

---

CAN Device ID and naming scheme ( 2024 ):


| ID |    Swerve ( 1977 )    |    Swerve ( 1822 )   |       Westcoast      |
|:--:|:---------------------:|:--------------------:|:--------------------:|
|  0 | Roborio               | Roborio              | Roborio / CTRE PDP   |
|  1 | REV PDH               | REV PDH              | **---- Reserved ----**  |
|  2 | Front Right Drive     | Front Right Drive    | Right Front Drive    |
|  3 | Front Right Angle     | Front Right Angle    | Right Rear Drive     |
|  4 | Front Right Sensor    | Front Right Sensor   | Left Front Drive     |
|  5 | Rear Right Drive      | Rear Right Drive     | Left Rear Drive      |
|  6 | Rear Right Angle      | Rear Right Angle     | **---- Unassigned ----** |
|  7 | Rear Right Sensor     | Rear Right Sensor    | **---- Unassigned ----** |
|  8 | Rear Left Drive       | Rear Left Drive      | **---- Unassigned ----** |
|  9 | Rear Left Angle       | Rear Left Angle      | **---- Unassigned ----** |
| 10 | Rear Left Sensor      | Rear Left Sensor     | **---- Unassigned ----** |
| 11 | Front Left Drive      | Front Left Drive     | **---- Unassigned ----** |
| 12 | Front Left Angle      | Front Left Angle     | **---- Unassigned ----** |
| 13 | Front Left Sensor     | Front Left Sensor    | **---- Unassigned ----** |
| 14 | Intake                | Intake               | Intake               |
| 15 | Shooter Top           | Shooter Top          | Shooter Top          |
| 16 | Shooter Bottom        | Shooter Bottom       | Shooter Bottom       |
| 17 | Shooter Angle         | Shooter Angle        | Shooter Angle        |
| 18 | Climber               | Climber              | Climber              |
| 19 | Shooter Angle Encoder | **---- Unassigned ----** | **---- Unassigned ----** |
| 20 | **---- Unassigned ----** | **---- Unassigned ----** | **---- Unassigned ----** |

```
 __         __     ______     ______     __   __     ______     ______    
╱╲ ╲       ╱╲ ╲   ╱╲  ___╲   ╱╲  ___╲   ╱╲ "-.╲ ╲   ╱╲  ___╲   ╱╲  ___╲   
╲ ╲ ╲____  ╲ ╲ ╲  ╲ ╲ ╲____  ╲ ╲  __╲   ╲ ╲ ╲-.  ╲  ╲ ╲___  ╲  ╲ ╲  __╲   
 ╲ ╲_____╲  ╲ ╲_╲  ╲ ╲_____╲  ╲ ╲_____╲  ╲ ╲_╲╲"╲_╲  ╲╱╲_____╲  ╲ ╲_____╲ 
  ╲╱_____╱   ╲╱_╱   ╲╱_____╱   ╲╱_____╱   ╲╱_╱ ╲╱_╱   ╲╱_____╱   ╲╱_____╱ 
```                                   

Copyright (c) FIRST and other WPILib contributors. 
Open Source Software; you can modify and╱or share it under the terms of 
the WPILib BSD license file in the root directory of this project.

The license is also pasted below for reference:

================

Copyright (c) 2009-2024 FIRST and other WPILib contributors
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and╱or other materials provided with the distribution.
   * Neither the name of FIRST, WPILib, nor the names of other WPILib
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY FIRST AND OTHER WPILIB CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY NONINFRINGEMENT AND FITNESS FOR A PARTICULAR
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL FIRST OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

================

```
 ______     ______     ______     _____     __     ______   ______    
╱╲  ___╲   ╱╲  == ╲   ╱╲  ___╲   ╱╲  __-.  ╱╲ ╲   ╱╲__  _╲ ╱╲  ___╲   
╲ ╲ ╲____  ╲ ╲  __<   ╲ ╲  __╲   ╲ ╲ ╲╱╲ ╲ ╲ ╲ ╲  ╲╱_╱╲ ╲╱ ╲ ╲___  ╲  
 ╲ ╲_____╲  ╲ ╲_╲ ╲_╲  ╲ ╲_____╲  ╲ ╲____-  ╲ ╲_╲    ╲ ╲_╲  ╲╱╲_____╲ 
  ╲╱_____╱   ╲╱_╱ ╱_╱   ╲╱_____╱   ╲╱____╱   ╲╱_╱     ╲╱_╱   ╲╱_____╱ 
```

Lead Programmer: 
    - Salem Lessem
      https://github.com/ThatAlo

Assistant Programmer: 
    - Dean Morgan
      https://github.com/Dean27817

Loveland High Robotics programming team:
    [ Wyllow  ]      [ Dinesh ]
    [ Collin  ]      [ Jacob  ]
    [ Bradley ]      [ Willem ]

Team mentors:
    - Mike Pintaric
    - Bruce Bowman

FRC teams:
    - 1977: The PowerSquids
    - 1822: Electric Calamari

Sites I used for this file to make it look *fancy*:
    - https://tree.nathanfriend.io/
    - https://patorjk.com/software/taag/
                
| File       |               |                      |                         | Purpose                                                                                                                      |
|------------|---------------|----------------------|-------------------------|------------------------------------------------------------------------------------------------------------------------------|
| `cpp/`     |               |                      |                         | Defines the logic of the various components                                                                                  |
|            | `Commands/`   |                      |                         |                                                                                                                              |
|            |               | `autonomous.cpp`     |                         | Defines the logic for the autonomous routines                                                                                |
|            | `RobotBase/`  |                      |                         |                                                                                                                              |
|            |               | `Robot.cpp`          |                         | Calls the command scheduler, essentially boilerplate                                                                         |
|            |               | `RobotContainer.cpp` |                         | The structure of the robot (including subsystems, commands, autonomous routines, and button mappings) is declared here       |
|            | `Subsystems/` |                      |                         |                                                                                                                              |
|            |               | `Climber/`           |                         |                                                                                                                              |
|            |               |                      | `Climber.cpp`           | Declares the climber components and defines climber logic                                                                    |
|            |               |                      | `Actuator.cpp`          | Controls the actuator motor                                                                                                  |
|            |               | `Drivetrain/`        |                         |                                                                                                                              |
|            |               |                      | `Commands.cpp`          | Advanced drivetrain commands, such as path following and odometry manipulation.                                              |
|            |               |                      | `Drivetrain.cpp`        | Declares the swerve modules and defines drivetrain logic.                                                                    |
|            |               |                      | `SwerveModule.cpp`      | Manages the control of the individual module, reports odometry data to the drivetrain.                                       |
|            |               | `NoteMechanism/`     |                         |                                                                                                                              |
|            |               |                      | `NoteMechanism.cpp`     | Declares Note Mechanism components and defines Note Mechanism logic                                                          |
|            |               |                      | `Intake.cpp`            | Manages the control of the intake motors                                                                                     |
|            |               |                      | `Shooter.cpp`           | Manages the control of the shooter motors                                                                                    |
| `include/` |               |                      |                         | Provides headers for ease of use, controls what components are part of what                                                  |
|            | `Control/`    |                      |                         |                                                                                                                              |
|            |               | `Controllers.h`      |                         | Seperates the controllers from the program, allowing hot swappable controllers and custom control schemes                    |
|            | `Headers/`    |                      |                         |                                                                                                                              |
|            |               | `Headers.h`          |                         | Manages file inclusion and should be included in every file not included in it                                               |
|            |               | `Libraries.h`        |                         | Includes ALL libraries for use in the program (std and 3rd party)                                                            |
|            |               | `Util.h`             |                         | Utility variables and structs that make passing data around the project easier.  Used extensively in the drivetrain          |
|            | `RobotBase/`  |                      |                         |                                                                                                                              |
|            |               | `Parameters/`        |                         |                                                                                                                              |
|            |               |                      | `AutoParameters.h`      | Autonomous mode parameters, non robot specific.                                                                              |
|            |               |                      | `MechParameters.h`      | Mechanism parameters, including motor IDs and configuration values                                                           |
|            |               |                      | `TeleopParameters.h`    | Teleoperated mode parameters, incuding control preferences                                                                   |
|            |               |                      | `RobotParameters.h`     | Combines the 3 previous files into one for easy inclusion                                                                    |
|            |               | `Specifications/`    |                         |                                                                                                                              |
|            |               |                      | `RobotSpecifications.h` | Manages the inclusion of robot specific variables, such as magnet offset.  Includes all other files in the directory (sorta) |
|            |               |                      | `*Robot_Name*.h`        | Specifications for a specific robot, usually denoted by a specific name                                                      |
|            | `Devices/`    |                      |                         |                                                                                                                              |
|            |               | `Devices.h`          |                         | Includes all files in the Devices directory for easy inclusion                                                               |
|            |               | `*Device*.h`         |                         | Singleton class to allow access to devices throughout the program, such as the gyro or the PDH                               |
|            |               |                      |                         |                                                                                                                              |
|            |               |                      |                         |                                                                                                                              |
