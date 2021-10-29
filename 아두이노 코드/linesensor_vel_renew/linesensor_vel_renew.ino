/*
사용한 센서 
가속도: ADXL345 GY-80 
속도: hw-511 tcrt5000

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
 
// ADXL345 변수
ADXL345 accel;
int16_t ax, ay, az;

 
// SD-CARD 변수
//#include <SD.h>
//#define SD_CS 4 // SD CARD 의 CS 핀
//#define LOGFILE "vel_acc.csv" // 로그 저장할 파일명


//속도계 변수
# define CIRCUMFERENCE 200 // 뒷바퀴의 둘레(cm)
# define WHITE_LENGTH 50.0 // 하얀색 마킹의 길이(cm)
# define WHITE_NO 4 // 요소(하얀색 마킹)의 갯수
# define BLACK_LENGTH 50.0 // 원둘레에서 마킹의 길이를 빼고 마킹갯수로 나눈 값
# define REEDPIN 3
bool lastbool, currbool; //1이 떨어져있을 때, 0이 가까이 있을 때 
unsigned long count, lastTime, currTime, delta; //열릴 때시간, 닫힐 때시간, 
float vel;


unsigned long TIME;


void setup()
{
  Serial.begin(9600);

  TIME = 0;
  
  //속도계 세팅, 이전 현재 모두 1(검정)
    pinMode(REEDPIN, INPUT);                  
    lastbool = 1;
    currbool = 1;
    currTime = 0;

  //가속도계 세팅
    Wire.begin();
//    while(!Serial){
//        ;
//    }
//
//
//  //속도계 연결 검사
//    Serial.println("Testing velocity device connections...");
//    Serial.println(digitalRead(REEDPIN) ? "velocity device connection successful" : "velocity device connection failed");
//
//  //가속도계 연결 검사
//    Serial.println("Initializing Acc devices...");
//    // verify connection
//    Serial.println("Testing device connections...");
//    Serial.println(accel.testConnection() ? "ADXL345 connection successful" : "ADXL345 connection failed");
//
//  //SD 연결 검사
//    Serial.println("Serial Port Connected..");
//    Serial.println("SD Card Init Start..");
//    if(!SD.begin(SD_CS)){
//        Serial.println("SD-CARD Initialization failed");
//        Serial.println("Exit Program..");
//        while(1);
//    }
//    Serial.println("SD-CARD Initialization done.");

  //파일 생성
//    File logFile = SD.open(LOGFILE, FILE_WRITE);
//    logFile.println("Time(ms),Vel(km/h), Acc(x), Acc(y), Acc(z)");
//    logFile.close();


    //SENSOR ACTIVATE TO USE SERIAL MECRO (시리얼 매크로 사용시 센서 활성화 코드) 
    accel.initialize();
    accel.testConnection();
//    SD.begin(SD_CS);
    Serial.println("CLEARDATA");
    Serial.println("LABEL,Time(ms),Vel(km/h), Acc(x), Acc(y), Acc(z)");
}


 
void loop()
{    
    //시간 측정 
    TIME = millis();
    
    //속도 측정
    currbool = digitalRead(REEDPIN); // 리드스위치의 상태를 확인합니다.        //검정색 위 1, 하얀색 0
    
    if(currbool == 1 && lastbool == 0){  // 하얀색 마킹에서 검정색으로 바뀌었을 때 (B -> W)
      currTime = millis();  // 시간을 확인해서 저장합니다.
      delta = currTime - lastTime;
  //  Serial.println(delta);
      vel = (WHITE_LENGTH*36.0/delta); // 마킹의 길이를 시간으로 나누어 속도를 구해줍니다.(단위는 Km/h입니다.)
      lastbool = currbool;  // lastbool값을 currbool로 바꿔줍니다.
      lastTime = currTime;  //
      count = 0;
    }

    else if(currbool == 0 && lastbool == 1 ){  // 검정색에서 하얀색으로 바뀌었을 때 (W -> B)
      currTime = millis();  // 시간을 확인해서 저장합니다.
      delta = currTime - lastTime;
  //  Serial.println(delta);
      vel = (BLACK_LENGTH*36.0/delta); // 검은색의 길이를 시간으로 나누어 속도를 구해줍니다.(단위는 Km/h입니다.)
      lastbool = currbool;  // lastbool값을 currbool로 바꿔줍니다.
      lastTime = currTime;  //
      count = 0;
    }
    
    if(currbool == lastbool){  // 센서의 변화가 없으면
      count++;
      if(count > 60){ // 카운트가 60이 넘어가면(자전거가 멈췄을 때) 속도를 0으로 바꿔줍니다.
        vel = 0;
      }
    }

  //가속도 측정
    accel.getAcceleration(&ax, &ay, &az);
//    File logFile = SD.open(LOGFILE, FILE_WRITE);

//    if(logFile){
//        logFile.print(TIME); logFile.print(",");
//        logFile.print(vel); logFile.print(",");
//        logFile.print(ax); logFile.print(",");
//        logFile.print(ay); logFile.print(",");
//        logFile.println(az);
//        
////        Serial.print("TIME(ms):\t");
////        Serial.print(TIME);
////        Serial.print("Velocity(km/h):\t");
////        Serial.print(vel); Serial.print("\t");
////        Serial.print("Acceleration:\t");
////        Serial.print(ax); Serial.print("\t");
////        Serial.print(ay); Serial.print("\t");
////        Serial.println(az);
//
////        //MACRO PRINT CODE
        Serial.print("DATA,");
        Serial.print(TIME); Serial.print(",");
        Serial.print(delta); Serial.print(",");
        Serial.print(vel); Serial.print(",");
        Serial.print(ax); Serial.print(",");
        Serial.print(ay); Serial.print(",");
        Serial.println(az);
//
//        logFile.close();
//    }
//    else
//    {
//        Serial.println("error opening datalog file..");
//        Serial.println("Exit Program..");
//        while(1);
//    }
}
