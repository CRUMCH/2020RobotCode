/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "MyEncoder.h"
#include <frc/WPILib.h>

//revs/sec
//revs/sec
//position
MyEncoder::MyEncoder(frc::Encoder *initEncoder, double initPulsesPerRotation) {
    //Motor Shaft
    pulsesPerRotation = initPulsesPerRotation;
    encoder = initEncoder;
    encoder->SetDistancePerPulse(1.0 / 2048.0);
}

double MyEncoder::GetRevs() {
    return encoder->GetRate();
}

double MyEncoder::GetDistance() {
    return encoder->Get() / pulsesPerRotation;
}

double MyEncoder::PIDGet() {
    return GetRevs();
}