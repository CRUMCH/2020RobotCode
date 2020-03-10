
#include "Robot.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/phoenix.h>
#include <frc/WPILib.h>
#include "rev/ColorSensorV3.h"

WPI_VictorSPX WheelBackLeft {3};
WPI_VictorSPX WheelBackRight {4};
WPI_VictorSPX WheelFrontRight {2};
WPI_VictorSPX WheelFrontLeft {1};

frc::MecanumDrive Mecanums {WheelFrontLeft , WheelBackLeft , WheelFrontRight , WheelBackRight};

WPI_TalonSRX BallShootUp {1};
WPI_TalonSRX BallShootSide {2};

frc::VictorSP BallShootUpper {5};
frc::VictorSP BallShootLower {6};

frc::VictorSP ElevatorTop {0};
frc::VictorSP ElevatorBottom {1};

frc::VictorSP HangerUp {4};
frc::VictorSP HangerSide {0};

frc::VictorSP ColorWheelSpin {7}; // ?

frc::Relay BallIntake {2};

frc::Solenoid IntakeOpen {0};
frc::Solenoid IntakeClose {1};

frc::Solenoid ColorWheelOpen {2};
frc::Solenoid ColorWheelClose {3};

frc::Joystick Xbox {0};
frc::Joystick Yoke {1};
frc::Joystick ControllerThingy {2}; // ?

// PWM ports 10-19 refer to those on the Rev MoreBoard

frc::DigitalInput PresenceSensorFirst {5}; // Photoelectric Sensor ?
frc::DigitalInput PresenceSensorSecond {6}; // Photoelectric Sensor ?
int psFirstVal = PresenceSensorFirst.Get();

frc::DigitalInput ShooterLimitY {0};
frc::DigitalInput ShooterLimitXRight {2};
frc::DigitalInput ShooterLimitXLeft {1};
frc::DigitalInput BalanceLeft {3};
frc::DigitalInput BalanceRight {4};
frc::DigitalInput ClimberUpperLimit {5};

// Communication With Arduino WIP

static constexpr auto usb = frc::SerialPort::Port::kUSB;
frc::SerialPort PixyCam {19200, usb};
std::string PixyCamStr = "";
char PixyArray [80];
int pixyCamX = 0;
int pixyCamY = 0;

std::string colorVisionStr = "";

bool psFirstOn = false;
bool psSecondOn = false;
bool psSwitched = false;
int ballCount = 0;

bool colorWheelSwitch = false;
int colorWheelRotationsDoubled = 0;

bool intakeButton = false;

static constexpr auto i2cPort = frc::I2C::Port::kOnboard;
rev::ColorSensorV3 ColorSensor {i2cPort};
rev::ColorSensorV3::RawColor colorRead = ColorSensor.GetRawColor();

void Robot::RobotInit() 
{
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  IntakeOpen.SetPulseDuration(0.1);
  IntakeClose.SetPulseDuration(0.1);

  ColorWheelOpen.SetPulseDuration(0.1);
  ColorWheelClose.SetPulseDuration(0.1);
}

void Robot::RobotPeriodic() 
{
  colorRead = ColorSensor.GetRawColor();
  
  colorVisionStr = RawColorString(colorRead);
  frc::SmartDashboard::PutString("",colorVisionStr);

  // Communication With Arduino WIP

  int size = PixyCam.Read(PixyArray, 80);
  PixyCamStr.clear();
  for(int i = 0; i < size; i++) 
  {
    PixyCamStr += PixyArray[i];
  }
  std::cout << PixyArray;
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
  // RunDriveTrain();
  // RunLauncher();
  // RunHanger();
  // RunElevator();
  // RunIntakeArm();
  // RunColorWheel();
  // ControlByButtons();
  ShooterTest();

  if(Xbox.GetRawButton(1))
  {
  std::cout << psFirstVal << std::endl;
  }
  
  if(Xbox.GetRawButton(2))
  {
    std::cout << ShooterLimitY.Get() << std::endl;
  }

  if(Xbox.GetRawButton(3))
  {
    std::cout << ShooterLimitXRight.Get() << std::endl;
  }

  if(Xbox.GetRawButton(4))
  {
    std::cout << ShooterLimitXLeft.Get() << std::endl;
  }
}

void Robot::TestPeriodic() 
{

}

std::string Robot::RawColorString(rev::ColorSensorV3::RawColor rawColor)
{
  std::ostringstream output;
  output << "Color: ";
  output << rawColor.blue << ", ";
  output << rawColor.red << ", ";
  output << rawColor.green << ", ";
  
  return output.str();
}

/*########################################################################################

          Drive Train

########################################################################################*/

