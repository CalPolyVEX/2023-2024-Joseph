#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor intakeL = motor(PORT10, ratio6_1, true);
motor intakeR = motor(PORT14, ratio6_1, false);
motor L1 = motor(PORT6, ratio6_1, true);
motor L2 = motor(PORT7, ratio6_1, true);
motor L3 = motor(PORT8, ratio6_1, true);
motor L4 = motor(PORT5, ratio6_1, false);
motor R1 = motor(PORT16, ratio6_1, false);
motor R2 = motor(PORT17, ratio6_1, false);
motor R3 = motor(PORT18, ratio6_1, false);
motor R4 = motor(PORT15, ratio6_1, true);

// vex::motor_group leftDriveMotors = motor_group(L1,L2,L3);
// vex::motor_group rightDriveMotors = motor_group(R1,R2,R3);
// vex::motor_group allDriveMotors = motor_group(L1, R1, L2, R2, L3, R3);

inertial inertialSensor = inertial(PORT19);
digital_out climber = digital_out(Brain.ThreeWirePort.A);
digital_out leftWing = digital_out(Brain.ThreeWirePort.B);
digital_out rightWing = digital_out(Brain.ThreeWirePort.C);
digital_out pneuIntake = digital_out(Brain.ThreeWirePort.D);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}