#include "JointT1.h"

JointT1::JointT1(int _stepPIN, int _dirPIN, int _enablePIN, int _endstoPIN){
  stepPIN = _stepPIN;
  dirPIN = _dirPIN;
  enablePIN = _enablePIN;
  endstoPIN = _endstoPIN;

  stepper = new AccelStepper(1,stepPIN,dirPIN);
}

void JointT1::startConfig(){
  pinMode(enablePIN, OUTPUT);
  pinMode(endstoPIN, INPUT_PULLUP);
  digitalWrite(enablePIN, LOW);
  stepper->setMaxSpeed(T1_MAX_SPEED);
  stepper->setAcceleration(T1_ACCELERATION);
}

void JointT1::moveToDegree(double degree){
  Serial.print(">> ");
  Serial.print(stepper->currentPosition());
  Serial.print(" -> ");

  long int targetStep = (long int) degree*T1_STEP_PER_DEGREE;
  if(targetStep > T1_MAX_STEP){
    targetStep = T1_MAX_STEP;
  }else if(targetStep < T1_MIN_STEP){
    targetStep = T1_MIN_STEP;
  }
  stepper->moveTo(targetStep);

  Serial.println(targetStep);
}

void JointT1::moveToStep(long int step){
  Serial.print(">> ");
  Serial.print(stepper->currentPosition());
  Serial.print(" -> ");

  long int targetStep = step;
  if(targetStep > T1_MAX_STEP){
    targetStep = T1_MAX_STEP;
  }else if(targetStep < T1_MIN_STEP){
    targetStep = T1_MIN_STEP;
  }
  stepper->moveTo(targetStep);

  Serial.println(targetStep);
}

void JointT1::moveToRadian(double radian){
  Serial.print(">> ");
  Serial.print(stepper->currentPosition());
  Serial.print(" -> ");

  double degree = (radian*PI)/180.0;
  long int targetStep = (long int) degree*T1_STEP_PER_DEGREE;
  if(targetStep > T1_MAX_STEP){
    targetStep = T1_MAX_STEP;
  }else if(targetStep < T1_MIN_STEP){
    targetStep = T1_MIN_STEP;
  }
  stepper->moveTo(targetStep);

  Serial.println(targetStep);
}

void JointT1::runJoint(){
  stepper->run();
}

void JointT1::startHoming(){
  stepper->moveTo(-T1_MAX_STEP);
}
    
void JointT1::hitHome(){
  stepper->setCurrentPosition(0);
  stepper->moveTo(0);
}

void JointT1::getPosition(){
  long int steps = stepper->currentPosition();
  double angle = steps/T1_STEP_PER_DEGREE;
  Serial.print("Step: ");
  Serial.print(steps);
  Serial.print(" Angle: ");
  Serial.println(angle);
}