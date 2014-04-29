    /*

    Copyright (C) 2014, Alexis Enston

    This file is part of HALbot

    HALbot is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    HALbot is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with HALbot.  If not, see <http://www.gnu.org/licenses/>.*/

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

//#define Speed  225
int Speed = 250;

//distance sensor
NewPing DistanceSensor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

//LiquidCrystal lcd(10,11,5,4,3,2);

//control vars
//char DirFromSerial = 'S'; //S = stop, R = right, L = left

void WheelControl(int DirectionP, int BrakeP, int WhatToDo)
{
    switch (WhatToDo) {
    case 1: //forward
        digitalWrite(DirectionP, HIGH); 
        digitalWrite(BrakeP, LOW);
        break;
    case 2: //backwards
        digitalWrite(DirectionP, LOW); 
        digitalWrite(BrakeP, LOW);
        break; 
    case 3: //stop
        digitalWrite(BrakeP, HIGH);
        break;
  }
}

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
  
 // DirFromSerial = 'T';
 //STOP MOVING before ive sent you commands
  WheelControl(LeftDirectionP, LeftBrakeP, 3);
  WheelControl(RightDirectionP, RightBrakeP, 3);
 
}



void loop ()
{
  unsigned int cm = DistanceSensor.ping_cm();
  char TempChr = '#';
  char BackForward = '#';
  
  //DISTANCE SENSOR
  Serial.print("DIST:");
  Serial.print(cm);
  //ACCELEROMETER
  Serial.print(",X:");
  Serial.print(analogRead(3));
  Serial.print(",Y:");
  Serial.print(analogRead(3));
  Serial.print(",Z:");
  Serial.println(analogRead(3));
  
  //Serial.println("cm");
  //Serial.print("Direction [F/S/R]: ");
  TempChr = Serial.read();
  
  
 // lcd.clear();
 // lcd.print("Dist: " + String(cm) + "cm");
  
  //MOTOR
  
  int Left = 0; //1 BACK, 2 FORWARD, 3 break, 0 no change
  int Right = 0;
  
  switch (TempChr){
    case 'W':
      Left = 2;
      Right = 2;
      break;
    case 'S':
      Left = 1;
      Right = 1;
      break;
    case 'A':
      Left = 2;
      Right = 1;
      break;
    case 'D':
      Left = 1;
      Right = 2;
      break;
    case 'X':
      Left = 3;
      Right = 3;
      break;
    case '1':
      Speed = 100;
      break;
    case '2':
      Speed = 150;
      break;
    case '3':
      Speed = 200;
      break;
    case '4':
      Speed = 250;
      break;
  }
  
  WheelControl(LeftDirectionP, LeftBrakeP, Left);
  WheelControl(RightDirectionP, RightBrakeP, Right);
  
  analogWrite(LeftSpeedP, Speed);
  analogWrite(RightSpeedP, Speed);
    
 /* switch (Left) {
    case 1: //forward
        digitalWrite(LeftDirectionP, HIGH); 
        digitalWrite(LeftBrakeP, LOW);
        break;
    case 2: //backwards
        digitalWrite(LeftDirectionP, LOW); 
        digitalWrite(LeftBrakeP, LOW);
        break; 
    case 3: //stop
        digitalWrite(LeftBrakeP, HIGH);
        break;
  }*/

  
  
  
  
 /* if(BackForward == 'F')
  {
     digitalWrite(LeftDirectionP, HIGH); //Establishes forward direction of Channel A
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
    
  }*/
  
  
  //backward @ half speed
 // digitalWrite(12, LOW); //Establishes backward direction of Channel A
  //digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  //analogWrite(3, 123);   //Spins the motor on Channel A at half speed

  
  
  delay(500);
}
