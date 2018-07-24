#include "Pins.h"
#include "Joint.h"


Joint JA(A_STEP_PIN, A_DIR_PIN, A_ENABLE_PIN, A_ENDSTOP_PIN, A_INITIAL_ANGLE, JOINT_TYPE_1);
Joint JB(B_STEP_PIN, B_DIR_PIN, B_ENABLE_PIN, B_ENDSTOP_PIN, B_INITIAL_ANGLE, JOINT_TYPE_2);
Joint JC(C_STEP_PIN, C_DIR_PIN, C_ENABLE_PIN, C_ENDSTOP_PIN, C_INITIAL_ANGLE, JOINT_TYPE_2);

const int tam_cmd = 50;
char cmd[tam_cmd];
char num[tam_cmd];
bool moving = false;

void goHomeAll();
void goHomePArcial(bool _joint[]);
void interpretaComando();
void cleanNUM();
void cleanCMD();


void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);

  JA.startConfig();
  JB.startConfig();
  JC.startConfig();
}

void loop() {
  if(!moving && Serial.available()){
    Serial.readBytesUntil(';', cmd, tam_cmd);
    //Serial.print("Received: ");
    //Serial.println(cmd);
    interpretaComando();
  }

  if(moving == true && !JA.stepper->isRunning() && !JB.stepper->isRunning() && !JC.stepper->isRunning()){
    Serial.println("#");
    moving = false;
  }
  JA.stepper->run();
  JB.stepper->run();
  JC.stepper->run();
}

