#include "JointT2.h"

JointT2::JointT2(int _stepPIN, int _dirPIN, int _enablePIN, int _endstoPIN, double _initDegree){
  stepPIN = _stepPIN;
  dirPIN = _dirPIN;
  enablePIN = _enablePIN;
  endstoPIN = _endstoPIN;
  initDegree = _initDegree;

  stepper = new AccelStepper(1,stepPIN,dirPIN);
}

void JointT2::startConfig(){
  double radInit = initDegree*M_PI/180.0;

  pinMode(enablePIN, OUTPUT);
  pinMode(endstoPIN, INPUT_PULLUP);
  digitalWrite(enablePIN, LOW);

  stepper->setMaxSpeed(T2_MAX_SPEED);
  stepper->setAcceleration(T2_ACCELERATION);
  stepper->setCurrentPosition(radToStep(radInit));
}

void JointT2::moveToDegree(double _degree){
  // Serial.print(">> ");
  // Serial.print(stepper->currentPosition());
  // Serial.print(" -> ");

  long int targetStep = radToStep((_degree*M_PI/180.0));
  if(targetStep > T2_MAX_STEP){
    targetStep = T2_MAX_STEP;
  }else if(targetStep < T2_MIN_STEP){
    targetStep = T2_MIN_STEP;
  }
  stepper->moveTo(targetStep);

  // Serial.println(targetStep);
}

void JointT2::moveToStep(long int step){
  // Serial.print(">> ");
  // Serial.print(stepper->currentPosition());
  // Serial.print(" -> ");

  long int targetStep = step;
  if(targetStep > T2_MAX_STEP){
    targetStep = T2_MAX_STEP;
  }else if(targetStep < T2_MIN_STEP){
    targetStep = T2_MIN_STEP;
  }
  stepper->moveTo(targetStep);

  // Serial.println(targetStep);
}

void JointT2::moveToRadian(double _rad){
  // Serial.print(">> ");
  // Serial.print(stepper->currentPosition());
  // Serial.print(" -> ");

  long int targetStep = radToStep(_rad);
  if(targetStep > T2_MAX_STEP ){
    targetStep = T2_MAX_STEP;
  }else if(targetStep < T2_MIN_STEP){
    targetStep = T2_MIN_STEP;
  }
  stepper->moveTo(targetStep);

  // Serial.println(targetStep);
}

void JointT2::runJoint(){
  stepper->run();
}

double JointT2::stepToRad(long int _step){
  double distance = (double)_step/(double)T2_STEP_PER_MM;
  return acos((6506-pow(distance,2))/6490);
}

long int JointT2::radToStep(double _rad){
  double distance = (sqrt(6506-6490*cos(_rad)));
  return distance*T2_STEP_PER_MM;
}

void JointT2::startHoming(){
  stepper->moveTo(2*T2_MAX_STEP);
}
void JointT2::hitHome(){
  double radInit = initDegree*M_PI/180.0;
  long int _step = radToStep(radInit);
  stepper->setCurrentPosition(_step);
  stepper->moveTo(_step);
}

void JointT2::getPosition(){
  long int steps = stepper->currentPosition();
  double angle = stepToRad(steps)*180/M_PI;
  //Serial.print("Step: ");
  //Serial.print(steps);
  //Serial.print(" Angle: ");
  //Serial.println(angle);
}