
#pragma once
#include <frc/WPILib.h>
#include <ctre/phoenix.h>
#include "MyEncoder.h"
#include <iostream>

class AutoAim
{
 public:
  AutoAim(MyEncoder *initShooterRaiseEncoder, frc::DigitalInput *initShooterLimitXLeft,
   frc::DigitalInput *initShooterLimitXRight, frc::DigitalInput *initShooterLimitY,
   WPI_TalonSRX *initBallShootUp, WPI_TalonSRX *initBallShootSide, bool initLockedOn, bool initBlocksSeen);
  void RunAutoAim();
 private:
  MyEncoder *ShooterRaiseEncoder;
  frc::DigitalInput *ShooterLimitXLeft;
  frc::DigitalInput *ShooterLimitXRight;
  frc::DigitalInput *ShooterLimitY;
  WPI_TalonSRX *BallShootUp;
  WPI_TalonSRX *BallShootSide;
  bool lockedOn;
  bool blocksSeen;
};
