/*
속도계 핀
DO - 3

가속도계 핀 
SDA: A4
SCL: A5

SD 핀
CS    4
SCK   13
MOSI  11
MISO   12
*/

#include "Wire.h"
// I2Cdev and ADXL345 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "ADXL345.h",
#include <SD.h>
 
// ADXL345 변수
ADXL345 accel;
int16_t ax, ay, az;

 
// SD-CARD 변수
#define SD_CS 4 // SD CARD 의 CS 핀
#define LOGFILE "vel_acc.csv" // 로그 저장할 파일명


//속도계 변수
# define DIAMETER 64 //(cm)
# define ELEM_LENGTH 25.0 //cm
# define REEDPIN 3
bool lastbool, currbool, error; //1이 떨어져있을 때, 0이 가까이 있을 때 
unsigned long count, ckTime, uckTime, delta; //열릴 때시간, 닫힐 때시간, 
float vel;


unsigned long TIME;


void setup()
{
  Serial.begin(9600);

  TIME = 0;
  
  //속도계 세팅
    pinMode(REEDPIN, INPUT);                  
    lastbool = 0;
    ckTime = 0;

  //가속도계 세팅
    Wire.begin();
    while(!Serial){
        ;
    }


  //속도계 연결 검사
    Serial.println("Testing velocity device connections...");
    Serial.println(digitalRead(REEDPIN) ? "velocity device connection successful" : "velocity device connection failed");

  //가속도계 연결 검사
    Serial.println("Initializing Acc devices...");
    accel.initialize();
    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accel.testConnection() ? "ADXL345 connection successful" : "ADXL345 connection failed");

  //SD 연결 검사
    Serial.println("Serial Port Connected..");
    Serial.println("SD Card Init Start..");
    if(!SD.begin(SD_CS)){
        Serial.println("SD-CARD Initialization failed");
        Serial.println("Exit Program..");
        while(1);
    }
    Serial.println("SD-CARD Initialization done.");

  //파일 생성
    File logFile = SD.open(LOGFILE, FILE_WRITE);
    logFile.println("Time(ms),Vel(km/h), Acc(x), Acc(y), Acc(z)");
    logFile.close();
}


 
void loop()
{
    TIME = millis();
  //속도 측정

    currbool = digitalRead(REEDPIN); // 리드스위치의 상태를 확인합니다.        //검정색 위 1, 하얀색 0
    
    if(currbool == 1 && lastbool == 0){  // 리드 스위치가 열릴 때(닫힘 -> 열림)
      ckTime = millis();  // 시간을 확인해서 저장합니다.
      lastbool = 1;  // lastbool값을 1로 바꿔줍니다.(리드스위치가 열려있는 상태값 저장)
    }
    
    else if(currbool == 0 && lastbool == 1 ){  // 리드 스위치가 닫히고(열림 -> 닫힘), 노이즈 방지 카운트가 5이상일때
      uckTime = millis();  // 시간을 확인해서 저장합니다.
        
      delta = (uckTime - ckTime);
      // 열릴 때 시각과 닫힐 때 시각의 차를 이용하여 바퀴가 한바퀴 돌때 걸린 시간을 계산합니다.
      vel = (ELEM_LENGTH*2/delta)*36.00; // 바퀴가 한바퀴 돌때의 거리와 시간을 가지고 속도를 구해줍니다.(단위는 Km/h입니다.)
      lastbool = 0; 
      count = 0; 
    }
    
    if(currbool == 1){  // 리드 스위치가 열려있으면 카운트를 1씩 증가 시켜 줍니다.
      count++;
      if(count > 60){ // 카운트가 150이 넘어가면(자전거가 멈췄을 때) 속도를 0으로 바꿔줍니다.
        vel = 0;
      }
    }

  //가속도 측정
    accel.getAcceleration(&ax, &ay, &az);
    File logFile = SD.open(LOGFILE, FILE_WRITE);

    if(logFile){
        logFile.print(TIME); logFile.print(",");
        logFile.print(vel); logFile.print(",");
        logFile.print(ax); logFile.print(",");
        logFile.print(ay); logFile.print(",");
        logFile.println(az);
        Serial.print("TIME(ms):\t");
        Serial.print(TIME);
        Serial.print("Velocity(km/h):\t");
        Serial.print(vel); Serial.print("\t");
        Serial.print("Acceleration:\t");
        Serial.print(ax); Serial.print("\t");
        Serial.print(ay); Serial.print("\t");
        Serial.println(az);
        logFile.close();
    }
    else
    {
        Serial.println("error opening datalog file..");
        Serial.println("Exit Program..");
        while(1);
    }
}
