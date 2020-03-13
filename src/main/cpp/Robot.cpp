
#include "Robot.h"
#include "MyEncoder.h"
#include <iostream>
#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/phoenix.h>
#include <frc/WPILib.h>
#include "rev/ColorSensorV3.h"
#include "AutoAim.h"

WPI_VictorSPX WheelBackLeft {3};
WPI_VictorSPX WheelBackRight {4};
WPI_VictorSPX WheelFrontRight {2};
WPI_VictorSPX WheelFrontLeft {1};

frc::MecanumDrive Mecanums {WheelFrontLeft , WheelBackLeft , WheelFrontRight , WheelBackRight};

WPI_TalonSRX BallShootUp {1};
  bool yMotorSet = false;
WPI_TalonSRX BallShootSide {2};

frc::VictorSP BallShootUpper {5};
frc::VictorSP BallShootLower {6};

frc::VictorSP ElevatorTop {0};
frc::VictorSP ElevatorBottom {1};

frc::VictorSP HangerUp {4};
frc::VictorSP HangerSide {0};

frc::Relay BallIntake {2};

frc::Solenoid IntakeOpen {0};
frc::Solenoid IntakeClose {1};

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
char PixyArrayOutput [1];
int pixyCamX = 0;
int pixyCamY = 0;

int desiredEncoderDistance1 = 0;
int desiredEncoderDistance2 = 0;

bool psFirstOn = false;
bool psSecondOn = false;
bool psSwitched = false;
int ballCount = 0;

bool intakeButton = false;

bool blocksSeen = false;
bool aimSwitch = false;
bool stringComplete =  false;

// static constexpr auto i2cPort = frc::I2C::Port::kOnboard;
// rev::ColorSensorV3 ColorSensor {i2cPort};
// rev::ColorSensorV3::RawColor colorRead = ColorSensor.GetRawColor();

//Encoders
frc::Encoder frcShooterTopEncoder(10, 12, false, frc::CounterBase::EncodingType::k4X); //DIO ports
frc::Encoder frcShooterBottomEncoder(15, 16, false, frc::CounterBase::EncodingType::k4X); //DIO Ports
frc::Encoder frcShooterRaiseEncoder(17, 18, false, frc::CounterBase::EncodingType::k4X); //DIO ports

MyEncoder ShooterTopEncoder(&frcShooterTopEncoder, 2048);
MyEncoder ShooterBottomEncoder(&frcShooterBottomEncoder, 2048);
MyEncoder ShooterRaiseEncoder(&frcShooterRaiseEncoder, 1024);

frc::PIDController shooterTopPID(.8, 0, 0, &ShooterTopEncoder, &BallShootUpper); // Tune
frc::PIDController shooterBottomPID(.1, .1, .3, &ShooterBottomEncoder, &BallShootLower); // Tune

//AutoAim
AutoAim autoAim(&ShooterRaiseEncoder,
 &ShooterLimitXLeft,
 &ShooterLimitXRight,
 &ShooterLimitY,
 &BallShootUp,
 &BallShootSide,
 blocksSeen,
 20,
 -20,
 desiredEncoderDistance1,
 desiredEncoderDistance2);

void Robot::RobotInit() 
{
  m_chooser.SetDefaultOption(kAutoNameDefault, kAutoNameDefault);
  m_chooser.AddOption(kAutoNameCustom, kAutoNameCustom);
  frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  WheelFrontLeft.SetInverted(true);
  WheelBackLeft.SetInverted(true);
  WheelBackRight.SetInverted(true);

  IntakeOpen.SetPulseDuration(0.1);
  IntakeClose.SetPulseDuration(0.1);

  shooterTopPID.SetInputRange(-10.0, 10.0); // Tune Values
  shooterBottomPID.SetInputRange(-10.0, 10.0); // Tune Values

  shooterTopPID.SetOutputRange(-1.0,1.0);
  shooterBottomPID.SetOutputRange(-1.0,1.0);
}

void Robot::RobotPeriodic() 
{
  // Communication With Arduino WIP

  // int size = PixyCam.Read(PixyArray, 80);
  // PixyCamStr.clear();
  // for(int i = 0; i < size; i++) 
  // {
  //   PixyCamStr += PixyArray[i];
  //   if(PixyArray[i] == '\n')
  //   {
      // PixyCam.Write(PixyArrayOutput, 1);
      // PixyCam.Flush();
  //   }
  // }
//  std::cout << PixyArray;
}

