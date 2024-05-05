#include "vex.h"
#include "robot-config.h"

motor_group adm = motor_group(L1, R1, L2, R2, L3, R3);
motor_group intake = motor_group(intakeL, intakeR);

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
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  //chassis.set_swing_constants(12, .35, .002, 2, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(1.5, 300, 3000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 1000);

  

  //Calibrate inertial sensor
  inertialSensor.calibrate();
  wait(2000, msec);
  Controller1.rumble("--");

  /*chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(1.5, 300, 1000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);*/
}

void odom_constants(){
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
}

void six_ball_auton(){
  //6 ball full auton

  //get alliance triball from match load zone
  intake.setVelocity(100, percent);
  intake.spin(forward);
  wait(0.5, seconds);
  chassis.drive_distance(-45);
  chassis.left_swing_to_angle(315);
  leftWing.set(true);
  rightWing.set(true);
  wait(0.3, seconds);
  chassis.drive_distance(-8);
  leftWing.set(false);
  rightWing.set(false);
  wait(0.3, seconds);
  chassis.drive_distance(-5);
  //score alliance triball and the one that starts under the bar, then scores the one in the intake
  chassis.left_swing_to_angle(270);
  chassis.drive_distance(-12);
  chassis.drive_distance(8);
  chassis.turn_to_angle(0);
  chassis.turn_to_angle(90);
  chassis.drive_distance(12);
  //zero against the wall
  chassis.drive_distance(-10);
  chassis.turn_to_angle(0);
  chassis.drive_distance(-7);
  intake.spin(reverse);
  wait(0.5, seconds);
  intake.spin(forward);
  //grab the right middle triball, drop it next to the goal to score later
  chassis.drive_distance(20);
  chassis.turn_to_angle(25);
  chassis.drive_distance(25);
  chassis.drive_distance(-10);
  //spit out triball outside goal to score later
  intake.stop();
  chassis.turn_to_angle(145);
  chassis.drive_distance(13);
  intake.spin(reverse);
  wait(0.5, seconds);
  chassis.drive_distance(-13);
  //pick up middle middle triball, and score two with wings
  chassis.turn_to_angle(55);
  intake.spin(forward);
  chassis.drive_distance(23);
  chassis.drive_distance(-1);
  chassis.turn_to_angle(0);
  leftWing.set(true);
  rightWing.set(true);
  wait(0.3, seconds);
  chassis.drive_distance(-25);
  chassis.drive_distance(10);
  leftWing.set(false);
  rightWing.set(false);
  //score triball in intake
  chassis.turn_to_angle(180);
  chassis.drive_distance(18);
  //touch the bar
  chassis.set_drive_constants(5, 1.5, 0, 10, 0);
  chassis.drive_distance(-35);
  intake.spin(reverse);
  wait(0.3, seconds);
  intake.stop();
  chassis.drive_distance(2);
  chassis.turn_to_angle(-80);
  chassis.drive_distance(35);
  chassis.drive_distance(-4);
  chassis.turn_to_angle(-76);
  //chassis.turn_to_angle(-45);
  //chassis.drive_distance(35);


  /*chassis.drive_distance(6);
  chassis.drive_distance(12);
  chassis.drive_distance(18);
  chassis.drive_distance(-36);*/
}

