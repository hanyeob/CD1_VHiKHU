#include "Wire.h"
// I2Cdev and ADXL345 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "ADXL345.h"
#include <SD.h>
 
// ADXL345 핀 정의
ADXL345 accel;
int16_t ax, ay, az;

 
// SD-CARD CS 핀 정의
#define SD_CS 4 // SD CARD 의 CS 핀
#define LOGFILE "DATALOG.txt" // 로그 저장할 파일명
 
#define SENSOR A0 // 로그 저장할 아날로그 핀

 
void setup()
{
    Wire.begin();
    Serial.begin(9600);
    while(!Serial){
        ;
    }

    
    Serial.println("Initializing I2C devices...");
    accel.initialize();
    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accel.testConnection() ? "ADXL345 connection successful" : "ADXL345 connection failed");

    delay(500);
    Serial.println("Serial Port Connected..");
    delay(500);
    Serial.println("SD Card Init Start..");
    if(!SD.begin(SD_CS)){
        Serial.println("SD-CARD Initialization failed");
        Serial.println("Exit Program..");
        while(1);
    }
    Serial.println("SD-CARD Initialization done.");
    delay(500);
    Serial.println("Data Logging Strart....");
}
 
void loop()
{
    accel.getAcceleration(&ax, &ay, &az);
    File logFile = SD.open(LOGFILE, FILE_WRITE);

    if(logFile){
        logFile.print("accel:\t");
        logFile.print(ax); logFile.print("\t");
        logFile.print(ay); logFile.print("\t");
        logFile.println(az);
        Serial.print("accel:\t");
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
    delay(500);
}
