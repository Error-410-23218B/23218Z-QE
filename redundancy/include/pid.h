#pragma once
#ifndef pid_h
#define pid_h

#include "vex.h"
// Declared Methods in global scope and allows them to be used in other .cpp files, related to PID code;
namespace eftl
{
    typedef unsigned char TYPE;

    class PIDController
    {
    public:
        double prevError;
        double integral;
        double derivative;
        double Power;
        double Setpoint;

        double kP;
        double kI;
        double kD;
        double kF;

        double pkP;
        double pkI;
        double pkD;
        double pkF;
        PIDController(double ikP, double ikI, double ikD, double ikF);

        double step(double setpoint, double process_variable);
        void tune();
        void tune_test();
        //  double slewRate(double slewSetpoint,TYPE type);
    };
}

extern eftl::PIDController flywheelController;

extern eftl::PIDController flywheelAutonController;

extern eftl::PIDController driveVelocityController;

extern eftl::PIDController drivePosController;

extern eftl::PIDController turnController;

extern eftl::PIDController flywheelt;

extern eftl::PIDController drivet;

extern eftl::PIDController drivePost;

extern eftl::PIDController turnt;

extern task f1;

#endif pid_h