void interpretaComando(){
  //Comands G:
  if(cmd[0] == 'G' || cmd[0] == 'g'){
    
    //Comand G1 (Moves to a target angle (in degree)):
    if(cmd[1] == '1'){
      int index = 2;
      // Run through the string, catching every comands    
      while(cmd[index] != '\0'){
        
        // Blank space, jump over  
        if(cmd[index]==' '){
          index++;
        }

        //Number without a joint as reference  (error)
        else if(cmd[index] >= '0' && cmd[index] <= '9'){
          break;
        }

        // Comand for joint A
        else if(cmd[index]=='A' || cmd[index]=='a'){
          index++;
          // Check if it is a number after the comand
          if(cmd[index] >= '0' && cmd[index] <= '9'){
            int counter = 0;
            //Read the whole number
            while(!(cmd[index] == ' ' || cmd[index] == '\0'|| (cmd[index]>='a' && cmd[index]<='c') || (cmd[index]>='A' && cmd[index]<='C'))){
                num[counter] = cmd[index];
                counter++;
                index++;
            }
            double valor = atof(num);
            JA.moveToDegree(valor);
            moving = true;
          }else{ //A referenced joint without any value associated (error)
              break;
          }
          cleanNUM();
        }

        // Comand for joint B
        else if(cmd[index]=='B' || cmd[index]=='b'){
          index++;
          // Check if it is a number after the comand
          if(cmd[index] >= '0' && cmd[index] <= '9'){
            int counter = 0;
            //Read the whole number
            while(!(cmd[index] == ' ' || cmd[index] == '\0' || (cmd[index]>='a' && cmd[index]<='c') || (cmd[index]>='A' && cmd[index]<='C'))){
                num[counter] = cmd[index];
                counter++;
                index++;
            }
            double valor = atof(num);
            JB.moveToDegree(valor);
            moving = true;
          }else{ //A referenced joint without any value associated (error)
              break;
          }
          cleanNUM();
        }
        
        // Comand for joint C
        else if(cmd[index]=='C' || cmd[index]=='c'){
          index++;
          // Check if it is a number after the comand
          if(cmd[index] >= '0' && cmd[index] <= '9'){
            int counter = 0;
            //Read the whole number
            while(!(cmd[index] == ' ' || cmd[index] == '\0' || (cmd[index]>='a' && cmd[index]<='c') || (cmd[index]>='A' && cmd[index]<='C'))){
                num[counter] = cmd[index];
                counter++;
                index++;
            }
            double valor = atof(num);
            JC.moveToDegree(valor);
            moving = true;
          }else{ //A referenced joint without any value associated (error)
              break;
          }
          cleanNUM();
        }
      }
    }

    //Comand G28 (Moves to endstops (detecting it)): 
    if(cmd[1]=='2' && cmd[2]=='8'){
      bool foundParameter = false;
      bool homeJoints[3] = {false,false,false};
      int index = 3;
      // Run through the string, catching every comands    
      while(cmd[index] != '\0'){
        
        // Blank space, jump over  
        if(cmd[index]==' '){
          index++;
        }

        //Number without a joint as reference  (error)
        else if(cmd[index] >= '0' && cmd[index] <= '9'){
          break;
        }

        // Comand for joint A
        else if(cmd[index]=='A' || cmd[index]=='a'){
          index++;
          homeJoints[0] = true;
          foundParameter = true;
        }

        // Comand for joint B
        else if(cmd[index]=='B' || cmd[index]=='b'){
          index++;
          homeJoints[1] = true;
          foundParameter = true;
        }
        
        // Comand for joint C
        else if(cmd[index]=='C' || cmd[index]=='c'){
          index++;
          homeJoints[2] = true;
          foundParameter = true;
        }
      }
      if(!foundParameter){
        goHomeAll();
      }else{
        goHomeParcial(homeJoints);
      }
    }
  }

  //Comands M:
  else if(cmd[0] == 'M' || cmd[0] == 'm'){
    
    //Comand M114 (Get current positions):
    if(cmd[1] == '1' && cmd[2] == '1' && cmd[3] == '4'){
      JA.getPosition();
      Serial.print(", ");
      JB.getPosition();
      Serial.print(", ");
      JC.getPosition();
      Serial.println(";");
    }
  }
  cleanCMD();  
}
//
void goHomeAll(){
  bool hit_a = false, hit_b = false, hit_c = false;
  JA.startHoming();
  JB.startHoming();
  JC.startHoming();
  while(true){
    if(digitalRead(B_ENDSTOP_PIN) == LOW && hit_b == false){
      JB.hitHome();
      hit_b = true;
      //Serial.println(">> HIT B");
    }else{
      JB.runJoint();
    }
    if(digitalRead(C_ENDSTOP_PIN) == LOW && hit_c == false){
      JC.hitHome();
      hit_c = true;
      //Serial.println(">> HIT C");
    }else{
      JC.runJoint();
    }
    if(hit_b && hit_c){
      break;
    }
  }
  while(true){
    if(digitalRead(A_ENDSTOP_PIN) == LOW && hit_a == false){
      JA.hitHome();
      hit_a = true;
      //Serial.println(">> HIT A");
      break;
    }else{
      JA.runJoint();
    }
  }
  Serial.println("#");
}

void goHomeParcial(bool _joint[]){
  bool hit_a = true, hit_b = true, hit_c = true;
  
  if(_joint[0]){
    JA.startHoming();
    hit_a = false;
  }
  if(_joint[1]){
    JB.startHoming();
    hit_b = false;
  }
  if(_joint[2]){
    JC.startHoming();
    hit_c = false;
  }

  while(true){
    if(digitalRead(A_ENDSTOP_PIN) == LOW && hit_a == false){
      JA.hitHome();
      hit_a = true;
      //Serial.println(">> HIT A");
    }else{
      JA.runJoint();
    }
    // ###########
    if(digitalRead(B_ENDSTOP_PIN) == LOW && hit_b == false){
      JB.hitHome();
      hit_b = true;
      //Serial.println(">> HIT B");
    }else{
      JB.runJoint();
    }
    // ###########
    if(digitalRead(C_ENDSTOP_PIN) == LOW && hit_c == false){
      JC.hitHome();
      hit_c = true;
      //Serial.println(">> HIT C");
    }else{
      JC.runJoint();
    }
    // ########### 
    if(hit_a && hit_b && hit_c){
      break;
    }
  }
  Serial.println("#");
}
void cleanCMD(){
  for(int i=0; i<tam_cmd;i++){
    cmd[i] = '\0';
  }
}
void cleanNUM(){
  for(int i=0; i<tam_cmd;i++){
    num[i] = '\0';
  }
}