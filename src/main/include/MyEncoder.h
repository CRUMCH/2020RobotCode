/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
#include <frc/WPILib.h>

class MyEncoder : public frc::PIDSource {
 private:
  frc::Encoder *encoder;
  double pulsesPerRotation;
 public:
  MyEncoder(frc::Encoder *initEncoder, double initPulsesPerRotation);
  double GetRevs();
  double GetDistance();
  double PIDGet();
 protected:
  //frc::PIDSourceType m_pidSource = PIDSourceType::kDisplacement;
};
