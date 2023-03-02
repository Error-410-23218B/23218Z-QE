#include <iostream>
#include "vex.h"
#include "pid.h"
#include "graph.h"

// Structure used to declare variables, at bottom multiple instances of the
// structure are declared, use same variable in "different" ways.

eftl::PIDController flywheelController(2.35,0.0012,0.84,0.1876);
eftl::PIDController flywheelAutonController(2.35,0.0011,0.84,0.1876);
eftl::PIDController driveVelocityController(0.0, 0.0, 0.0, 0.0);
eftl::PIDController drivePosController(0.0, 0.0, 0.0, 0.0);
eftl::PIDController turnController(0.0, 0.0, 0.0, 0.0);

/*
eftl::PIDController flywheelt(200.0, 0.0, 0.0, 120.0);
 eftl::PIDController drivet(0.0, 0.0, 0.0, 0.0);
eftl::PIDController drivePost(0.0, 0.0, 0.0, 0.0);
 eftl::PIDController turnt  (200.0, 0.0, 0.0, 120.0);
*/

eftl::PIDController::PIDController(double ikP, double ikI, double ikD, double ikF)
{
  kP = ikP;
  kI = ikI;
  kD = ikD;
  kF = ikF;

  
}

double eftl::PIDController::step(double isetpoint, double process_variable)
{ 

  double error = isetpoint - process_variable;
  integral += error;
  if(integral>isetpoint){
    integral = 0;
    
  }
  derivative = error - prevError;
  prevError = error;
  Power = isetpoint * kF + error * kP + integral * kI + derivative * kD;
 

return Power;
  


}



