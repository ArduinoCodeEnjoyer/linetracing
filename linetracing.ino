#include <ATX2.h>

int sensor[5]={0};
float error = 0;
float P = 0, I = 0, D = 0;
float prev_error = 0, prev_I = 0;

float Kp = 20,Ki = 0,Kd = 15;
float PID_Value = 0;
int base_speed = 30;
int Lspeed = 0;
int Rspeed = 0;

void setup(){
  XIO();  // ATX2 initialize
  setTextSize(2);
  glcdMode(3);
}


void loop() {
  sensor[0] = digitalRead(24); //edit
  sensor[1] = digitalRead(25); //edit
  sensor[2] = digitalRead(26); //edit
  sensor[3] = digitalRead(27); //edit
  sensor[4] = digitalRead(28); //edit
  
  glcd(0,0,"L=%d",sensor[0]);
  glcd(0,0,"LC=%d",sensor[1]);
  glcd(0,0,"CEN=%d",sensor[2]);
  glcd(0,0,"RC=%d",sensor[3]);
  glcd(0,0,"R=%d",sensor[4]);
  
  if((sensor[0] = 0)&&(sensor[1] = 0)&&(sensor[2] = 0)&&(sensor[3] = 0)&&(sensor[4] = 1)){
    error = 4;
  }
  else if((sensor[0] = 0)&&(sensor[1] = 0)&&(sensor[2] = 0)&&(sensor[3] = 1)&&(sensor[4] = 1)){
    error = 3;
  }
  else if((sensor[0] = 0)&&(sensor[1] = 0)&&(sensor[2] = 0)&&(sensor[3] = 1)&&(sensor[4] = 0)){
    error = 2;
  }
  else if((sensor[0] = 0)&&(sensor[1] = 0)&&(sensor[2] = 1)&&(sensor[3] = 1)&&(sensor[4] = 0)){
    error = 1;
  }
  else if((sensor[0] = 0)&&(sensor[1] = 0)&&(sensor[2] = 1)&&(sensor[3] = 0)&&(sensor[4] = 0 )){
    error = 0;
  }
  else if((sensor[0] = 0)&&(sensor[1] = 1)&&(sensor[2] = 1)&&(sensor[3] = 0)&&(sensor[4] = 0)){
    error = -1;
  }
  else if((sensor[0] = 0)&&(sensor[1] = 1)&&(sensor[2] = 0)&&(sensor[3] = 0)&&(sensor[4] = 0)){
    error = -2;
  }
  else if((sensor[0] = 1)&&(sensor[1] = 1)&&(sensor[2] = 0)&&(sensor[3] = 0)&&(sensor[4] = 0)){
    error = -3;
  }
  else if((sensor[0] = 1)&&(sensor[1] = 0)&&(sensor[2] = 0)&&(sensor[3] = 0)&&(sensor[4] = 0)){
    error = -4;
  }

  P = error;
  I = I + prev_I;
  D = error - prev_error;
  
  PID_Value = (Kp*P) + (Ki*I) + (Kd*D);

  prev_I = I;
  prev_error = error;
  
  float Lspeed = base_speed + PID_Value;
  float Rspeed = base_speed - PID_Value;

  if(Lspeed > 100){
    Lspeed = 100;
  }
  if(Rspeed > 100){
    Rspeed = 100;
  }
  if(Lspeed < -100){
    Lspeed = -100;
  }
  if(Rspeed < -100){
    Rspeed = -100;
  }
  motor(1,Lspeed);
  motor(2,Rspeed);
}
