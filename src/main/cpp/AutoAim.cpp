
#include "AutoAim.h"
#include <frc/WPILib.h>
#include <ctre/phoenix.h>

AutoAim::AutoAim(MyEncoder *initShooterRaiseEncoder,
  frc::DigitalInput *initShooterLimitXLeft,
  frc::DigitalInput *initShooterLimitXRight,
  frc::DigitalInput *initShooterLimitY,
  WPI_TalonSRX *initBallShootUp,
  WPI_TalonSRX *initBallShootSide,
  bool initBlocksSeen,
  int initDesiredX1,
  int initDesiredX2,
  int initDesiredEncoderDistance1,
  int initDesiredEncoderDistance2) 
{
  ShooterRaiseEncoder = initShooterRaiseEncoder;
  ShooterLimitXLeft = initShooterLimitXLeft;
  ShooterLimitXRight = initShooterLimitXRight;
  ShooterLimitY = initShooterLimitY;
  BallShootUp = initBallShootUp;
  BallShootSide = initBallShootSide;
  blocksSeen = initBlocksSeen;
  desiredX1 = initDesiredX1;
  desiredX2 = initDesiredX2;
  desiredEncoderDistance1 = initDesiredEncoderDistance1;
  desiredEncoderDistance2 = initDesiredEncoderDistance2;
}


bool AutoAim::GetLockedOn()
{
  return lockedOn;
}

void AutoAim::SetLockedOn(bool newLockedOn)
{
  lockedOn = newLockedOn;
}

void AutoAim::SetCurrentX(int newCurrentX)
{
  currentX = newCurrentX;
}

void AutoAim::RunAutoAim()
{
  if(blocksSeen)
  {
    if(currentX > desiredX1 &&
        currentX < desiredX2 &&
        ShooterRaiseEncoder->GetDistance() > desiredEncoderDistance1 &&
        ShooterRaiseEncoder->GetDistance() < desiredEncoderDistance2)
    {
      lockedOn = true;

      BallShootSide->Set(0);
      BallShootUp->Set(0);
    }
    else
    {
      lockedOn = false;
    }
    
    if(!lockedOn)
    {
      if(currentX > desiredX1 && ShooterLimitXLeft->Get() == 1)
      {
        BallShootSide->Set(0.25);
      }
      else if(currentX < desiredX2 && ShooterLimitXRight->Get() == 1) 
      {
        BallShootSide->Set(-0.25);
      }
      else
      {
        BallShootSide->Set(0);
      }

      if(ShooterRaiseEncoder->GetDistance() > desiredEncoderDistance1 && ShooterLimitY->Get() == 1)
      {
        BallShootUp->Set(0.1);
      }
      else if(ShooterRaiseEncoder->GetDistance() < desiredEncoderDistance2 && ShooterRaiseEncoder->GetDistance() < 60)
      {
        BallShootUp->Set(-0.1);
      }
      else
      {
        BallShootUp->Set(0);
      }
    }
  }
  else
  {
    if(searchingTimes != 2)
    {
      if(ShooterLimitXLeft->Get() == 1 && !topRotationSwitch)
      {
        topRotationSwitch = true;
        searchingTimes = searchingTimes + 1;
      }

      if(ShooterLimitXRight->Get() == 1 && topRotationSwitch)
      {
        topRotationSwitch = false;
      }

      if(topRotationSwitch)
      {
        BallShootSide->Set(.25);
      }
      else
      {
        BallShootSide->Set(-.25);
      }
    }
    else
    {
      BallShootSide->Set(0);
      BallShootUp->Set(0);

      searchingTimes = 0;
    }
  }
}