void Match_Load_AWP(){
  //Match loading + AWP auton

  //This auton does 10 match loads, tries to score them, and gets it's half of the AWP and touches the bar

  //This is the first part of the 6 ball auton, up until it scores the alliance triball and the preload in the goal
  
  //get alliance triball from match load zone
  intake.setVelocity(100, percent);
  intake.spin(forward);
  wait(0.3, seconds);
  chassis.drive_distance(-43);
  chassis.left_swing_to_angle(315);
  leftWing.set(true);
  rightWing.set(true);
  chassis.drive_distance(-10);
  leftWing.set(false);
  wait(0.3, seconds);
  chassis.drive_distance(-5);

  //score alliance triball and the one that starts under the bar, then spits out the one in the intake
  chassis.left_swing_to_angle(270);
  wait(0.3, seconds);
  drive_for_time(750, reverse);
  rightWing.set(false);
  chassis.drive_distance(8);
  chassis.turn_to_angle(0);
  chassis.turn_to_angle(90);
  drive_for_time(750, forward);

  //zero against the wall
  chassis.drive_distance(-10);
  chassis.turn_to_angle(0);
  intake.spin(reverse);
  drive_for_time(350, reverse);

  //go get match loads
  chassis.right_swing_to_angle(-45);
  chassis.drive_distance(23);
  chassis.left_swing_to_angle(0);
  //The rest of the auton is copy/paste from prog skills (as of 3/1/24), with a slightly different number for the alley straight

  chassis.drive_distance(62);
  chassis.left_swing_to_angle(30);
  chassis.drive_distance(12);
  leftWing.set(true);
  rightWing.set(true);
  chassis.left_swing_to_angle(48);

  chassis.drive_distance(-10);

  int matchLoad = 0;

  while(matchLoad < 8)
  {
    chassis.drive_distance(8);
    chassis.drive_distance(-8);
    matchLoad = matchLoad + 1;
  }

  leftWing.set(false);
  wait(0.2, seconds);
  chassis.drive_distance(-6);
  //bulldoze them down the alley and into the goal
  chassis.left_swing_to_angle(0);
  intake.setVelocity(100, percent);
  intake.spin(forward);
  chassis.set_drive_constants(8, 1.5, 0, 10, 0);
  
  //chassis.drive_distance(-63); (removed to prevent wing hitting vertical pole)
  chassis.drive_distance(-15);
  rightWing.set(false);
  chassis.drive_distance(-20);
  rightWing.set(true);
  chassis.drive_distance(-28);

  chassis.left_swing_to_angle(-30);
  chassis.drive_distance(-20);
  chassis.left_swing_to_angle(-90);
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  drive_for_time(500, reverse);
  //ram the goal a second time (removed to save time)
  chassis.drive_distance(8);
  drive_for_time(500, reverse);
  chassis.drive_distance(5);
  //touch the bar
  chassis.left_swing_to_angle(-45);
  rightWing.set(false);
  chassis.drive_distance(27);
  chassis.left_swing_to_angle(0);
  chassis.drive_distance(20);

}

void AWP_Plus_One(){
  //Just the AWP + 1 auton

  //set intake up to spin forward to release 
  
  //get alliance triball from match load zone
  intake.setVelocity(100, percent);
  intake.spin(forward);
  wait(0.5, seconds);
  chassis.drive_distance(-45);
  chassis.left_swing_to_angle(315);
  leftWing.set(true);
  rightWing.set(true);
  wait(0.3, seconds);
  chassis.drive_distance(-8);
  leftWing.set(false);
  rightWing.set(false);
  wait(0.3, seconds);
  chassis.drive_distance(-5);
  //score alliance triball and the one that starts under the bar, then scores the one in the intake
  chassis.left_swing_to_angle(270);
  //chassis.drive_distance(-12);
  drive_for_time(500, reverse);
  chassis.drive_distance(8);
  chassis.turn_to_angle(0);
  chassis.turn_to_angle(90);
  //chassis.drive_distance(12);
  drive_for_time(500);
  intake.spin(reverse);
  //zero against the wall
  chassis.drive_distance(-10);
  chassis.turn_to_angle(0);
  drive_for_time(500, reverse);
  //chassis.drive_distance(-7);
  wait(0.5, seconds);
  intake.spin(forward);
  //grab the right middle right triball (the one completely on our side)
  chassis.drive_distance(20);
  chassis.turn_to_angle(25);
  chassis.drive_distance(25);
  chassis.drive_distance(-10);
  //score triball in the goal
  chassis.turn_to_angle(145);
  chassis.drive_distance(13);
  chassis.left_swing_to_angle(180);
  chassis.drive_distance(-5);
  intake.spin(reverse);
  drive_for_time(500);
  chassis.drive_distance(-10);
  drive_for_time(500);
  //touch the bar
  chassis.set_drive_constants(5, 1.5, 0, 10, 0);
  intake.spin(reverse);
  chassis.drive_distance(-35);
  wait(0.3, seconds);
  intake.stop();
  chassis.drive_distance(2);
  chassis.turn_to_angle(-80);
  chassis.drive_distance(35);
  chassis.drive_distance(-4);
  chassis.turn_to_angle(-76);
}

