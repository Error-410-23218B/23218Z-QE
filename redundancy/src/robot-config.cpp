#include "vex.h"

using namespace vex;
using signature = vision::signature;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;
competition Competition;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor leftMotorA = motor(PORT19, ratio18_1, true);
motor leftMotorB = motor(PORT20, ratio18_1, true);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT17, ratio18_1, false);
motor rightMotorB = motor(PORT18, ratio18_1, false);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 478.78, 435, 288, mm, 1);
motor IntakeMotorGroupMotorA = motor(PORT7, ratio18_1, false);
motor IntakeMotorGroupMotorB = motor(PORT9, ratio18_1, true);
motor_group IntakeMotorGroup = motor_group(IntakeMotorGroupMotorA, IntakeMotorGroupMotorB);
motor FlywheelMotorGroupMotorA = motor(PORT15, ratio6_1, false);
motor FlywheelMotorGroupMotorB = motor(PORT16, ratio6_1, true);
motor_group FlywheelMotorGroup = motor_group(FlywheelMotorGroupMotorA, FlywheelMotorGroupMotorB);
digital_out FlyPneum = digital_out(Brain.ThreeWirePort.A);
digital_out ExtensionPneum = digital_out(Brain.ThreeWirePort.B);
digital_out ExtensionPneum2 = digital_out(Brain.ThreeWirePort.C);
motor29 redLED = motor29(Brain.ThreeWirePort.C,false);
motor29 greenLED = motor29(Brain.ThreeWirePort.D,false);
motor29 blueLED  = motor29(Brain.ThreeWirePort.E,false);

// VEXcode generated functions
// define variable for remote controller enable/disable
// define variables used for controlling motors based on controller inputs
bool DrivetrainNeedsToBeStopped_Controller1 = true;
bool Controller1RightShoulderControlMotorsStopped = true;


// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3 + Axis1
      // right = Axis3 - Axis1
      int drivetrainLeftSideSpeed = Controller1.Axis3.position() + Controller1.Axis1.position();
      int drivetrainRightSideSpeed = Controller1.Axis3.position() - Controller1.Axis1.position();
      
      // check if the value is inside of the deadband range
      if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          // stop the left drive motor
          LeftDriveSmart.stop();
          // tell the code that the left motor has been stopped
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }
      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
        // check if the right motor has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller1) {
          // stop the right drive motor
          RightDriveSmart.stop();
          // tell the code that the right motor has been stopped
          DrivetrainRNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }

        if (Controller1.ButtonR2.pressing()) {
        IntakeMotorGroup.spin(forward);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (Controller1.ButtonR1.pressing()) {
        IntakeMotorGroup.spin(reverse);
        Controller1RightShoulderControlMotorsStopped = false;
      } else if (!Controller1RightShoulderControlMotorsStopped) {
        IntakeMotorGroup.stop();
        // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
        Controller1RightShoulderControlMotorsStopped = true;
      }
    }
    // wait  before repeating the process
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);
}