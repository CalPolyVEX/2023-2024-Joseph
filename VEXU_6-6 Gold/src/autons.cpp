#include "vex.h"

motor_group adm = motor_group(L1, R1, L2, R2, L3, R3);

void drive_for_time(int timeMs, directionType direction, int maxVoltage) 
{
  adm.spin(direction, maxVoltage, volt);
  wait(timeMs, msec);
  adm.stop();
}

void drive_for_time(int timeMs, directionType direction) 
{
  drive_for_time(timeMs, direction, 12);
}

void drive_for_time(int timeMs) 
{
  drive_for_time(timeMs, fwd, 12);
}

void default_constants(){
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .3, .03, 3, 15);
  chassis.set_swing_constants(12, .4, .01, 4, 15);
  chassis.set_drive_exit_conditions(1.5, 300, 1500);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);

  inertialSensor.calibrate();
  wait(2, seconds);
  Controller1.rumble("--");
}

void odom_constants(){
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
}

void worlds_Auton()
{
  // Worlds Auton

  //chassis.set_coordinates(5, 5, -45);
  
  //NOTE: Onlly use heading once in the code, otherwise it will break the code if you use it more then once
  //chassis.set_heading(-45);

  chassis.set_coordinates(0, 0 , -45);

  chassis.drive_to_point(0,0);
  
  //fling preload triball into alley
  leftWing.set(true);
  wait(0.1, seconds);
  leftWing.set(false);

  //pick up triball in match load zone
  intake.setVelocity(100, percent);
  intake.spin(forward);
  flyTop.setVelocity(-70, rpm);
  flyTop.spin(forward);
  flyBottom.setVelocity(-70, rpm);
  flyBottom.spin(forward);
  chassis.drive_distance(5);
  wait(0.4, seconds);
  chassis.drive_distance(-5);

  //score match load alliance triball into goal
  chassis.turn_to_angle(45);
  flyBottom.setVelocity(-110, rpm);
  flyTop.setVelocity(-110, rpm);
  intake.setVelocity(25, percent);
  intake.spin(reverse);
  //wait(0.5, seconds); removed to save time
  chassis.drive_distance(9);
  chassis.drive_distance(-7);
  chassis.left_swing_to_angle(75);
  chassis.turn_to_angle(180);
  //chassis.drive_distance(-2); removed to save time
  chassis.right_swing_to_angle(-90);
  //drive_for_time(700, reverse, 7);
  chassis.set_drive_exit_conditions(1.5, 300, 1000);
  chassis.drive_distance(-10);
  chassis.drive_distance(5);

  //go to match load zone to match load 10 down the alley
  chassis.right_swing_to_angle(-135);
  chassis.drive_distance(9.5);
  flyBottom.setVelocity(500, rpm);
  flyTop.setVelocity(350, rpm);
  intake.setVelocity(100, percent);
  intake.spin(forward);
  chassis.turn_to_angle(-45);
  leftWing.set(true);
  rightWing.set(true);
  chassis.drive_distance(6);

  //go back and forth 9 times to put 10 down the alley

  int matchLoad = 0;

  while(matchLoad < 8)
  {
    chassis.drive_distance(-7);
    chassis.drive_distance(8);
    matchLoad = matchLoad + 1;
  }

  flyTop.setVelocity(-70, rpm);
  flyBottom.setVelocity(-70, rpm);


  //plow them all down the alley
  leftWing.set(false);
  chassis.drive_distance(-5);
  chassis.turn_to_angle(45);
  chassis.drive_distance(-13);
  chassis.left_swing_to_angle(5);
  chassis.set_drive_constants(8, 1.5, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.drive_distance(-58);
  chassis.set_drive_exit_conditions(1.5, 300, 2000);
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);

  //push them along the match load bar
  chassis.set_swing_exit_conditions(1, 300, 1200);
  chassis.drive_distance(2);
  chassis.left_swing_to_angle(-8);
  chassis.drive_distance(-10);
  chassis.left_swing_to_angle(-43);
  chassis.drive_distance(-15);
  chassis.left_swing_to_angle(-90);

  //score them in the goal and score them twice
  intake.spin(reverse);
  chassis.drive_distance(3);
  drive_for_time(500, reverse);
  chassis.drive_distance(10);
  drive_for_time(500, reverse);

  //touch the bar
  chassis.drive_distance(5);
  rightWing.set(false);
  chassis.left_swing_to_angle(-45);
  chassis.drive_distance(20);
  chassis.left_swing_to_angle(0);
  chassis.drive_distance(26);














}

