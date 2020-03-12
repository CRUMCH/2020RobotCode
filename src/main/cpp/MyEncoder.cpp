
#pragma once
#include "MyEncoder.h"
#include <frc/WPILib.h>

//revs/sec
//revs/sec
//position
MyEncoder::MyEncoder(frc::Encoder *initEncoder, double initPulsesPerRotation) 
{
    //Motor Shaft
    pulsesPerRotation = initPulsesPerRotation;
    encoder = initEncoder;
    encoder->SetDistancePerPulse(1.0 / 2048.0);
}

double MyEncoder::GetRevs() 
{
    return encoder->GetRate();
}

double MyEncoder::GetDistance() 
{
    return encoder->Get() / pulsesPerRotation;
}

double MyEncoder::PIDGet() 
{
    return GetRevs();
}