void Robot::AutonomousInit() 
{
  m_autoSelected = m_chooser.GetSelected();
  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  std::cout << "Auto selected: " << m_autoSelected << std::endl;

  if (m_autoSelected == kAutoNameCustom) {
    // if(!yMotorSet && ShooterLimitY.Get() == 0)
    // {
    //   BallShootUp.Set(.1);
    // }
    // else
    // {
    //   frcShooterRaiseEncoder.Reset();
    //   yMotorSet = true;
    // }
  
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
  PixyArrayOutput[0] = '\n';
  PixyCam.Write(PixyArrayOutput, 1);
  PixyCam.Flush();
}

void Robot::TeleopPeriodic() 
{
  // autoAim.SetLockedOn(lockedOn);

  // if(Xbox.GetRawButtonPressed(4))
  // {
  //   aimSwitch = true;
  // }

  RunDriveTrain();
  // RunHanger();
  // RunElevator();
  // RunColorWheel();

  // if(aimSwitch)
  // {
  //   autoAim.RunAutoAim();
  // }

  RunLauncher();

  if(Xbox.GetRawButtonPressed(4))
  {
    autoAim.SetLockedOn(true);
  }

  if(Xbox.GetRawButton(1))
  {
    BallShootSide.Set(.25);
    BallShootUp.Set(.1);
    HangerUp.Set(.25);
    HangerSide.Set(.25);

  }
  else
  {
    BallShootSide.Set(0);
    BallShootUp.Set(0);
  }

  // if(Xbox.GetRawButtonPressed(4))
  // {
  //   autoAim.Run();
  // }

  // ControlByButtons();
  // ShooterTest();
  // RunIntakeArm();

  // if(Xbox.GetRawButton(1))
  // {
  // std::cout << psFirstVal << std::endl;
  // }
  
  // if(Xbox.GetRawButton(2))
  // {
  //   std::cout << ShooterLimitY.Get() << std::endl;
  // }

  // if(Xbox.GetRawButton(3))
  // {
  //   std::cout << ShooterLimitXRight.Get() << std::endl;
  // }

  // if(Xbox.GetRawButton(4))
  // {
  //   std::cout << ShooterLimitXLeft.Get() << std::endl;
  // }
}

void Robot::TestPeriodic() 
{

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
  
  Mecanums.DriveCartesian(xboxRX , xboxLX , xboxRX);
}

/*########################################################################################

          Launcher

########################################################################################*/

bool launcherStarted = false;
double shooterTopStart = 0;

void Robot::RunLauncher()
{
 if(autoAim.GetLockedOn())
 {   
    // std::cout << ShooterTopEncoder.GetRevs() << std::endl;
    // std::cout << ShooterBottomEncoder.GetRevs() << std::endl;
    // std::cout << ShooterTopEncoder.GetDistance() << std::endl;
    // std::cout << ShooterBottomEncoder.GetDistance() << std::endl;

    if(!launcherStarted)
    {
      shooterTopStart = ShooterTopEncoder.GetDistance();

      launcherStarted = true;

      shooterTopPID.SetSetpoint(.1);
      shooterBottomPID.SetSetpoint(-.1);

      shooterTopPID.Enable();
      shooterBottomPID.Enable();
    }
    else if(launcherStarted && ShooterTopEncoder.GetDistance() - shooterTopStart > 10) // Tune Value
    {
      if(launcherStarted)
      {
        shooterTopPID.Disable();
        shooterBottomPID.Disable();

        BallShootUpper.Set(0);
        BallShootLower.Set(0);
        
        if(ShooterLimitY.Get())
        {
          BallShootUp.Set(0);
        }
        else
        {
          BallShootUp.Set(-.25);
        }

        if(ShooterLimitXLeft.Get())
        {
          BallShootSide.Set(0);
        }
        else
        {
          BallShootSide.Set(-.25);
        }

        if(ShooterLimitY.Get() && ShooterLimitXLeft.Get())
        {
          BallShootSide.Set(0);
          BallShootUp.Set(0);

          launcherStarted = false;
          autoAim.SetLockedOn(false);
        }
      }
    } 
  }
}

/*########################################################################################

          Hanger

########################################################################################*/

void Robot::RunHanger()
{
//   double customYAxis = Xbox.GetRawAxis(5);
//   double customXAxis = Xbox.GetRawAxis(4);
  
//   if(customYAxis < .1 && customYAxis > -.1)
//   {
//     customYAxis = 0;
//   }

//   if(customXAxis < .1 && customXAxis > -.1)
//   {
//     customXAxis = 0;
//   }

//   if(customYAxis > 0)
//   {
//     HangerUp.Set(.5);
//   }
//   else if(customYAxis < 0)
//   {
//     HangerUp.Set(-.5);
//   }
//   else
//   {
//     HangerUp.Set(0);
//   }

//   if(customXAxis > 0)
//   {
//     HangerSide.Set(.5);
//   }
//   else if(customXAxis < 0)
//   {
//     HangerSide.Set(-.5);
//   }
//   else
//   {
//     HangerSide.Set(0);
//   }
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
      ElevatorBottom.Set(-.5);

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
  }
  
  if((ShooterLimitXLeft.Get() == 0))
  {
    if(xboxRX > 0)
    {
      xboxRX = 0;
    }
  }
  
  if((ShooterLimitY.Get() == 0) && (xboxRY < 0))
  {
    xboxRY = 0;
  }
  
  BallShootUp.Set(xboxRY);
  BallShootSide.Set(xboxRX);

  BallShootUpper.Set(xboxTrigR);
  BallShootLower.Set(-xboxTrigR);
}
#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
