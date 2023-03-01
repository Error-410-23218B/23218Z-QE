
#include "autonomous.h"
#include "math.h"
#include "pid.h"
#include "vex.h"

// Tile variable is the amount of inches in one tile
const double Tile = 12.0;
// Roller positions
double roller_y;
double roller_x;
// Variables used for autonomous selection
bool redLon;
bool redSon;
bool blueLon;
bool blueSon;
const double Pt = 1.8;
const double Dt = 2.8;
const double inches = 25.4;
// autonomous function,when run it runs the selected autonomous that was
// selected when GUI(); is ran

// These 4 methods are called from GUI.cpp used for setting variables to select
// autonomous.
void redLSelect() { redLon = true; }
void redSSelect() { redSon = true; }
void blueLSelect() { blueLon = true; }
void blueSSelect() { blueSon = true; }

void flyp()
{
  FlyPneum.set(true);
  wait(150, msec);
  FlyPneum.set(false);
}

void extp()
{
  ExtensionPneum2.set(true);
  wait(1000,msec);
  ExtensionPneum.set(true);
  wait(200, msec);
  ExtensionPneum.set(false);
  ExtensionPneum2.set(false);
}

int flywheelST()
{
  double flyat = flywheelAutonController.step(11500, FlywheelMotorGroup.voltage(voltageUnits::mV));
  FlywheelMotorGroup.spin(forward, flyat, voltageUnits::mV);
  return 0;
}

// intake method, simply runs intake during autonomous
int reverseIntake()
{


  IntakeMotorGroup.setVelocity(100, percent);
  IntakeMotorGroup.spin(reverse);
  return 0;
}

int intake()
{
  IntakeMotorGroup.setVelocity(100, percent);
  IntakeMotorGroup.spin(forward);
  return 0;
}
/*
void turnMethod(double turnDegrees, turnType test)
{
  int currentAngle = 0;
  Drivetrain.turnFor(90);
}
*/
/*
void driveMethod(double driveAmount, double driveVelocity)
{
  double currentSpeed = Drivetrain.velocity(percentUnits::pct);
  double mvOut = driveVelocityController.step(95.0, currentSpeed);
  CDrivetrain.velocity(12000);
}
*/

// Flywheel method, flyPID from final_pid.cpp is run, flyPID is called here, and
// returns the value for RPM;
void Flywheel()
{
  for (int i = 0; i < 334; i++)
  {
    double currentSpeed = FlywheelMotorGroup.velocity(percentUnits::pct);
    double mvOut = flywheelController.step(95.0, currentSpeed);
    FlywheelMotorGroup.spin(directionType::fwd, mvOut, voltageUnits::mV);
  }
}

// Roller Method, takes
void redRoller()
{
  /*
  RollerMotor.setVelocity(10, percent);

  roller_y =
      (Vision10.largestObject.originY - Vision10.largestObject.centerY) * 2;
  roller_x = Vision10.largestObject.originY - Vision10.largestObject.originX;
  roller_x = double(roller_x);
  IntakeMotor.spin(forward, roller_x, volt);
  RollerMotor.spinFor(forward, 1, sec);
  roller_x = 0;
  roller_y = 0;
  */

  IntakeMotorGroup.spinFor(forward, 0.7, rev);
}

