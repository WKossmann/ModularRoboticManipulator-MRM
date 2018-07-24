//This class defines the joint type 1
#ifndef Joint_h
#define Joint_h

#include <AccelStepper.h>

#define T1_MAX_STEP         13100
#define T1_MIN_STEP         0
#define T1_STEP_PER_DEGREE  44.44448
#define T1_MAX_SPEED        12800
#define T1_ACCELERATION     5000

#define T2_MAX_STEP         277600 
#define T2_MIN_STEP         159600
#define T2_STEP_PER_MM      2560
#define T2_MAX_SPEED        30000
#define T2_ACCELERATION     30000

#define JOINT_TYPE_1 1
#define JOINT_TYPE_2 2

class Joint{
  public:
    Joint(int _stepPIN, int _dirPIN, int _enablePIN, int _endstoPIN, double _initDegree, int _type);
       
    void startConfig();
    void runJoint();
    void moveToDegree(double degree);
    void moveToStep(long int step);
    void startHoming();
    void hitHome();
    void getPosition();
    AccelStepper* stepper;

    //For type 2:
    double stepToRad(long int _step);
    long int radToStep(double _rad);

  private:
    
    int stepPIN;
    int dirPIN;
    int enablePIN;
    int endstoPIN;
    int typeOfJoint = 0;

    //For type 2:
    double initDegree;
};

#endif