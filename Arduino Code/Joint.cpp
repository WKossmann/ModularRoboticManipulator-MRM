#include "Joint.h"

Joint::Joint(int _stepPIN, int _dirPIN, int _enablePIN, int _endstoPIN, double _initDegree, int _type){
  stepPIN = _stepPIN;
  dirPIN = _dirPIN;
  enablePIN = _enablePIN;
  endstoPIN = _endstoPIN;
  initDegree = _initDegree;
  typeOfJoint = _type;

  stepper = new AccelStepper(1,stepPIN,dirPIN);
}

void Joint::startConfig(){
    pinMode(enablePIN, OUTPUT);
    pinMode(endstoPIN, INPUT_PULLUP);
    digitalWrite(enablePIN, LOW);

    if(typeOfJoint == JOINT_TYPE_1){
        stepper->setMaxSpeed(T1_MAX_SPEED);
        stepper->setAcceleration(T1_ACCELERATION);
        stepper->setCurrentPosition(0);        
    }else if(typeOfJoint == JOINT_TYPE_2){
        double radInit = initDegree*M_PI/180.0;
        stepper->setMaxSpeed(T2_MAX_SPEED);
        stepper->setAcceleration(T2_ACCELERATION);
        stepper->setCurrentPosition(radToStep(radInit));
    }
}

void Joint::runJoint(){
  stepper->run();
}

void Joint::moveToDegree(double _degree){
    // Serial.print(">> ");
    // Serial.print(stepper->currentPosition());
    // Serial.print(" -> ");
    if(typeOfJoint == JOINT_TYPE_1){
        long int targetStep = (long int) _degree*T1_STEP_PER_DEGREE;
        moveToStep(targetStep);
    }else if(typeOfJoint == JOINT_TYPE_2){
        long int targetStep = radToStep((_degree*M_PI/180.0));
        moveToStep(targetStep);
    }
    // Serial.println(targetStep);
}


void Joint::moveToStep(long int step){
    // Serial.print(">> ");
    // Serial.print(stepper->currentPosition());
    // Serial.print(" -> ");
    if(typeOfJoint == JOINT_TYPE_1){
        long int targetStep = step;
        if(targetStep > T1_MAX_STEP){
            targetStep = T1_MAX_STEP;
        }else if(targetStep < T1_MIN_STEP){
            targetStep = T1_MIN_STEP;
        }
        stepper->moveTo(targetStep);
    }else if(typeOfJoint == JOINT_TYPE_2){
        long int targetStep = step;
        if(targetStep > T2_MAX_STEP){
            targetStep = T2_MAX_STEP;
        }else if(targetStep < T2_MIN_STEP){
            targetStep = T2_MIN_STEP;
        }
        stepper->moveTo(targetStep);
    }
    // Serial.println(targetStep);
}

void Joint::startHoming(){
    if(typeOfJoint == JOINT_TYPE_1){
        stepper->moveTo(-T1_MAX_STEP);
    }else if(typeOfJoint == JOINT_TYPE_2){
        stepper->moveTo(2*T2_MAX_STEP);        
    }
}

void Joint::hitHome(){
    if(typeOfJoint == JOINT_TYPE_1){
        stepper->setCurrentPosition(0);
        stepper->moveTo(0);
    }else if(typeOfJoint == JOINT_TYPE_2){
        double radInit = initDegree*M_PI/180.0;
        long int _step = radToStep(radInit);
        stepper->setCurrentPosition(_step);
        stepper->moveTo(_step);
    }
}

void Joint::getPosition(){
    long int steps;
    double angle;
    if(typeOfJoint == JOINT_TYPE_1){
        steps = stepper->currentPosition();
        angle = steps/T1_STEP_PER_DEGREE;
    }else if(typeOfJoint == JOINT_TYPE_2){
        steps = stepper->currentPosition();
        angle = stepToRad(steps)*180/M_PI;
    }
    // Serial.print("Step: ");
    // Serial.print(steps);
    // Serial.print(" Angle: ");
    Serial.print(angle);
}

double Joint::stepToRad(long int _step){
  double distance = (double)_step/(double)T2_STEP_PER_MM;
  return acos((6506-pow(distance,2))/6490);
}

long int Joint::radToStep(double _rad){
  double distance = (sqrt(6506-6490*cos(_rad)));
  return distance*T2_STEP_PER_MM;
}