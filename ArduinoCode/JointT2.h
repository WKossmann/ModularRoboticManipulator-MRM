//This class defines the joint type 2
#ifndef JointT2_h
#define JointT2_h

#include <AccelStepper.h>
#define T2_MAX_STEP         277600
#define T2_MIN_STEP         159600
#define T2_STEP_PER_MM      2560
#define T2_MAX_SPEED        51200
#define T2_ACCELERATION     7200

class JointT2{
  public:
    JointT2(int _stepPIN, int _dirPIN, int _enablePIN, int _endstoPIN, double _initDegree);
       
    void startConfig();
    void runJoint();
    void moveToDegree(double degree);
    void moveToStep(long int step);
    void moveToRadian(double radian);
    long int degreeToStep(double degree);
    double stepToRad(long int _step);
    long int radToStep(double _rad);
    void startHoming();
    void hitHome();
    void getPosition();
 
  private:
    AccelStepper* stepper;
    int stepPIN;
    int dirPIN;
    int enablePIN;
    int endstoPIN;
    double initDegree;
};
  
#endif