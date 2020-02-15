
#include "Robot.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/phoenix.h>
#include <frc/WPILib.h>
//#include "rev/ColorSensorV3.h"

WPI_VictorSPX WheelBackLeft {2};
WPI_VictorSPX WheelBackRight {1};
WPI_VictorSPX WheelFrontRight {4};
WPI_VictorSPX WheelFrontLeft {3};

frc::MecanumDrive Mecanums {WheelFrontLeft , WheelFrontRight , WheelBackRight , WheelBackLeft};

WPI_TalonSRX BallShootFront {5};
WPI_TalonSRX BallShootBack {6};

frc::VictorSP ElevatorTop {0};
frc::VictorSP ElevatorBottom {1};

frc::Relay BallIntake {9};

frc::Solenoid IntakeLeftOpen {1};
frc::Solenoid IntakeRightOpen {2};

frc::Solenoid IntakeLeftClose {3};
frc::Solenoid IntakeRightClose {4};

frc::Joystick Xbox {0};
frc::Joystick Yoke {1};

/*static constexpr auto i2cPort = frc::I2C::Port::kOnboard;
rev::ColorSensorV3 ColorSensor {i2cPort};*/

bool intakeButton = false;

void Robot::RobotInit() 
{
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  IntakeLeftOpen.SetPulseDuration(0.1);
  IntakeRightOpen.SetPulseDuration(0.1);
  IntakeRightClose.SetPulseDuration(0.1);
  IntakeLeftClose.SetPulseDuration(0.1);
}
void Robot::RobotPeriodic() 
{

}

void Robot::AutonomousInit() 
{
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // Custom Auto goes here
  } else {
    // Default Auto goes here
  }
}

void Robot::AutonomousPeriodic() 
{
  if (m_autoSelected == kAutoNameCustom) 
  {
    // Custom Auto goes here
  } else 
  {
    // Default Auto goes here
  }
}

void Robot::TeleopInit() 
{

}

void Robot::TeleopPeriodic() 
{
  RoboControl();
}

void Robot::TestPeriodic() 
{

}

void Robot::RoboControl()
{
  /*########################################################################################################################
      
                Drivetrain Program

  #########################################################################################################################*/
 
  double xboxLX = Xbox.GetRawAxis(0);
  double xboxRX = Xbox.GetRawAxis(4);

  double xboxRY = Xbox.GetRawAxis(5);
  
  if ((xboxRY > -0.1) && (xboxRY < 0.1))
  {
    xboxRY = 0;
  }

  if ((xboxRX > -0.1) && (xboxRX < 0.1))
  {
    xboxRX = 0;
  }

  if ((xboxLX > -0.1) && (xboxLX < 0.1))
  {
    xboxLX = 0;
  }
  
  Mecanums.DriveCartesian(xboxRX , xboxRY , xboxLX);
  
  /*########################################################################################################################

                Launcher Prototype Program

  #########################################################################################################################*/              
  
  double speedwheel = (Yoke.GetRawAxis(2) * -1);
  speedwheel = ((speedwheel + 1.0) / 2.0);

  if(Yoke.GetRawButton(1))
  {
    BallShootFront.Set(-speedwheel);
    BallShootBack.Set(-speedwheel);
  }
  else 
  {
    BallShootFront.Set(0);
    BallShootBack.Set(0);
  }

/*###########################################################################################################################

                Hanger

  ############################################################################################################################*/   



  /*###########################################################################################################################

                Belt Elevator

  ############################################################################################################################*/  

  if(Xbox.GetRawButton(1))
  {
    ElevatorTop.Set(0.35);
    ElevatorBottom.Set(-0.35);
  }
  else
  {
    ElevatorTop.Set(0);
    ElevatorBottom.Set(0);
  }

  /*###########################################################################################################################

                Ball Intake Arm

  ############################################################################################################################*/   
  
  if(Xbox.GetRawButtonPressed(6))
  {
    intakeButton = !intakeButton;

    if(intakeButton)
    {
      BallIntake.Set(frc::Relay::kOn);

      IntakeRightOpen.StartPulse();
      IntakeLeftOpen.StartPulse();
    }
    else
    {
      BallIntake.Set(frc::Relay::kOff);

      IntakeRightClose.StartPulse();
      IntakeRightOpen.StartPulse();
    }
  }

  
  
  /*###########################################################################################################################

                Color Wheel

  ############################################################################################################################*/              
  
  //std::cout << RawColorString(ColorSensor.GetRawColor()) << std::endl;

}

/*std::string Robot::RawColorString(rev::ColorSensorV3::RawColor rawColor)
{
  std::ostringstream output;
  output << "Color: ";
  output << rawColor.blue << ", ";
  output << rawColor.red << ", ";
  output << rawColor.ir << ", ";
  output << rawColor.green << ", ";
  
  return output.str();
}*/

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
