#include <TimeAlarms.h>
#include <DS1307RTC.h>
#include <Time.h>
#include <Wire.h>


//
//Define the pins that the LED's are connected to
//
const int leftRB = 3;      //Left Royal Blue LED's connected to this pin
const int leftCW = 5;      //Left CW LED's
const int leftWW = 10;     //Left White LED's 6NW + 4CW
const int leftUV = 4;      //Left UV LED's
const int rightRB = 9;     //Right Royal Warm 
const int rightCW = 8;     //Right CW
const int rightWW = 7;     //Right White
const int rightUV = 6;     //Right UV

//
//Define the output levels for the Grow, Glow and Moon Condition
//
byte RBGlow = 255;  //75
byte CWGlow = 2;  //10
byte WWGlow = 2;  //10
byte UVGlow = 50;  //50

byte RBGrow = 255;
byte CWGrow = 125; //150
byte WWGrow = 100;  //150
byte UVGrow = 225;

byte RBMoon = 3;
byte CWMoon = 0;
byte WWMoon = 0;
byte UVMoon = 0;



//
//Variable containing the output level, 0 is off, 255 is full on
//
byte leftRBlvl = 0;           
byte leftCWlvl = 0;
byte leftWWlvl = 0;
byte leftUVlvl = 0;
byte rightRBlvl = 0;
byte rightCWlvl = 0;
byte rightWWlvl = 0;
byte rightUVlvl = 0;

//
//Variable containing the next output level, 0 is off, 255 is full on
//
byte leftRBnxt = 0;           
byte leftCWnxt = 0;
byte leftWWnxt = 0;
byte leftUVnxt = 0;
byte rightRBnxt = 0;
byte rightCWnxt = 0;
byte rightWWnxt = 0;
byte rightUVnxt = 0;


//
// Duration of the ramping function
//
int rampDuration = 60;
int rampCount = 61;

// Turn on Glow at 9am
byte morningGlowHour = 9;
byte morningGlowMin = 00;

// Turn on Grow at 1:15pm
byte afternoonGrowHour = 12 + 1;
byte afternoonGrowMin = 15;

// Turn on Glow at 4:45pm
byte eveningGlowHour = 12 + 4;
byte eveningGlowMin = 45;

// Turn on moonlights at 9:30pm
byte eveningMoonHour = 12 + 9;
byte eveningMoonMin = 30;

// Turn off lights at 11:00pm
byte eveningOffHour = 12 + 11;
byte eveningOffMin = 00;


