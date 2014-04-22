//#include <LiquidCrystal.h>
 
#include <NewPing.h>

#define TRIGGER_PIN  3
#define ECHO_PIN     2
#define MAX_DISTANCE 200

//for motor
#define LeftDirectionP	12
#define LeftBrakeP	9
#define LeftSpeedP	3

#define RightDirectionP	13
#define RightBrakeP	8
#define RightSpeedP	11

#define Speed  225
//distance sensor
NewPing DistanceSensor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

//LiquidCrystal lcd(10,11,5,4,3,2);

//control vars
char DirFromSerial = 'S'; //S = stop, R = right, L = left


void setup ()
{
  //bluetooth needs 57600, PC normally is 9600
  Serial.begin(57600);
 // lcd.begin(16,2);
 // lcd.print("Hello World!");
  
  //Motor stuff
  //right
  pinMode(LeftDirectionP, OUTPUT);
  pinMode(LeftBrakeP, OUTPUT);
  //left
  pinMode(RightBrakeP, OUTPUT);
  pinMode(RightDirectionP, OUTPUT);
  
  DirFromSerial = 'T';
}

void loop ()
{
  unsigned int cm = DistanceSensor.ping_cm();
  char TempChr = 'A';
  
  Serial.print("Distance: ");
  Serial.print(cm);
  Serial.println("cm");
  //Serial.print("Direction [F/S/R]: ");
  TempChr = Serial.read();
  if (TempChr == 'S' || TempChr == 'R' || TempChr == 'L' || TempChr == 'T')
  {
    DirFromSerial = TempChr;
  }
  //Serial.print("F / B:");
  //TempChr = Serial.read();
  if(TempChr == 'B' || TempChr == 'F')
  {
    BackForward = TempChr;
  }
  
 // lcd.clear();
 // lcd.print("Dist: " + String(cm) + "cm");
  
  //MOTOR
  
  
  
  if(BackForward == 'F')
  {
     digitalWrite(LeftDirectionP, t); //Establishes forward direction of Channel A
     digitalWrite(RightDirectionP, HIGH); //Establishes forward direction of Channel B
  }
  else
  {
     digitalWrite(LeftDirectionP, LOW); 
     digitalWrite(RightDirectionP, LOW);
  }

  if(DirFromSerial == 'S' || DirFromSerial == 'L')
  {
   
    digitalWrite(LeftBrakeP, LOW);   //Disengage the Brake for Channel A
    analogWrite(LeftSpeedP, Speed);   //Spins the motor on Channel A at full speed
  }
  
  if(DirFromSerial == 'S' || DirFromSerial == 'R')
  {
    
    
    digitalWrite(RightBrakeP, LOW);   //Disengage the Brake for Channel B
    analogWrite(RightSpeedP, Speed);   //Spins the motor on Channel B at full speed
  }
  
  if(DirFromSerial == 'R' || DirFromSerial == 'T')
  {
    digitalWrite(LeftBrakeP, HIGH);
  }
  
  if(DirFromSerial == 'T' || DirFromSerial == 'L')
  {
    //stop
    digitalWrite(RightBrakeP, HIGH);
    
  }
  
  
  //backward @ half speed
 // digitalWrite(12, LOW); //Establishes backward direction of Channel A
  //digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  //analogWrite(3, 123);   //Spins the motor on Channel A at half speed

  
  
  delay(500);
}
