/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "AutoAim.h"
#include <frc/WPILib.h>
#include <ctre/phoenix.h>

AutoAim::AutoAim(MyEncoder *initShooterRaiseEncoder, frc::DigitalInput *initShooterLimitXLeft,
    frc::DigitalInput *initShooterLimitXRight, frc::DigitalInput *initShooterLimitY,
    WPI_TalonSRX *initBallShootUp, WPI_TalonSRX *initBallShootSide) 
{
    ShooterRaiseEncoder = initShooterRaiseEncoder;
    ShooterLimitXLeft = initShooterLimitXLeft;
    ShooterLimitXRight = initShooterLimitXRight;
    ShooterLimitY = initShooterLimitY;
    BallShootUp = initBallShootUp;
    BallShootSide = initBallShootSide;
}

bool xboxTargettingSwitch = false;
bool topRotationSwitch = false;

void AutoAim::RunAutoAim()
{
//   if(blockX > /*XValue*/ && blockX < /*XValue2*/ && blockY > /*YValue1*/ && blockY < /*YValue2*/)
//   {
//     lockedOn = true;
//     // BallShootSide->Set();
//   }
//   else
//   {
//     lockedOn = false;
//   }
  
//   if(!lockedOn)
//   {
//     if(blocksSeen)
//     {
//       xboxTargettingSwitch = false;

//       if(blockX > /*XValue1*/)
//       {
//         BallShootSide->Set(0.25);
//       }
//       else if(blockX < /*XValue2*/) 
//       {
//         BallShootSide->Set(-0.25);
//       }
//       else
//       {
//         BallShootSide->Set(0);
//       }

//       if(blockY > /*YValue1*/)
//       {
//         BallShootUp->Set(0.1);
//       }
//       else if(blockY < /*YValue2*/)
//       {
//         BallShootUp->Set(-0.1);
//       }
//       else
//       {
//         BallShootUp->Set(0);
//       }
//     }
//     else
//     {
//       if(xbox.GetRawButtonPressed(4))
//       {
//         xboxTargettingSwitch = true;
//       }

//       if(xboxTargettingSwitch = true)
//       {
//         if(shooterLimitXLeft->Get() = 1)
//         {
//           topRotationSwitch = true;
//         }

//         if(shooterLimitXRight->Get() = 1)
//         {
//           topRotationSwitch = false;
//         }

//         if(topRotationSwitch)
//         {
//           BallShootSide->Set(.25);
//         }
//         else
//         {
//           BallShootSide->Set(-.25);
//         }
//       }
//     }
//   }
}
