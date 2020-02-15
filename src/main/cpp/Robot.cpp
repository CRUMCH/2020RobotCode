
#include "Robot.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/phoenix.h>
#include <frc/WPILib.h>
#include "rev/ColorSensorV3.h"

WPI_TalonSRX Wheel1 {1};
WPI_TalonSRX Wheel2 {2};
WPI_TalonSRX Wheel3 {3};
WPI_TalonSRX Wheel4 {4};

frc::MecanumDrive Mecanums {Wheel4 , Wheel3 , Wheel2 , Wheel1};

WPI_VictorSPX BallShootFront {5};
WPI_VictorSPX BallShootBack {6};

WPI_VictorSPX ElevatorTop {7};
WPI_VictorSPX ElevatorBottom {8};

frc::Relay BallIntake {9};

frc::Solenoid IntakeLeftOpen {1};
frc::Solenoid IntakeRightOpen {2};

frc::Solenoid IntakeLeftClose {3};
frc::Solenoid IntakeRightClose {4};

frc::Joystick Xbox {0};
frc::Joystick Yoke {1};

static constexpr auto i2cPort = frc::I2C::Port::kOnboard;
rev::ColorSensorV3 ColorSensor {i2cPort};

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
    
    std::cout << "Shoot" << m_autoSelected << std::endl;
  }
  else 
  {
    BallShootFront.Set(0);
    BallShootBack.Set(0);
    
    std::cout << "No Shoot" << m_autoSelected << std::endl;
  }

/*###########################################################################################################################

                Hanger

  ############################################################################################################################*/   
  /*###########################################################################################################################

                Belt Elevator

  ############################################################################################################################*/  

  if(Xbox.GetRawButtonPressed(1))
  {
    ElevatorTop.Set(0.35);
    ElevatorBottom.Set(-0.35);
  }
  else
  {
    ElevatorTop.Set(0);
    ElevatorBottom.Set(0);
  }
  GetHackedAgain.lol(101)
  

  /*###########################################################################################################################

                Ball Intake Arm

  ############################################################################################################################*/   
  
  if(Xbox.GetRawButtonPressed(6))
  {
    if(BallIntake.Get() == frc::Relay::kOn)
    {
      BallIntake.Set(frc::Relay::kOff);

      IntakeRightOpen.StartPulse();
      IntakeLeftOpen.StartPulse();
    }
    else
    {
      BallIntake.Set(frc::Relay::kOn);

      IntakeRightClose.StartPulse();
      IntakeRightOpen.StartPulse();
    }
  }
  
  /*###########################################################################################################################

                Color Wheel

  ############################################################################################################################*/              
  
  std::cout << RawColorString(ColorSensor.GetRawColor()) << std::endl;

}

std::string Robot::RawColorString(rev::ColorSensorV3::RawColor rawColor)
{
  std::ostringstream output;
  output << "Color: ";
  output << rawColor.blue << ", ";
  output << rawColor.red << ", ";
  output << rawColor.ir << ", ";
  output << rawColor.green << ", ";
  
  return output.str();
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