void setup() {
  Serial.begin(9600);
  Alarm.delay(200);
  setSyncProvider(RTC.get);
  setSyncInterval(60*30);
  
  //
  //Set the lights when the arduino is initially powered on
  //

  /* this bit is only required if lights go OFF after Midnight
  if ((hour()*100+minute()) < (eveningMoonHour*100+eveningMoonMin)){
    analogWrite(leftRB, RBMoon);
    analogWrite(leftWW, WWMoon);
    analogWrite(leftUV, UVMoon);
    analogWrite(leftCW, CWMoon);
    analogWrite(rightRB, RBMoon);
    analogWrite(rightWW, WWMoon);
    analogWrite(rightUV, UVMoon);
    analogWrite(rightCW, CWMoon);
    leftRBlvl = RBMoon;           
    leftCWlvl = CWMoon;
    leftWWlvl = WWMoon;
    leftUVlvl = UVMoon;
    rightRBlvl = RBMoon;
    rightCWlvl = CWMoon;
    rightWWlvl = WWMoon;
    rightUVlvl = UVMoon;
  }
  */
  
  if ((hour()*100+minute()) >= (morningGlowHour*100+morningGlowMin)){
    analogWrite(leftRB, 0);
    analogWrite(leftWW, 0);
    analogWrite(leftUV, 0);
    analogWrite(leftCW, 0);
    analogWrite(rightRB, 0);
    analogWrite(rightWW, 0);
    analogWrite(rightUV, 0);
    analogWrite(rightCW, 0);
    leftRBlvl = 0;           
    leftCWlvl = 0;
    leftWWlvl = 0;
    leftUVlvl = 0;
    rightRBlvl = 0;
    rightCWlvl = 0;
    rightWWlvl = 0;
    rightUVlvl = 0;
  }
 
  if ((hour()*100+minute()) >= (morningGlowHour*100+morningGlowMin)){
    analogWrite(leftRB, RBGlow);
    analogWrite(leftWW, WWGlow);
    analogWrite(leftUV, UVGlow);
    analogWrite(leftCW, CWGlow);
    analogWrite(rightRB, RBGlow);
    analogWrite(rightWW, WWGlow);
    analogWrite(rightUV, UVGlow);
    analogWrite(rightCW, CWGlow);
    leftRBlvl = RBGlow;           
    leftCWlvl = CWGlow;
    leftWWlvl = WWGlow;
    leftUVlvl = UVGlow;
    rightRBlvl = RBGlow;
    rightCWlvl = CWGlow;
    rightWWlvl = WWGlow;
    rightUVlvl = UVGlow;
  }
  if ((hour()*100+minute()) >= (afternoonGrowHour*100+afternoonGrowMin)){
    analogWrite(leftRB, RBGrow);
    analogWrite(leftWW, WWGrow);
    analogWrite(leftUV, UVGrow);
    analogWrite(leftCW, CWGrow);
    analogWrite(rightRB, RBGrow);
    analogWrite(rightWW, WWGrow);
    analogWrite(rightUV, UVGrow);
    analogWrite(rightCW, CWGrow);
    leftRBlvl = RBGrow;           
    leftCWlvl = CWGrow;
    leftWWlvl = WWGrow;
    leftUVlvl = UVGrow;
    rightRBlvl = RBGrow;
    rightCWlvl = CWGrow;
    rightWWlvl = WWGrow;
    rightUVlvl = UVGrow;
  }
  if ((hour()*100+minute()) >= (eveningGlowHour*100+eveningGlowMin)){
    analogWrite(leftRB, RBGlow);
    analogWrite(leftWW, WWGlow);
    analogWrite(leftUV, UVGlow);
    analogWrite(leftCW, CWGlow);
    analogWrite(rightRB, RBGlow);
    analogWrite(rightWW, WWGlow);
    analogWrite(rightUV, UVGlow);
    analogWrite(rightCW, CWGlow);
    leftRBlvl = RBGlow;           
    leftCWlvl = CWGlow;
    leftWWlvl = WWGlow;
    leftUVlvl = UVGlow;
    rightRBlvl = RBGlow;
    rightCWlvl = CWGlow;
    rightWWlvl = WWGlow;
    rightUVlvl = UVGlow;
  }
  if ((hour()*100+minute()) >= (eveningMoonHour*100+eveningMoonMin)){
    analogWrite(leftRB, RBMoon);
    analogWrite(leftWW, WWMoon);
    analogWrite(leftUV, UVMoon);
    analogWrite(leftCW, CWMoon);
    analogWrite(rightRB, RBMoon);
    analogWrite(rightWW, WWMoon);
    analogWrite(rightUV, UVMoon);
    analogWrite(rightCW, CWMoon);
    leftRBlvl = RBMoon;           
    leftCWlvl = CWMoon;
    leftWWlvl = WWMoon;
    leftUVlvl = UVMoon;
    rightRBlvl = RBMoon;
    rightCWlvl = CWMoon;
    rightWWlvl = WWMoon;
    rightUVlvl = UVMoon;
  }
  
  //Turn the lights on based on alarms
  //Alarm.alarmRepeat(hours,minutes,seconds,function);
  Alarm.alarmRepeat(morningGlowHour,morningGlowMin,00,glowLights);
  Alarm.alarmRepeat(afternoonGrowHour,afternoonGrowMin,00,growLights);
  Alarm.alarmRepeat(eveningGlowHour,eveningGlowMin,00,glowLights);
  Alarm.alarmRepeat(eveningMoonHour,eveningMoonMin,00,moonLights);
  Alarm.alarmRepeat(eveningOffHour,eveningOffMin,00,offLights);
  
  Alarm.timerRepeat(30,lightRamp);
  
}