void Robot::RunDriveTrain()
{
  double xboxLX = Xbox.GetRawAxis(0);
  double xboxRX = Xbox.GetRawAxis(4);
  double xboxLY = Xbox.GetRawAxis(1);
  
  if ((xboxLY > -0.1) && (xboxLY < 0.1))
  {
    xboxLY = 0;
  }

  if ((xboxRX > -0.1) && (xboxRX < 0.1))
  {
    xboxRX = 0;
  }

  if ((xboxLX > -0.1) && (xboxLX < 0.1))
  {
    xboxLX = 0;
  }
  
  Mecanums.DriveCartesian(xboxRX , xboxLY , xboxLX);
}

/*########################################################################################

          Launcher

########################################################################################*/

void Robot::RunLauncher()
{ 
  

  if(Xbox.GetRawButton(1))
  {
    BallShootUp.Set(.8);
    BallShootSide.Set(.8);
  }
  else 
  {
    BallShootUp.Set(0);
    BallShootSide.Set(0);
  }
}

/*########################################################################################

          Hanger

########################################################################################*/

void Robot::RunHanger()
{
  int customYAxis = Xbox.GetRawAxis(5);
  int customXAxis = Xbox.GetRawAxis(4);
  
  if(customYAxis < .1 && customYAxis > -.1)
  {
    customYAxis = 0;
  }

  if(customXAxis < .1 && customXAxis > -.1)
  {
    customXAxis = 0;
  }

  if(customYAxis > 0)
  {
    HangerUp.Set(.5);
  }
  else if(customYAxis < 0)
  {
    HangerUp.Set(-.5);
  }
  else
  {
    HangerUp.Set(0);
  }

  if(customXAxis > 0)
  {
    HangerSide.Set(.5);
  }
  else if(customXAxis < 0)
  {
    HangerSide.Set(-.5);
  }
  else
  {
    HangerSide.Set(0);
  }
}

/*########################################################################################

          Elevator

########################################################################################*/

void Robot::RunElevator()
{
  psFirstOn = PresenceSensorFirst.Get();
  psSecondOn = PresenceSensorSecond.Get();
  
  if(ballCount < 5)
  {
    IntakeOpen.StartPulse();

    if(psFirstOn == true)
    {
      ElevatorTop.Set(.5);
      ElevatorBottom.Set(.5);

      if(psSwitched == false)
      {
        ballCount = ballCount + 1;
        psSwitched = true;
      }
    }
    if(psSecondOn == true && psFirstOn == false)
    {
      ElevatorTop.Set(0);
      ElevatorBottom.Set(0);
    }
  }
  else
  {
    IntakeClose.StartPulse();
  }
}

/*########################################################################################

          Intake Arm

########################################################################################*/

void Robot::RunIntakeArm()
{
  if(Xbox.GetRawButtonPressed(6))
  {
    intakeButton = !intakeButton;

    if(intakeButton)
    {
      BallIntake.Set(frc::Relay::kReverse);

      IntakeOpen.StartPulse();

      ElevatorTop.Set(-.5);
      ElevatorBottom.Set(.5);

      BallShootUpper.Set(.8);
      BallShootLower.Set(-.8);
    }
    else
    {
      BallIntake.Set(frc::Relay::kOff);

      IntakeClose.StartPulse();

      ElevatorTop.Set(0);
      ElevatorBottom.Set(0);

      BallShootUpper.Set(0);
      BallShootLower.Set(0);
    }
  }
}

/*########################################################################################

          Color Wheel

########################################################################################*/

