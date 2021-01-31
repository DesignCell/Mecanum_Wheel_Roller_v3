//Declarations
int x1,y1,x2,y2; // Define analog input varibales
int w1,w2,w3,w4; // Define wheel speeds
int cnt; //analog read delay

// Coefficients
const int L1 = 3.55; // Width from center
const int L2 = 3.35; // Length from center
const int x1m = 4000; // X1 Limit (-flip sense)
const int y1m = -4000; // Y1 Limit (-flip sense)
const int x2m = -150; // X2 Limit (-flip sense)
//const int y2m = 50; // Y2 Limit (-flip sense)

//Analog Joystick Pins
const int x1ap = A0;
const int y1ap = A1;
const int x2ap = A2;
//const int y2ap = A3;

// (4) A4988 Stepper Driver Pins
const int e1 = 2; ///Driver 1 Enable
const int d1 = 3; ///Driver 1 Direction
const int s1 = 4; ///Driver 1 Step
const int e2 = 5; ///Driver 2 Enable
const int d2 = 6; ///Driver 2 Direction
const int s2 = 7; ///Driver 2 Step
const int e3 = 8; ///Driver 3 Enable
const int d3 = 9; ///Driver 3 Direction
const int s3 = 10; ///Driver 3 Step
const int e4 = 11; ///Driver 4 Enable
const int d4 = 12; //Driver 4 Direction
const int s4 = 13; //Driver 4 Step

//Enable AccelStepper
#include <AccelStepper.h>
AccelStepper stp1(1, s1, d1);
AccelStepper stp2(1, s2, d2);
AccelStepper stp3(1, s3, d3);
AccelStepper stp4(1, s4, d4);

void setup() {
// Set Analog Pin Inputs
pinMode(x1ap, INPUT);
pinMode(y1ap, INPUT);
pinMode(x2ap, INPUT);
//pinMode(y2ap, INPUT);

// Set Pin Outputs
pinMode(e1,OUTPUT);
pinMode(e2,OUTPUT);
pinMode(e3,OUTPUT);
pinMode(e4,OUTPUT);

//Disable Motors
digitalWrite(e1,HIGH);
digitalWrite(e2,HIGH);
digitalWrite(e3,HIGH);
digitalWrite(e4,HIGH);

//SetMaxSpeed
int mspd = 200000;
stp1.setMaxSpeed(mspd);
stp2.setMaxSpeed(mspd);
stp3.setMaxSpeed(mspd);
stp4.setMaxSpeed(mspd);

//Set Acceleration
stp1.setAcceleration(100);
stp2.setAcceleration(100);
stp3.setAcceleration(100);
stp4.setAcceleration(100);

//Serial.begin(9600);
}

void loop() {
  //Read inputs every 1000ms
  if (cnt <0){
  cnt--;
  }
  else{
  cnt = 1000;
  x1 = map(analogRead(x1ap), 0, 1000, -x1m, x1m); //Left Right Vector (500)
  y1 = map(analogRead(y1ap), 0, 1026, -y1m, y1m); //Fwd Rev Vector (513)
  x2 = map(analogRead(x2ap), 0, 1026, -x2m, x2m); //Rotation Vector (513)
  //y2 = map(analogRead(y2ap), 0, 1023, -y2m, y2m); //Not Used

//Serial.print(analogRead(x1ap));
//Serial.print("\t");
//Serial.print(analogRead(y1ap));
//Serial.print("\t");
//Serial.println(analogRead(x2ap));
//
//Serial.print(x1);
//Serial.print("\t");
//Serial.print(y2);
//Serial.print("\t");
//Serial.println(x2);

  
  //zero out if in dead zone
  if ((x1 >-100) && ( x1 <100)){
  x1=0;
  }
  if ((y1 >-100)&&(y1 <100)){
  y1=0;
  }
  if ((x2 >-20)&&(x2 <20)){
  x2=0;
  }
//  if ((y2 >-5)&&(y2 <5)){
//  y2=0;
//  }  
  }
 
//Wheel Calculations
w1 = ( y1 + x1 - (L1 + L2)*x2);
w2 = -( y1 - x1 + (L1 + L2)*x2);
w3 = ( y1 - x1 - (L1 + L2)*x2);
w4 = -( y1 + x1 + (L1 + L2)*x2);

//Serial.print(w1);
//Serial.print("\t");
//Serial.print(w2);
//Serial.print("\t");
//Serial.print(w3);
//Serial.print("\t");
//Serial.println(w4);

if ((w1 >-10) && (w1 <10)){
  digitalWrite(e1,HIGH); 
} 
  else  {
    digitalWrite(e1,LOW);
  }
if ((w2 >-10) && (w2 <10)){
  digitalWrite(e2,HIGH);
} 
  else  {
    digitalWrite(e2,LOW);
  }
if ((w3 >-10) && (w3 <10)){
  digitalWrite(e3,HIGH);
} 
  else  {
    digitalWrite(e3,LOW);
  }
if ((w4 >-10) && (w4 <10)){
  digitalWrite(e4,HIGH);
} 
  else  {
    digitalWrite(e4,LOW);
  }

stp1.setSpeed(w1);
stp2.setSpeed(w2);
stp3.setSpeed(w3);
stp4.setSpeed(w4);

stp1.runSpeed();
stp2.runSpeed(); 
stp3.runSpeed();
stp4.runSpeed();
}


 