void blueRoller() { IntakeMotorGroup.spinFor(reverse, 0.5, rev); }
/*
// Autonomous Code, runs drive commands and is selected by autonomous();
void blueLong()
{
  // Creates a new task, so that the intake can run at the same time as the main
  // task which runs rest of the methods.
  task t1(intake);

  Drivetrain.driveFor(2 * Tile,forward);
  // Drivetrain.turnFor(left,135,degrees);
  Drivetrain.turnFor(left,135);
  Drivetrain.driveFor(2 * Tile,forward);
  // Drivetrain.turnFor(left,45,degrees);
  Drivetrain.turnFor(left,45);
  Drivetrain.driveFor(50.8,forward);
  Drivetrain.driveFor(25.4,reverse);
  Roller();
  Flywheel();
  // stops task
  t1.stop();
}
// Blue Short side of field,with drive commands being changed
void blueShort()
{
  task t1(intake);
  Drivetrain.driveFor(2 * Tile, forward);
  // Drivetrain.turnFor(right,135,degrees);
  Drivetrain.turnFor(right,135);
  Drivetrain.driveFor(2 * Tile, forward);
  // Drivetrain.turnFor(right,45,degrees);
  Drivetrain.turnFor(right,45);
  Drivetrain.driveFor(50.8,forward);
  Drivetrain.driveFor(25.4,reverse);
  Roller();
  Flywheel();
  t1.stop();
}
// Red Long side of field,with drive commands being changed
void redLong()
{
  task t1(intake);
  Drivetrain.driveFor(2*Tile,forward);
  Drivetrain.turnFor(left,135);
  Drivetrain.driveFor(2*Tile,forward);
  Drivetrain.turnFor(left,45);
  Drivetrain.driveFor(2,forward);
  Drivetrain.driveFor(1,reverse);
  Roller();
  Flywheel();
  t1.stop();
}
// Red Short side of field,with drive commands being changed
void redShort()
{
  task t1(intake);
  Drivetrain.driveFor(2 * Tile, forward);
  // Drivetrain.turnFor(right,135,degrees);
  Drivetrain.turnFor(right,135);
  Drivetrain.driveFor(2 *  Tile,forward);
  // Drivetrain.turnFor(right,45,degrees);
  Drivetrain.turnFor(right,45);
  Drivetrain.driveFor(2,forward);
  Drivetrain.driveFor(1,reverse);
  Roller();
  Flywheel();
  t1.stop();
}
*/

void blueL()
{
  Drivetrain.setDriveVelocity(75, percent);
  Drivetrain.setTimeout(5, sec);
  blueRoller();
  Drivetrain.turnFor(left, 10, degrees);
  task f1(flywheelST);
  for (int i = 0; i < 2; i++)
  {
    flyp();
    wait(1000, msec);
  }

  f1.stop();
}

void blueS()
{
  Drivetrain.setDriveVelocity(75, percent);
  Drivetrain.setTimeout(20, sec);
  Drivetrain.driveFor(forward, 1 * Tile * Dt, vex::inches);
  Drivetrain.turnFor(right, 90, degrees);

  Drivetrain.driveFor(forward, 0.4 * Tile * Dt, vex::inches);
  Drivetrain.turnFor(left, 90, degrees);
  Drivetrain.driveFor(forward, 1 * Tile * Dt, vex::inches);
  blueRoller();
  Drivetrain.turnFor(right, 10, degrees);
  task f1(flywheelST);
  for (int i = 0; i < 3; i++)
  {
    flyp();
  }
  f1.stop();
}

void redL()
{
  Drivetrain.setDriveVelocity(75, percent);
  Drivetrain.setTimeout(20, sec);
  redRoller();
  Drivetrain.turnFor(left, 10, degrees);
  task f1(flywheelST);
  for (int i = 0; i < 2; i++)
  {
    flyp();
    wait(1000, msec);
  }
  f1.stop();
}

void redS()
{
  Drivetrain.setDriveVelocity(75, percent);
  Drivetrain.setTimeout(20, sec);
  Drivetrain.driveFor(forward, 1 * Tile * Dt, vex::inches);
  Drivetrain.turnFor(right, 90, degrees);

  Drivetrain.driveFor(forward, 0.4 * Tile * Dt, vex::inches);
  Drivetrain.turnFor(left, 90, degrees);
  Drivetrain.driveFor(forward, 1 * Tile * Dt, vex::inches);
  redRoller();
  Drivetrain.turnFor(right, 10, degrees);
  task f1(flywheelST);
  for (int i = 0; i < 3; i++)
  {
    flyp();
  }
  f1.stop();
}


