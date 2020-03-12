
#pragma once
#include "AutoAim.h"
#include <frc/WPILib.h>
#include <ctre/phoenix.h>

AutoAim::AutoAim(MyEncoder *initShooterRaiseEncoder,
  frc::DigitalInput *initShooterLimitXLeft,
  frc::DigitalInput *initShooterLimitXRight,
  frc::DigitalInput *initShooterLimitY,
  WPI_TalonSRX *initBallShootUp,
  WPI_TalonSRX *initBallShootSide,
  bool initLockedOn,
  bool initBlocksSeen) 
{
  ShooterRaiseEncoder = initShooterRaiseEncoder;
  ShooterLimitXLeft = initShooterLimitXLeft;
  ShooterLimitXRight = initShooterLimitXRight;
  ShooterLimitY = initShooterLimitY;
  BallShootUp = initBallShootUp;
  BallShootSide = initBallShootSide;
  lockedOn = initLockedOn;
  blocksSeen = initBlocksSeen;
}

void AutoAim::RunAutoAim()
{
  bool topRotationSwitch = false;
  int searchingTimes = 0;

  double yEncoderRevs = ShooterRaiseEncoder->GetDistance();
  
  if(blocksSeen)
  {
    if(/*blockX > /*XValue && blockX < /*XValue2 && blockY > /*YValue1 && blockY < /*YValue2*/ true)
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
      if(/*blockX > /*XValue1 &&*/ ShooterLimitXLeft->Get() == 1)
      {
        BallShootSide->Set(0.25);
      }
      else if(/*blockX < /*XValue2 &&*/ ShooterLimitXRight->Get() == 1) 
      {
        BallShootSide->Set(-0.25);
      }
      else
      {
        BallShootSide->Set(0);
      }

      if(/*blockY > /*YValue1 &&*/ ShooterLimitY->Get() == 1)
      {
        BallShootUp->Set(0.1);
      }
      else if(/*blockY < /*YValue2 && */ true)
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
      if(/*ShooterLimitXLeft->Get() == 1 && topRotationSwitch = false*/ true)
      {
        topRotationSwitch = true;
        searchingTimes = searchingTimes + 1;
      }

      if(/*ShooterLimitXRight->Get() == 1 && topRotationSwitch = true*/ true)
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
