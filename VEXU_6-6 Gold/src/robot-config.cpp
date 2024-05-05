#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor R1 = motor(PORT20, ratio6_1, false);
motor R2 = motor(PORT19, ratio6_1, false);
motor R3 = motor(PORT18, ratio6_1, true);
motor L1 = motor(PORT11, ratio6_1, true);
motor L2 = motor(PORT12, ratio6_1, true);
motor L3 = motor(PORT13, ratio6_1, false);
inertial inertialSensor = inertial(PORT16);
digital_out leftWing = digital_out(Brain.ThreeWirePort.A);
digital_out rightWing = digital_out(Brain.ThreeWirePort.C);
motor flyTop = motor(PORT1, ratio6_1, true);
motor flyBottom = motor(PORT15, ratio6_1, true);
motor intake = motor(PORT10, ratio6_1, true);
digital_out climber = digital_out(Brain.ThreeWirePort.B);

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