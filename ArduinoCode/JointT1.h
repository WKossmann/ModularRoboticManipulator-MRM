//This class defines the joint type 1
#ifndef JointT1_h
#define JointT1_h

#include <AccelStepper.h>
#define T1_MAX_STEP         13100
#define T1_MIN_STEP         0
#define T1_STEP_PER_DEGREE  44.44448
#define T1_MAX_SPEED        12800
#define T1_ACCELERATION     3600

class JointT1{
  public:
    JointT1(int _stepPIN, int _dirPIN, int _enablePIN, int _endstoPIN);
       
    void startConfig();
    void runJoint();
    void moveToDegree(double degree);
    void moveToStep(long int step);
    void moveToRadian(double radian);
    void startHoming();
    void hitHome();
    void getPosition();
    AccelStepper* stepper;

  private:
    
    int stepPIN;
    int dirPIN;
    int enablePIN;
    int endstoPIN;
};
  
#endif
