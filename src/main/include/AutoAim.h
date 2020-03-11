/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <frc/WPILib.h>
#include <ctre/phoenix.h>
#include "MyEncoder.h"

class AutoAim {
 public:
  AutoAim(MyEncoder *initShooterRaiseEncoder, frc::DigitalInput *initShooterLimitXLeft,
   frc::DigitalInput *initShooterLimitXRight, frc::DigitalInput *initShooterLimitY,
   WPI_TalonSRX *initBallShootUp, WPI_TalonSRX *initBallShootSide);
  void RunAutoAim();
 private:
  MyEncoder *ShooterRaiseEncoder;
  frc::DigitalInput *ShooterLimitXLeft;
  frc::DigitalInput *ShooterLimitXRight;
  frc::DigitalInput *ShooterLimitY;
  WPI_TalonSRX *BallShootUp;
  WPI_TalonSRX *BallShootSide;
};
