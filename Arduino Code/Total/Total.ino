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

// I2Cdev and ADXL345 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include <Wire.h>
#include <ADXL345.h>
#include <SD.h>
 
// ADXL345 변수
ADXL345 accel(ADXL345_ALT);
int16_t ax, ay, az;

 
// SD-CARD 변수
#define SD_CS 4 // SD CARD 의 CS 핀
#define LOGFILE "vel_acc.csv" // 로그 저장할 파일명


//속도계 변수
# define ROUND 201 //(cm)
# define ELEM_LENGTH 25.125 //cm
# define REEDPIN 3
bool lastbool, currbool, error; //1이 떨어져있을 때, 0이 가까이 있을 때 
unsigned long lasttime, currtime, delta;
float vel;



void setup()
{
    Wire.begin();
    Serial.begin(9600);
  
  //속도계 연결 검사
    Serial.println("Testing velocity device connections...");
    Serial.println(digitalRead(REEDPIN) ? "velocity device connection successful" : "velocity device connection failed");

  //가속도계 연결 검사
    Serial.println("Initializing Acc devices...");
    byte deviceID = accel.readDeviceID();
    if (deviceID != 0) {
      Serial.print("0x");
      Serial.print(deviceID, HEX);
      Serial.println("");
    } else {
      Serial.println("read device id: failed");
      while(1) {
        delay(100);
      }
    }
    
  //SD 연결 검사
    Serial.println("Serial Port Connected..");
    Serial.println("SD Card Init Start..");
    if(!SD.begin(SD_CS)){
        Serial.println("SD-CARD Initialization failed");
        Serial.println("Exit Program..");
        while(1);
    }
    Serial.println("SD-CARD Initialization done.");
    

  //속도계 세팅
    pinMode(REEDPIN, INPUT);     // 디지털 3번핀을 입력모드로 설정
    currbool = 1;
    lasttime = 0;

  //가속도계 세팅
    // Data Rate
    // - ADXL345_RATE_3200HZ: 3200 Hz
    // - ADXL345_RATE_1600HZ: 1600 Hz
    // - ADXL345_RATE_800HZ:  800 Hz
    // - ADXL345_RATE_400HZ:  400 Hz
    // - ADXL345_RATE_200HZ:  200 Hz
    // - ADXL345_RATE_100HZ:  100 Hz
    // - ADXL345_RATE_50HZ:   50 Hz
    // - ADXL345_RATE_25HZ:   25 Hz
    // - ...
    if (!accel.writeRate(ADXL345_RATE_800HZ)) {
      Serial.println("write rate: failed");
      while(1) {
        delay(100);
      }
    }
  
    // Data Range
    // - ADXL345_RANGE_2G: +-2 g
    // - ADXL345_RANGE_4G: +-4 g
    // - ADXL345_RANGE_8G: +-8 g
    // - ADXL345_RANGE_16G: +-16 g
    if (!accel.writeRange(ADXL345_RANGE_16G)) {
      Serial.println("write range: failed");
      while(1) {
        delay(100);
      }
    }
  
    if (!accel.start()) {
      Serial.println("start: failed");
      while(1) {
        delay(100);
      }
    }


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
    currbool = digitalRead(REEDPIN);             // 변수 a를 선언하여 디지털 3번핀의 값을 입력
    if(lastbool && !currbool){              //1에서 0으로 바뀔 때
      currtime = millis();
      delta = currtime - lasttime; 
      lasttime = currtime;
      
      vel = (ELEM_LENGTH/float(delta))*36;      //km/h
    }

  //가속도 측정
    //accel.getAcceleration(&ax, &ay, &az);
    accel.update();
    File logFile = SD.open(LOGFILE, FILE_WRITE);

    if(logFile){
        logFile.print(vel); logFile.print(",");
        logFile.print(accel.getX()); logFile.print(",");
        logFile.print(accel.getY()); logFile.print(",");
        logFile.println(accel.getZ());
        Serial.print("Velocity(km/h):\t");
        Serial.print(vel); Serial.print("\t");
        Serial.print("Acceleration:\t");
        Serial.print(accel.getX()); Serial.print("\t");
        Serial.print(accel.getY()); Serial.print("\t");
        Serial.println(accel.getZ());
        logFile.close();
    }
    else
    {
        Serial.println("error opening datalog file..");
        Serial.println("Exit Program..");
        while(1);
    }
}
