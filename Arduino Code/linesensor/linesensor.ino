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
#include "ADXL345.h"
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
unsigned long lasttime, currtime, delta;
float vel;



void setup()
{
  Serial.begin(9600);

  //속도계 세팅
    pinMode(REEDPIN, INPUT);                  
    currbool = 1;
    lasttime = 0;

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
    logFile.println("Vel(km/h), Acc(x), Acc(y), Acc(z)");
    logFile.close();
}


 
void loop()
{
  //속도 측정
    error = 0;
    lastbool = currbool;
    currbool = digitalRead(REEDPIN);        //검정색 위 1, 하얀색 0
    Serial.println(currbool);       
    if(lastbool && !currbool){              //이전상태가 1이고 현재상태가 0이라면(자석이 없어지) 
      currtime = millis();
      delta = currtime - lasttime; 
      lasttime = currtime;
      
      vel = (ELEM_LENGTH*2/delta)*36.00;      //km/h
    }

  //가속도 측정
    accel.getAcceleration(&ax, &ay, &az);
    File logFile = SD.open(LOGFILE, FILE_WRITE);

    if(logFile){
        logFile.print(vel); logFile.print(",");
        logFile.print(ax); logFile.print(",");
        logFile.print(ay); logFile.print(",");
        logFile.println(az);
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
