#ifndef _ROBOT_H
#define _ROBOT_H

#include "RobotContainer.hpp"

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;

  void DisabledInit() override;
  void DisabledPeriodic() override;
  void DisabledExit() override;

  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void AutonomousExit() override;

  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TeleopExit() override;

  void TestInit() override;
  void TestPeriodic() override;
  void TestExit() override;

 private:
  frc2::Command* m_autonomousCommand;

  RobotContainer m_container;
};

#endif  // _ROBOT_H