
#pragma once
#include <string>
#include "rev/ColorSensorV3.h"
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;
  

 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoNameDefault = "Default";
  const std::string kAutoNameCustom = "My Auto";
  std::string m_autoSelected;
  std::string RawColorString(rev::ColorSensorV3::RawColor);
  void RunDriveTrain();
  void RunLauncher();
  void RunHanger();
  void RunElevator();
  void RunIntakeArm();
  void RunColorWheel();
  void ControlByButtons();
  void ShooterTest();
};
