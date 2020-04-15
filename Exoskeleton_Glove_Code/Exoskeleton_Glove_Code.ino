/*******************************************************************************
* Copyright 2016 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/* Authors: Taehun Lim (Darby) */

#include <DynamixelWorkbench.h>

#if defined(__OPENCM904__)
  #define DEVICE_NAME "1" //Dynamixel on Serial3(USART3)  <-OpenCM 485EXP
#elif defined(__OPENCR__)
  #define DEVICE_NAME ""
#endif   

#define BAUDRATE  1000000
#define DXL_ID    1
#define ledPin 16
int state = 0;
int motorpos=0;
int jamming = 10;
int chamber = 11;
int abduction = 12;
int solenoidjamming = 13;
int solenoidchamber = 14;
int solenoidabduction = 15;


DynamixelWorkbench dxl_wb;

void setup() 
{
  Serial.begin(115200);
  Serial2.begin(115200);
  //while(!Serial); // Wait for Opening Serial Monitor
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  pinMode(chamber, OUTPUT);
  pinMode(abduction, OUTPUT);
  pinMode(jamming, OUTPUT);
  pinMode(solenoidchamber, OUTPUT);
  pinMode(solenoidabduction, OUTPUT);
  pinMode(solenoidjamming, OUTPUT);
  const char *log;
  bool result = false;
  bool result2 = false;
  bool result3 = false;
  bool result4 = false;
  bool result5 = false;

  uint8_t dxl_id = DXL_ID;
  uint8_t dx2_id = 2;
  uint8_t dx3_id = 3;
  uint8_t dx4_id = 4;
  uint8_t dx5_id = 5;
  
  uint16_t model_number = 0;

  result = dxl_wb.init(DEVICE_NAME, BAUDRATE, &log);
  if (result == false)
  {
    Serial.println(log);
    Serial.println("Failed to init");
  }
  else
  {
    Serial.print("Succeeded to init : ");
    Serial.println(BAUDRATE);  
  }

  result = dxl_wb.ping(dxl_id, &model_number, &log);
  result2 = dxl_wb.ping(dx2_id, &model_number, &log);
  result3 = dxl_wb.ping(dx3_id, &model_number, &log);
  result4 = dxl_wb.ping(dx4_id, &model_number, &log);
  result5 = dxl_wb.ping(dx5_id, &model_number, &log);
  if (result == false && result2 == false && result3 == false && result4 == false && result5 == false)
  {
    Serial.println(log);
    Serial.println("Failed to ping");
  }
  else
  {
    Serial.println("Succeeded to ping");
    Serial.print("id : ");
    Serial.print(dxl_id);
    Serial.print(" model_number : ");
    Serial.println(model_number);
  }

  result = dxl_wb.currentBasedPositionMode(dxl_id, 30, &log);
  result2 = dxl_wb.currentBasedPositionMode(dx2_id, 150, &log);
  result3 = dxl_wb.currentBasedPositionMode(dx3_id, 30, &log);
  result4 = dxl_wb.currentBasedPositionMode(dx4_id, 30, &log);
  result5 = dxl_wb.currentBasedPositionMode(dx5_id, 30, &log);
  if (result == false && result2 == false && result3 == false && result4 == false && result5 == false)
  {
    Serial.println(log);
    Serial.println("Failed to change current based position mode");
  }
  else
  {
    Serial.println("Succeed to change current based position mode");
    Serial.println("Dynamixel is moving...");

    for (int count = 0; count < 1; count++) //Motor Calibration
    {
      dxl_wb.goalPosition(dxl_id, (int32_t)0);
      dxl_wb.goalPosition(dx2_id, (int32_t)0);
      dxl_wb.goalPosition(dx3_id, (int32_t)0);
      dxl_wb.goalPosition(dx4_id, (int32_t)0);
      dxl_wb.goalPosition(dx5_id, (int32_t)0);
      delay(1500);

    }
  }
}

void loop() 
{
  //Serial.println("INICIO");
 if(Serial2.available() > 0){ // Checks whether data is comming from the serial port
    state = Serial2.read(); // Reads the data from the serial port
    Serial.println(state);
    state=state-48;
    int flex = 0;
 
 if (state == 1) { //Full Grasp
  dxl_wb.goalPosition(1, (int32_t)8000);
  dxl_wb.goalPosition(2, (int32_t)8000);
  dxl_wb.goalPosition(3, (int32_t)8000);
  dxl_wb.goalPosition(4, (int32_t)8000);
  dxl_wb.goalPosition(5, (int32_t)8000);
  delay(1500);
  state = 0;
 }
 else if (state == 2) { // Tripod Grasp
  dxl_wb.goalPosition(1, (int32_t)8000);
  dxl_wb.goalPosition(2, (int32_t)8000);
  dxl_wb.goalPosition(3, (int32_t)8000);
  delay(1000);
  state = 0;}  else if (state == 3) { //Pinch Grasp

  dxl_wb.goalPosition(2, (int32_t)12000);
  dxl_wb.goalPosition(3, (int32_t)8000);
  dxl_wb.goalPosition(5, (int32_t)8000);
  delay(1000);
  state = 0;} else if (state == 4) { //Abduction Chambers
  delay(500);
  for (int i = 0; i <= 255; i++) {
       analogWrite(abduction, i);
       delay(4);
  } 
  delay(200);
  state = 0;} else if (state == 5) {//Jamming
  delay(500);
  for (int i = 0; i <= 255; i++) {
       analogWrite(jamming, i);
       delay(4);
  } 
  delay(200);
  state = 0;} else if (state == 6) {//Chamber
  delay(500);
  for (int i = 0; i <= 255; i++) {
       analogWrite(chamber, i);
       delay(4);
  } 
  delay(200);
  state = 0;} else if (state == 7) {//Return to rest
  dxl_wb.goalPosition(1, (int32_t)0);
  dxl_wb.goalPosition(2, (int32_t)0);
  dxl_wb.goalPosition(3, (int32_t)0);
  dxl_wb.goalPosition(4, (int32_t)0);
  dxl_wb.goalPosition(5, (int32_t)0);
  delay(500);
           analogWrite(abduction, 0);
           delay(20);
           analogWrite(jamming, 0);
           delay(20);
           analogWrite(chamber, 0);
           delay(20);
           analogWrite(solenoidabduction, 255);
           delay(20);
           analogWrite(solenoidjamming, 255);
           delay(20);
           analogWrite(solenoidchamber, 255);
           delay(1000);
           analogWrite(solenoidabduction, 0);
           delay(20);
           analogWrite(solenoidjamming, 0);
           delay(20);
           analogWrite(solenoidchamber, 0);
  delay(50);
  state = 0;} else if (state == 8) { //flex sensor
    while (flex<5){
    int sensorValue = analogRead(A0);
    delay(2);
    Serial.println(sensorValue);
    if (sensorValue <=5){
    flex = flex + 1;
    }
    delay(10);
    }
        for (int i = 0; i <= 255; i++) {
       analogWrite(jamming, i);
       delay(4);
        }
  } else if (state == 9) { //Key Grasp

  dxl_wb.goalPosition(2, (int32_t)12000);
  dxl_wb.goalPosition(3, (int32_t)8000);
  delay(1000);}

  else if (state == 10) { //Thumb Abdcution
  dxl_wb.goalPosition(5, (int32_t)8000);
  delay(1000);}

  }
 }
 