void Robot::RunColorWheel()
{
  std::cout << RawColorString(ColorSensor.GetRawColor()) << std::endl;

  if(ControllerThingy.GetRawButtonPressed(1)) // Red
  {
    ColorWheelOpen.StartPulse();

    if(colorRead.blue < 800 && colorRead.green > 200 && colorRead.red > 200) // Search Not Blue
    {
      ColorWheelSpin.Set(.15);
    }
    else
    {
      ColorWheelSpin.Set(0);
    }
  }
  else if(ControllerThingy.GetRawButtonPressed(2)) // Blue
  {
    ColorWheelOpen.StartPulse();

    if(colorRead.blue > 200 && colorRead.green > 200 && colorRead.red < 800) // Search Not Red
    {
      ColorWheelSpin.Set(.15);
    }
    else
    {
      ColorWheelSpin.Set(0);
    }
  }
  else if(ControllerThingy.GetRawButtonPressed(3)) // Green
  {
    ColorWheelOpen.StartPulse();

    if(colorRead.blue < 800 && colorRead.green < 800 && colorRead.red > 200) // Search Not Yellow
    {
      ColorWheelSpin.Set(.15);
    }
    else
    {
      ColorWheelSpin.Set(0);
    }
  }
  else if(ControllerThingy.GetRawButtonPressed(4)) // Yellow
  {
    ColorWheelOpen.StartPulse();

    if(colorRead.blue > 200 && colorRead.green < 800 && colorRead.red > 200) // Search Not Green
    {
      ColorWheelSpin.Set(.15);
    }
    else
    {
      ColorWheelSpin.Set(0);
    }
  }
  else if(ControllerThingy.GetRawButtonPressed(5)) // Stage 1 Multi-Spin
  {
    ColorWheelOpen.StartPulse();

    if(colorWheelRotationsDoubled != 8) // Checking for if the number of half rotations does not equal 8
    {
      ColorWheelSpin.Set(.25);
      
      if(colorWheelSwitch == true && colorRead.blue > 800 && colorRead.green > 800 && colorRead.red < 200) // Search Yellow
      {
        colorWheelSwitch = false; // Setting bool to false so that it can't count one yellow twice
        colorWheelRotationsDoubled = colorWheelRotationsDoubled + 1; // Counting this appearence of yellow (1 half turn)
      }
      else if(colorWheelSwitch == false && colorRead.blue < 800 && colorRead.green < 800 && colorRead.red > 200) // Search Not Yellow
      {
        colorWheelSwitch = true; // Setting bool to true so when "Not Yellow" is found so that future yellow is found later
      }
    }
    else
    {
      ColorWheelSpin.Set(0);
    }
  }
  ColorWheelClose.StartPulse();
}

/*########################################################################################

          Button Control Test

########################################################################################*/

void Robot::ControlByButtons()
{
  if(Xbox.GetRawButton(1))
  {
    WheelBackLeft.Set(.5);
  }
  else
  {
    WheelBackLeft.Set(0);
  }
  
  if(Xbox.GetRawButton(2))
  {
    WheelBackRight.Set(.5);
  }
  else
  {
    WheelBackRight.Set(0);
  }

  if(Xbox.GetRawButton(3))
  {
    WheelFrontRight.Set(.5);
  }
  else
  {
    WheelFrontRight.Set(0);
  }

  if(Xbox.GetRawButton(4))
  {
    WheelFrontLeft.Set(.5);
  }
  else
  {
    WheelFrontLeft.Set(0);
  }

  if(Xbox.GetRawButton(5))
  {
    BallShootUp.Set(.5);
  }
  else
  {
    BallShootUp.Set(0);
  }

  if(Xbox.GetRawButton(6))
  {
    BallShootSide.Set(.5);
  }
  else
  {
    BallShootSide.Set(0);
  }

  if(Xbox.GetRawButton(7))
  {
    BallShootUpper.Set(.5);
  }
  else
  {
    BallShootUpper.Set(0);
  }

  if(Xbox.GetRawButton(8))
  {
    BallShootLower.Set(.5);
  }
  else
  {
    BallShootLower.Set(0);
  }

  if(Xbox.GetRawButton(9))
  {
    ColorWheelSpin.Set(.5);
  }
  else
  {
    ColorWheelSpin.Set(0);
  }

  if(Xbox.GetRawButton(10))
  {
    HangerUp.Set(.5);
  }
  else
  {
    HangerUp.Set(0);
  }

  if(Xbox.GetRawButton(1))
  {
    HangerSide.Set(.5);
  }
  else
  {
    HangerSide.Set(0);
  }

  if(Xbox.GetRawButton(2))
  {
    ElevatorTop.Set(.5);
  }
  else
  {
    ElevatorTop.Set(0);
  }

  if(Xbox.GetRawButton(3))
  {
    ElevatorBottom.Set(.5);
  }
  else
  {
    ElevatorBottom.Set(0);
  }
}

/*########################################################################################

          Shooter Test

########################################################################################*/

void Robot::ShooterTest()
{
  double xboxRX = Xbox.GetRawAxis(4);
  double xboxRY = Xbox.GetRawAxis(5);
  double xboxTrigR = Xbox.GetRawAxis(3);

  if((ShooterLimitXRight.Get() == 0))
  {
    if(xboxRX < 0)
    {
      xboxRX = 0;
    }

    BallShootSide.Set(xboxRX / 10);
  }
  else if((ShooterLimitXLeft.Get() == 0))
  {
    if(xboxRX > 0)
    {
      xboxRX = 0;
    }

    BallShootSide.Set(xboxRX / 10);
  }
  else
  {
    BallShootSide.Set(xboxRX / 10);
  }
  
  if((ShooterLimitY.Get() == 0) && (xboxRY > 0))
  {
    xboxRY = 0;
  }
  
  BallShootUp.Set(xboxRY / 10);

  BallShootUpper.Set(xboxTrigR);
  BallShootLower.Set(-xboxTrigR);
}
#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