void Prog_Skills(){
  //Start with the robot on the left side (from the driver station), aka Starting Tiles Robot 1, sideways against the match load bar,
  //with the intake just touching the driver station wall (when the intake is deployed).

  //go back and forth 11 times to get 11 match loads out of the zone
  
  leftWing.set(true);
  rightWing.set(true);
  wait(.2, seconds);
  chassis.drive_distance(-8);


  int matchLoad = 0;

  while(matchLoad < 10)
  {
    chassis.drive_distance(8);
    chassis.drive_distance(-8);
    matchLoad = matchLoad + 1;
  }

  rightWing.set(false);
  wait(0.2, seconds);
  chassis.drive_distance(-9);
  //bulldoze them down the alley and into the goal
  chassis.right_swing_to_angle(45);
  intake.setVelocity(100, percent);
  intake.spin(forward);
  chassis.set_drive_constants(7, 1.5, 0, 10, 0);
  //chassis.drive_distance(-60); (removed to prevent wing hitting vertical pole)
  
  chassis.drive_distance(-15);
  leftWing.set(false);
  chassis.drive_distance(-20);
  leftWing.set(true);
  chassis.drive_distance(-30);

  chassis.right_swing_to_angle(75);
  chassis.drive_distance(-20);
  chassis.right_swing_to_angle(135);
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  drive_for_time(1000, reverse);
  //ram the goal a second time
  chassis.drive_distance(8);
  drive_for_time(1000, reverse);

  //Go back for the second round of triballs
  chassis.drive_distance(8);
  leftWing.set(false);
  chassis.right_swing_to_angle(90);
  chassis.drive_distance(20);
  chassis.right_swing_to_angle(45);
  intake.setVelocity(100, percent);
  intake.spin(reverse);
  chassis.drive_distance(61);
  /*//zero on the left wall
  chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  chassis.turn_to_angle(-45);
  drive_for_time(300, reverse);
  //zero on back wall (aka driver station wall)
  chassis.drive_distance(20);
  chassis.turn_to_angle(215);
  drive_for_time(1000, reverse);
  //line up with match load zone to load 11 more triballs
  chassis.drive_distance(5);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-3);*/
  chassis.right_swing_to_angle(25);
  chassis.drive_distance(10);
  chassis.right_swing_to_angle(-5);
  leftWing.set(true);
  rightWing.set(true);
  wait(300, msec);
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);

  //Finishing the auto is just the same as doing the first part again, so I'm literally copy/pasting the
  //first part until it scores into the goal below, and it should work.

  //When you figure out the correct numbers, just copy them from the first part of the code down here.
  //Fyi this code is super similar to the quals match load auton I've been meaning to write, so use this as a guide.

  chassis.drive_distance(-8);

  matchLoad = 0;

  // while(matchLoad < 9)
  // {
  //   chassis.drive_distance(8);
  //   chassis.drive_distance(-8);
  //   matchLoad = matchLoad + 1;
  // }

  for (int i = 0; i < 10; i++) {
    chassis.drive_distance(8);
    chassis.drive_distance(-8);
  }

  rightWing.set(false);
  wait(0.2, seconds);
  chassis.drive_distance(-9);
  //bulldoze them down the alley and into the goal
  chassis.right_swing_to_angle(45);
  intake.setVelocity(100, percent);
  intake.spin(forward);
  chassis.set_drive_constants(7, 1.5, 0, 10, 0);
  //chassis.drive_distance(-60); (removed to prevent wing hitting vertical pole)
  thread([](){
    wait(1200, msec);
    leftWing.set(false);
    wait(400, msec);
    leftWing.set(true);
  });
  chassis.drive_distance(-61);  

  chassis.right_swing_to_angle(75);
  chassis.drive_distance(-20);
  chassis.right_swing_to_angle(135);
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  drive_for_time(1000, reverse);
  //ram the goal a second time
  chassis.drive_distance(8);
  drive_for_time(1000, reverse);
  chassis.drive_distance(5);




}

void odom_test(){
  //Empty auton slot

  //swing test
  chassis.right_swing_to_angle(45);
  chassis.left_swing_to_angle(0);
  chassis.right_swing_to_angle(90);
  chassis.left_swing_to_angle(0);
}

void holonomic_odom_test(){
  //Empty auton slot

  //This is just a test (that didn't work), no real need to keep it if we need the auton
  //Drive to Point test
  default_constants();
  inertialSensor.calibrate();
  wait(2000, msec);
  Controller1.rumble("--");
  chassis.set_coordinates(0, 0, 0);
  intake.setVelocity(100, percent);
  intake.spin(forward);
  chassis.drive_to_point(0, -5);
  chassis.drive_to_point(0, -1);
  chassis.drive_to_point(0, -11);
  chassis.drive_to_point(0,-2);
  chassis.drive_to_point(0, -22);
  chassis.drive_to_point(0, -3);

}