void skillAuton()
{
  task f1(flywheelST);
  Drivetrain.setDriveVelocity(75, percent);
  Drivetrain.setTimeout(20, sec);
  Drivetrain.driveFor(forward, 30 * Dt, mm);
  redRoller();
  IntakeMotorGroup.spin(forward);
  Drivetrain.driveFor(reverse, 1.2 * Tile * Dt, distanceUnits::in);
  Drivetrain.turnFor(right, 90, degrees);
  Drivetrain.driveFor(forward, 1.2 * Tile * Dt, distanceUnits::in);
  IntakeMotorGroup.stop();
  redRoller();
  Drivetrain.driveFor(reverse, 0.2 * Tile * Dt, distanceUnits::in);
  Drivetrain.turnFor(right, 135, degrees);
  IntakeMotorGroup.spin(forward);
  Drivetrain.driveFor(forward, 5.5 * Tile * Dt, distanceUnits::in);
  Drivetrain.turnFor(left, 45, degrees);
  Drivetrain.driveFor(forward, 1.2 * Tile * Dt, distanceUnits::in);
  redRoller();
  Drivetrain.driveFor(reverse, 1.2 * Tile * Dt, distanceUnits::in);
  Drivetrain.turnFor(right, 90, degrees);
  Drivetrain.driveFor(forward, 1.2 * Tile * Dt, distanceUnits::in);
  redRoller();
  Drivetrain.driveFor(reverse, 1 * Tile * Dt, distanceUnits::in);
  Drivetrain.turnFor(left, 45, degrees);
  Drivetrain.driveFor(forward, 1 * Tile * Dt, distanceUnits::in);
  extp();

}

void skillautonalt(){
  task f1(flywheelST);
   Drivetrain.setDriveVelocity(75, percent);
  Drivetrain.setTimeout(20, sec);
  Drivetrain.driveFor(forward, 30 * Dt, mm);
  redRoller();
  Drivetrain.driveFor(reverse, 1 * Tile * Dt, distanceUnits::in);
  IntakeMotorGroup.spin(forward);
  Drivetrain.turnFor(right, 90, degrees);
  Drivetrain.driveFor(forward, 1.2 * Tile * Dt, distanceUnits::in);
  IntakeMotorGroup.stop();
  redRoller();
  Drivetrain.turnFor(right,135,degrees);
  IntakeMotorGroup.spin(forward);
  Drivetrain.driveFor(forward,5 * Tile * Dt,distanceUnits::in);
  Drivetrain.turnFor(left,90,degrees);
  Drivetrain.driveFor(forward,6*Dt,distanceUnits::in);
  for(int i = 0; i<3;i++){
    flyp();
    wait(1000,msec);
  }
  
  Drivetrain.turnFor(right,45,degrees);
  Drivetrain.driveFor(forward,2.3*Tile*Dt,distanceUnits::in);
  Drivetrain.turnFor(left,90,degrees);
  for(int i = 0; i < 3;i++){
    flyp();
    wait(1000,msec);
  }
  f1.stop();
  FlywheelMotorGroup.stop();
  Drivetrain.driveFor(reverse, 3*Tile*Dt,distanceUnits::in);
  Drivetrain.turnFor(right,90,degrees);
  Drivetrain.driveFor(forward,30*Dt,mm);
  redRoller(); 
  Drivetrain.driveFor(reverse, 1 * Tile * Dt, distanceUnits::in);
  IntakeMotorGroup.spin(forward);
  Drivetrain.turnFor(right, 90, degrees);
  Drivetrain.driveFor(forward, 1.3 * Tile * Dt, distanceUnits::in);
  IntakeMotorGroup.stop();
  redRoller();
  Drivetrain.driveFor(reverse,1*Tile*Dt,distanceUnits::in);
  IntakeMotorGroup.spin(forward);
  Drivetrain.turnFor(right,45,degrees);
  Drivetrain.driveFor(forward,2*Tile*Dt,distanceUnits::in);
  extp();


}
void autonomous(){


  if(redLon)redL();
  if(redSon)redS();
  if(blueSon)blueS();
  if(blueLon)blueL();
  

}