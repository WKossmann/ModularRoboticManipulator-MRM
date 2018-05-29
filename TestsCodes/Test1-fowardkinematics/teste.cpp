#include <iostream>
#include <cmath>

using namespace std;
#define J2_A 9.5
#define J2_B 9.5
#define J1_H 7.6

void jointT1FowardK(double rad, double pos[4][4]){
    //First Collum
    pos[0][0] = cos(rad);
    pos[1][0] = sin(rad);
    pos[2][0] = 0;
    pos[3][0] = 0;
    //Second Collum
    pos[0][1] = -sin(rad);
    pos[1][1] = cos(rad);
    pos[2][1] = 0;
    pos[3][1] = 0;
    //Third Collum
    pos[0][2] = 0;
    pos[1][2] = 0;
    pos[2][2] = 1;
    pos[3][2] = 0;
    //Fourth Collum
    pos[0][3] = 0;
    pos[1][3] = 0;
    pos[2][3] = J1_H;
    pos[3][3] = 1;
}
void jointT2FowardK(double rad, double pos[4][4]){
    //First Collum
    pos[0][0] = sin(rad);
    pos[1][0] = 0;
    pos[2][0] = -cos(rad);
    pos[3][0] = 0;
    //Second Collum
    pos[0][1] = 0;
    pos[1][1] = 1;
    pos[2][1] = -1;
    pos[3][1] = 0;
    //Third Collum
    pos[0][2] = cos(rad);
    pos[1][2] = 0;
    pos[2][2] = sin(rad);
    pos[3][2] = 0;
    //Fourth Collum
    pos[0][3] = J2_B*cos(rad);
    pos[1][3] = 0;
    pos[2][3] = J2_A + J2_B*sin(rad);
    pos[3][3] = 1;
}
void multiMatrix(double A[4][4], double B[4][4], double R[4][4]){
    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 4; ++j){
            R[i][j] = 0;
            for(int k = 0; k < 4; ++k)
            {
                R[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int main(){
    double t1 = 45;
    double t2 = 0;
    double t3 = 0;
 
    double M0T1[4][4];
    double M1T2[4][4];
    double M2T3[4][4];
    double RES1[4][4];
    double RES2[4][4];
    
    jointT1FowardK(t1*M_PI/180.0, M0T1);
    jointT2FowardK(t2*M_PI/180.0, M1T2);
    jointT2FowardK(t3*M_PI/180.0, M2T3);

    multiMatrix(M0T1, M1T2, RES1);
    multiMatrix(RES1, M1T2, RES2);

    cout << "X : " << RES2[0][3] << endl;
    cout << "Y : " << RES2[1][3] << endl;
    cout << "Z : " << RES2[2][3] << endl;

    return 0;
}