void old_AWP(){
  // Just AWP, called "Old AWP" on brain
  intake.setVelocity(100, percent);
  intake.spin(forward);
  flyTop.setVelocity(-70, rpm);
  wait(0.3, seconds);
  flyTop.spin(forward);
  flyBottom.setVelocity(-70, rpm);
  flyBottom.spin(forward);
  chassis.drive_distance(12);
  wait(0.7, seconds);
  chassis.drive_distance(-5);
  chassis.turn_to_angle(90);
  intake.setVelocity(-110, rpm);
  flyTop.setVelocity(-110, rpm);
  intake.setVelocity(100, percent);
  intake.spin(reverse);
  wait(1.5, seconds);
  chassis.drive_distance(5);
  chassis.drive_distance(-5);
  chassis.left_swing_to_angle(120);
  chassis.turn_to_angle(225);
  chassis.drive_distance(-2);
  chassis.right_swing_to_angle(-45);
  drive_for_time(750, reverse);
  chassis.drive_distance(5);
  //ram the goal a second time (removed to get out of the way of the green bot)
  //drive_for_time(750, reverse);
  //chassis.drive_distance(5);
  chassis.right_swing_to_angle(-170);
  chassis.drive_distance(30);
  chassis.turn_to_angle(-88);
  chassis.drive_distance(10);
  wait(20, seconds);
  chassis.drive_distance(5);
  
}

void testing() {
  //For testing drive, turn or swings
  chassis.right_swing_to_angle(90);
  chassis.left_swing_to_angle(-90);
  chassis.right_swing_to_angle(0);
}

void safe_worlds_auton(){
  //Safe worlds auton to save time, I just took off a few of the match loads

  // Worlds Auton

  //chassis.set_coordinates(5, 5, -45);
  
  //NOTE: Only use heading once in the code, otherwise it will break the code if you use it more then once
  //chassis.set_heading(-45);

  //chassis.set_coordinates(0, 0 , -45);
  
  
  
  
  
  //****Need to add 45 degrees to all turns and swings*****

  //chassis.drive_to_point(0,0);
  
  //fling preload triball into alley
  leftWing.set(true);
  wait(0.1, seconds);
  leftWing.set(false);

  //pick up triball in match load zone
  intake.setVelocity(100, percent);
  intake.spin(forward);
  flyTop.setVelocity(-70, rpm);
  flyTop.spin(forward);
  flyBottom.setVelocity(-70, rpm);
  flyBottom.spin(forward);
  chassis.drive_distance(5);
  wait(0.4, seconds);
  chassis.drive_distance(-5);

  //score match load alliance triball into goal
  chassis.turn_to_angle(90);
  flyBottom.setVelocity(-110, rpm);
  flyTop.setVelocity(-110, rpm);
  intake.setVelocity(40, percent);
  intake.spin(reverse);
  //wait(0.5, seconds); removed to save time
  chassis.drive_distance(5);
  chassis.drive_distance(-3);
  chassis.left_swing_to_angle(120);
  chassis.turn_to_angle(225);
  //chassis.drive_distance(-2); removed to save time
  chassis.right_swing_to_angle(-45);
  drive_for_time(750, reverse, 6);
  chassis.drive_distance(5);

  //go to match load zone to match load 10 down the alley
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(9.5);
  flyBottom.setVelocity(500, rpm);
  flyTop.setVelocity(350, rpm);
  intake.setVelocity(100, percent);
  intake.spin(forward);
  chassis.turn_to_angle(-0);
  leftWing.set(true);
  rightWing.set(true);
  chassis.drive_distance(6);

  //go back and forth 10 times to put 8 down the alley

  int matchLoad = 0;

  while(matchLoad < 7)
  {
    chassis.drive_distance(-7);
    chassis.drive_distance(8);
    matchLoad = matchLoad + 1;
  }

  flyTop.setVelocity(-70, rpm);
  flyBottom.setVelocity(-70, rpm);


  //plow them all down the alley
  leftWing.set(false);
  chassis.drive_distance(-5);
  chassis.turn_to_angle(90);
  chassis.drive_distance(-13);
  chassis.left_swing_to_angle(50);
  chassis.set_drive_constants(7, 1.5, 0, 10, 0);
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.drive_distance(-60);
  chassis.set_drive_exit_conditions(1.5, 300, 2000);
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);

  //push them along the match load bar
  chassis.set_swing_exit_conditions(1, 300, 1200);
  chassis.drive_distance(2);
  chassis.left_swing_to_angle(35);
  chassis.drive_distance(-10);
  chassis.left_swing_to_angle(2);
  chassis.drive_distance(-15);
  chassis.left_swing_to_angle(-45);

  //score them in the goal and score them twice
  chassis.drive_distance(3);
  drive_for_time(500, reverse);
  chassis.drive_distance(10);
  drive_for_time(500, reverse);

  //touch the bar
  chassis.drive_distance(5);
  rightWing.set(false);
  chassis.left_swing_to_angle(0);
  chassis.drive_distance(20);
  chassis.left_swing_to_angle(45);
  chassis.drive_distance(26);
}
