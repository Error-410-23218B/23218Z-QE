/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Rohan                                            */
/*    Created:      Fri Jan 13 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    19, 20, 17, 18  
// IntakeMotorGroup     motor_group   7, 9            
// FlywheelMotorGroup   motor_group   15, 16          
// FlyPneum             digital_out   A               
// ExtensionPneum       digital_out   B               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
  #include "pid.h"
  #include "autonomous.h"
#include "graph.h"
#include "robot-config.h"
#include <iostream>
#include <stdio.h>

using namespace vex;
double flyt;
bool intakebutton = false;
bool rintakebutton = false;
 
int flywheelStep(){
  while(true){
   flyt = flywheelController.step(10200,FlywheelMotorGroup.voltage(voltageUnits::mV));
  FlywheelMotorGroup.spin(forward,flyt,voltageUnits::mV);



             }
             return 0;
             
  
};

void flyPneum(){
FlyPneum.set(true);
wait(150,msec);
FlyPneum.set(false);

}

void extend(){
  ExtensionPneum2.set(true);
  wait(1000,msec);
  ExtensionPneum.set(true);
  wait(100,msec);
  ExtensionPneum.set(false);
  ExtensionPneum2.set(false);

}

void exte(){
  ExtensionPneum.set(true);
  ExtensionPneum2.set(true);
}

void extef(){
  ExtensionPneum.set(false);
  ExtensionPneum2.set(false);

  
}

void Intake(){
  IntakeMotorGroup.spin(forward);
}

void Reverseintake(){
  IntakeMotorGroup.spin(reverse);

}
void  flywheel(){
  task f1(flywheelStep);
  FlywheelMotorGroup.setVelocity(100,percent);
  FlywheelMotorGroup.setMaxTorque(100,percent);
  FlywheelMotorGroup.spin(forward);
  
  if(Controller1.ButtonL2.pressing()){f1.stop();FlywheelMotorGroup.stop(); }
  

}



void drivercontrol(){
  Controller1.ButtonX.pressed(flyPneum);
  Controller1.ButtonUp.pressed(exte);
  Controller1.ButtonL1.pressed(flywheel);
  Controller1.ButtonDown.pressed(extef);
  //Controller1.ButtonUp.pressed(extend);


}


void pre_auton(){

}

void driveTest(){
  Drivetrain.driveFor(forward,300*6,mm);
}

void turnTest(){
  Drivetrain.turnFor(right,90,degrees);
}




int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!

  vexcodeInit();
  task g1(GUI);
  Drivetrain.setDriveVelocity(100,percent);
  FlywheelMotorGroup.setMaxTorque(100,percent);
  Drivetrain.setTurnVelocity(100,percent);
  IntakeMotorGroup.setMaxTorque(200,percent);
  IntakeMotorGroup.setVelocity(200,percent);  
 Competition.drivercontrol(drivercontrol);
 Controller1.ButtonRight.pressed(skillautonalt);

}


 