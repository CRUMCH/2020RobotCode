
#pragma once
#include <frc/WPILib.h>

class MyEncoder : public frc::PIDSource
{
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
