using namespace vex;

extern brain Brain;
extern competition Competition;

// VEXcode devices
extern controller Controller1;
extern drivetrain Drivetrain;
extern motor_group IntakeMotorGroup;
extern motor_group FlywheelMotorGroup;
extern digital_out FlyPneum;
extern digital_out ExtensionPneum;
extern motor29 redLED;
extern motor29 greenLED;
extern motor29 blueLED;
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );