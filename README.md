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