void worlds_auton(){
  //Worlds Auton

  //AWP + score some form the middle and cross the bar to start on the far side

  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  //get alliance triball from match load zone
  intake.setVelocity(100, percent);
  intake.spin(forward);
  wait(0.3, seconds);
  chassis.drive_distance(-23);
  chassis.left_swing_to_angle(315);
  leftWing.set(true);
  rightWing.set(true);
  chassis.drive_distance(-5);
  leftWing.set(false);
  wait(0.3, seconds);
  chassis.drive_distance(-3);

  //score alliance triball and the one that starts under the bar, then spits out the one in the intake
  chassis.left_swing_to_angle(270);
  wait(0.3, seconds);
  drive_for_time(750, reverse);
  rightWing.set(false);
  chassis.drive_distance(4);
  chassis.turn_to_angle(0);
  chassis.turn_to_angle(90);
  drive_for_time(650, forward);

  //zero against the wall
  chassis.drive_distance(-5);
  chassis.turn_to_angle(0);
  intake.spin(reverse);
  drive_for_time(350, reverse);

  //Pick up middle triball that is touching the bar


  intake.spin(forward);
  chassis.drive_distance(8);
  chassis.turn_to_angle(44);
  chassis.drive_distance(20);
  //spit out the one in the intake
  chassis.drive_distance(-10);
  chassis.turn_to_angle(140);
  chassis.drive_distance(5);
  intake.setVelocity(20, percent);
  intake.spin(reverse);
  wait(0.4, seconds);
  chassis.drive_distance(-5);
  intake.spin(forward);
  intake.setVelocity(100, percent);
  //pick up the second triball touching the bar
  chassis.turn_to_angle(20);
  chassis.drive_distance(7);
  chassis.turn_to_angle(70);
  chassis.drive_distance(8);
  wait(0.2, seconds);
  chassis.drive_distance(-9);

  //wing the two triballs not touching the bar into the goal
  chassis.right_swing_to_angle(0);
  leftWing.set(true);
  rightWing.set(true);
  drive_for_time(1000, reverse, 7);
  chassis.drive_distance(5);
  leftWing.set(false);
  rightWing.set(false);
  chassis.turn_to_angle(180);
  drive_for_time(400);
  intake.spin(reverse);

  //pick up 4th triball

  //Commented out to save time, put back in if we have extra time

  // chassis.drive_distance(-7);
  // intake.spin(forward);
  // chassis.turn_to_angle(90);
  // chassis.drive_distance(3);
  // wait(0.2, seconds);
  // chassis.drive_distance(-3);
  // chassis.turn_to_angle(180);
  // drive_for_time(600);
  // intake.spin(reverse);

  //cross the bar and touch the bar

  chassis.drive_distance(-7);
  chassis.left_swing_to_angle(-35);
  chassis.drive_distance(4);

  //drive over the bar
  // pneuIntake.set(true);
  chassis.turn_to_angle(0);
  // while(inertialSensor.pitch() < 10)
  // {
  //   drive_for_time(100);
  // }
  // while(inertialSensor.pitch() > 10)
  // {
  //   drive_for_time(100);
  // }
  chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  intake.spin(forward);
  drive_for_time(1000, forward, 3);

  // wait(1, seconds);

  //drive_for_time(1800);

  // pneuIntake.set(false);
  // wait(0.2, seconds);
  chassis.drive_distance(-5); 
  chassis.turn_to_angle(90);
  chassis.drive_distance(6);
  chassis.turn_to_angle(180);
  drive_for_time(700);
  intake.spin(reverse);
  drive_for_time(1500, reverse, 5);
  //touch the bar
  //chassis.drive_distance(3);
  chassis.turn_to_angle(-75);
  //pneuIntake.set(true);
  drive_for_time(1500, forward, 4);
  chassis.set_swing_exit_conditions(1.5, 300, 800);
  chassis.left_swing_to_angle(-90);
  chassis.drive_distance(-2);
  chassis.turn_to_angle(-70);


}

void safe_worlds_auton(){
  //Safe worlds auton
  //Maybe use for safe auton where we shave a few seconds off


}