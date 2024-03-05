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


                               License                                             

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

 
                                                                      
                                Credits

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


 
                                                                                               
                                            Structure

.
└── Main/<br>
    ├── cpp/<br>
    │   ├── Control/<br>
    │   │   └── Autonomous.cpp<br>
    │   ├── RobotBase/<br>
    │   │   ├── Robot.cpp<br>
    │   │   └── RobotContainer.cpp<br>
    │   └── Subsystems/<br>
    │       ├── Drivetrain/<br>
    │       │   ├── Commands.cpp<br>
    │       │   ├── DriveSubsystem.cpp<br>
    │       │   └── SwerveModule.cpp<br>
    │       ├── NoteMechanism/<br>
    │       │   ├── Intake.cpp<br>
    │       │   ├── NoteMechanism.cpp<br>
    │       │   └── Shooter.cpp<br>
    │       └── Climber/<br>
    │           ├── Climber.cpp<br>
    │           └── Actuator.cpp<br>
    └── include/<br>
        ├── Control/<br>
        │   ├── Autonomous.h<br>
        │   └── Controllers.h<br>
        ├── Headers╱<br>
        │   ├── Headers.h<br>
        │   ├── Libraries.h<br>
        │   ├── ProjectInfo.h<br>
        │   └── Util.h<br>
        ├── RobotBase/<br>
        │   ├── Parameters/<br>
        │   │   ├── AutoParameters.h<br>
        │   │   ├── MechParameters.h<br>
        │   │   ├── RobotParameters.h        { Include this file to include all parameters }<br>
        │   │   └── TeleopParameters.h<br>
        │   ├── Specifications/<br>
        │   │   ├── FullBotKrakens.h<br>
        │   │   ├── GenericFalcons.h<br>
        │   │   └── RobotSpecifications.h    { Include this file to include correct specifications }<br>
        │   ├── Robot.h<br>
        │   └── RobotContainer.h<br>
        └── Subsystems/<br>
            ├── Devices/<br>
            │   ├── Devices.h<br>
            │   ├── Field.h<br>
            │   ├── Gyro.h<br>
            │   └── PDH.h<br>
            ├── Drivetrain/<br>
            │   ├── Commands.h<br>
            │   ├── DriveSubsystem.h<br>
            │   └── SwerveModule.h<br>
            ├── NoteMechanism/<br>
            │   ├── Intake.h<br>
            │   ├── NoteMechanism.h<br>
            │   └── Shooter.h<br>
            └── Climber/<br>
                ├── Climber.h<br>
                └── Actuator.h<br>
                
| file name | what it does |
|:---------:|:------------:|
|Main/cpp/Controll/Autonomous.cpp| Sends the commands for the autonomus routine |
|Main/cpp/RobotBase/Robot.cpp| Calls the command based skeleton. Basically boilerplate |
|Main/cpp/RobotBase/RobotContainer.cpp| The heart of the program. This calls the default triggers, as well as cofigures the button bindings |
|Main/cpp/Subsystems/Drivetrain/Commands.cpp| sets the commands for the drivetrain. this includes the commands to set the trajectory and the pid tuners |
|Main/cpp/Subsystems/Drivetrain/DriveSubsystem.cpp| sets up each swerve module and the kinimatics for the swerve modules |
|Main/cpp/Subsystems/Drivetrain/SwerveModule.cpp| use |
|Main/cpp/Subsystems/NoteMechanism/Intake.cpp| use |
|Main/cpp/Subsystems/NoteMechanism/NoteMechanism.cpp| use |
|Main/cpp/Subsystems/NoteMechanism/Shooter.cpp| use |
|Main/cpp/Subsystems/Climber/Climber.cpp| Uses Actuator.cpp to controll the opening and closing of the pull up mech |
|Main/cpp/Subsystems/Climber/Actuator.cpp| Declares the defaults for the climber motor as well as setting speed and direction of said motor |
|Main/include/Control/Autonomous.h| use |
|Main/include/Control/Controllers.h| use |
|Main/include/Headers/Headers.h| use |
|Main/include/Headers/Librarys.h| use |
|Main/include/Headers/ProjectInfo.h| use |
|Main/include/Headers/Util.h| use |
|Main/include/RobotBase/Parameters/AutoParameters.h| use |
|Main/include/RobotBase/Parameters/MechParameters.h| use |
|Main/include/RobotBase/Parameters/RobotParameters.h| use |
|Main/include/RobotBase/Parameters/TeleopParameters.h| use |
|Main/include/RobotBase/Specifications/FullBotKrakens.h| use |
|Main/include/RobotBase/Specifications/GenericFalcons.h| use |
|Main/include/RobotBase/Specifications/RobotSpecifications.h| use |
|Main/include/RobotBase/Robot.h| use |
|Main/include/RobotBase/RobotContainer.h| use |
|Main/include/Subsystems/Devices/Devices.h| use |
|Main/include/Subsystems/Devices/Field.h| use |
|Main/include/Subsystems/Devices/Gyro.h| use |
|Main/include/Subsystems/Devices/PDH.h| use |
|Main/include/Subsystems/Drivetrain/Commands.h| use |
|Main/include/Subsystems/Drivetrain/DriveSubsystem.h| use |
|Main/include/Subsystems/Drivetrain/SwerveModule.h| use |
|Main/include/Subsystems/NoteMechanism/Intake.h| use |
|Main/include/Subsystems/NoteMechanism/NoteMechanism.h| use |
|Main/include/Subsystems/NoteMechanism/Shooter.h| use |
|Main/include/Subsystems/Climber/Climber.h| use |
|Main/include/Subsystems/Climber/Actuator.h| use |

