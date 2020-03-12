
#pragma once
#include <frc/WPILib.h>
#include <ctre/phoenix.h>
#include "MyEncoder.h"

class AutoAim
{
 public:
  AutoAim(MyEncoder *initShooterRaiseEncoder, // 1
   frc::DigitalInput *initShooterLimitXLeft, // 2
   frc::DigitalInput *initShooterLimitXRight, // 3
   frc::DigitalInput *initShooterLimitY, // 4
   WPI_TalonSRX *initBallShootUp, // 5 
   WPI_TalonSRX *initBallShootSide, // 6
   bool initBlocksSeen, // 7
   int initDesiredX1, // 8
   int initDesiredX2, // 9
   int initDesiredTopDistance1, // 10
   int initDesiredTopDistance2,
   int initCurrentX);
  void RunAutoAim();
  bool GetLockedOn();
 private:
  MyEncoder *ShooterRaiseEncoder;
  frc::DigitalInput *ShooterLimitXLeft;
  frc::DigitalInput *ShooterLimitXRight;
  frc::DigitalInput *ShooterLimitY;
  WPI_TalonSRX *BallShootUp;
  WPI_TalonSRX *BallShootSide;
  bool blocksSeen;
  int desiredX1;
  int desiredX2;
  int desiredEncoderDistance1;
  int desiredEncoderDistance2;
  int desiredTopDistance1;
  int desiredTopDistance2;
  int currentX;
  bool lockedOn;
  bool topRotationSwitch = false;
  int searchingTimes = 0;
};