void loop() {  
 Serial.println("time");
 Alarm.delay(1000);
}

void glowLights(){
  rampCount = 0;
  leftRBnxt = RBGlow;           
  leftCWnxt = CWGlow;
  leftWWnxt = WWGlow;
  leftUVnxt = UVGlow;
  rightRBnxt = RBGlow;
  rightCWnxt = CWGlow;
  rightWWnxt = WWGlow;
  rightUVnxt = UVGlow; 
}

void growLights(){
  rampCount = 0;
  leftRBnxt = RBGrow;           
  leftCWnxt = CWGrow;
  leftWWnxt = WWGrow;
  leftUVnxt = UVGrow;
  rightRBnxt = RBGrow;
  rightCWnxt = CWGrow;
  rightWWnxt = WWGrow;
  rightUVnxt = UVGrow;
}

void offLights(){
  rampCount = 0;
  leftRBnxt = 0;           
  leftCWnxt = 0;
  leftWWnxt = 0;
  leftUVnxt = 0;
  rightRBnxt = 0;
  rightCWnxt = 0;
  rightWWnxt = 0;
  rightUVnxt = 0;
//  was to deal with dimming wrong when lights going down, I think prob was actually a typo in CWlvl = CWnxt
//  analogWrite(rightCW, 0);
//  analogWrite(rightWW, 0);
//  analogWrite(leftCW, 0);
//  analogWrite(leftWW, 0);
//  leftCWlvl = 0;
//  leftWWlvl = 0;
//  rightCWlvl = 0;
//  rightWWlvl = 0;
}

void moonLights(){
  rampCount = 0;
  leftRBnxt = RBMoon;           
  leftCWnxt = CWMoon;
  leftWWnxt = WWMoon;
  leftUVnxt = UVMoon;
  rightRBnxt = RBMoon;
  rightCWnxt = CWMoon;
  rightWWnxt = WWMoon;
  rightUVnxt = UVMoon;
}

void lightRamp(){
//  Serial.print("lightRamp Function, rampCount: ");
//  Serial.println(int(rampCount));
//  Serial.print("rampDuration: ");
//  Serial.println(rampDuration);
  if (rampCount <= rampDuration) {
    analogWrite(leftRB, map(rampCount,0,(rampDuration),leftRBlvl,leftRBnxt));
    analogWrite(leftCW, map(rampCount,0,(rampDuration),leftCWlvl,leftCWnxt));
    analogWrite(leftWW, map(rampCount,0,(rampDuration),leftWWlvl,leftWWnxt));
    analogWrite(leftUV, map(rampCount,0,(rampDuration),leftUVlvl,leftUVnxt));
    analogWrite(rightRB, map(rampCount,0,(rampDuration),rightRBlvl,rightRBnxt));
    analogWrite(rightCW, map(rampCount,0,(rampDuration),rightCWlvl,rightCWnxt));
    analogWrite(rightWW, map(rampCount,0,(rampDuration),rightWWlvl,rightWWnxt));
    analogWrite(rightUV, map(rampCount,0,(rampDuration),rightUVlvl,rightUVnxt)); 
//    Serial.print("rampcount: ");
//    Serial.println(rampCount);
    if (rampCount == rampDuration) {
      leftRBlvl = leftRBnxt;           
      leftCWlvl = leftCWnxt;
      leftWWlvl = leftWWnxt;
      leftUVlvl = leftUVnxt;
      rightRBlvl = rightRBnxt;
      rightCWlvl = rightCWnxt;
      rightWWlvl = rightWWnxt;
      rightUVlvl = rightUVnxt;
    }
    rampCount++;
//    Serial.print("new rampCount: ");
//    Serial.println(int(rampCount));
//    Serial.print("royal blue: ");
//    Serial.println(map(rampCount,0,rampDuration,leftRBlvl,leftRBnxt));
  } 
}
