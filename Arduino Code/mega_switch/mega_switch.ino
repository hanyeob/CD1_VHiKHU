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
CS: 53
SCK: 52
MOSI: 51
MISO: 50
*/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
 
void displaySensorDetails(void)
{
  sensor_t sensor;
  accel.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print ("Sensor: "); Serial.println(sensor.name);
  Serial.print ("Driver Ver: "); Serial.println(sensor.version);
  Serial.print ("Unique ID: "); Serial.println(sensor.sensor_id);
  Serial.print ("Max Value: "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
  Serial.print ("Min Value: "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
  Serial.print ("Resolution: "); Serial.print(sensor.resolution); Serial.println(" m/s^2"); 
  Serial.println("------------------------------------");
  Serial.println("");
}
 
void displayDataRate(void)
{
  Serial.print ("Data Rate: ");
  switch(accel.getDataRate())
  {
    case ADXL345_DATARATE_3200_HZ:
    Serial.print ("3200 "); 
    break;
    case ADXL345_DATARATE_1600_HZ:
    Serial.print ("1600 "); 
    break;
    case ADXL345_DATARATE_800_HZ:
    Serial.print ("800 "); 
    break;
    case ADXL345_DATARATE_400_HZ:
    Serial.print ("400 "); 
    break;
    case ADXL345_DATARATE_200_HZ:
    Serial.print ("200 "); 
    break;
    case ADXL345_DATARATE_100_HZ:
    Serial.print ("100 "); 
    break;
    case ADXL345_DATARATE_50_HZ:
    Serial.print ("50 "); 
    break;
    case ADXL345_DATARATE_25_HZ:
    Serial.print ("25 "); 
    break;
    case ADXL345_DATARATE_12_5_HZ:
    Serial.print ("12.5 "); 
    break;
    case ADXL345_DATARATE_6_25HZ:
    Serial.print ("6.25 "); 
    break;
    case ADXL345_DATARATE_3_13_HZ:
    Serial.print ("3.13 "); 
    break;
    case ADXL345_DATARATE_1_56_HZ:
    Serial.print ("1.56 "); 
    break;
    case ADXL345_DATARATE_0_78_HZ:
    Serial.print ("0.78 "); 
    break;
    case ADXL345_DATARATE_0_39_HZ:
    Serial.print ("0.39 "); 
    break;
    case ADXL345_DATARATE_0_20_HZ:
    Serial.print ("0.20 "); 
    break;
    case ADXL345_DATARATE_0_10_HZ:
    Serial.print ("0.10 "); 
    break;
    default:
    Serial.print ("???? "); 
    break;
  } 
  Serial.println(" Hz"); 
}
 
void displayRange(void)
{
  Serial.print ("Range: +/- ");
  switch(accel.getRange())
  {
    case ADXL345_RANGE_16_G:
    Serial.print ("16 "); 
    break;
    case ADXL345_RANGE_8_G:
    Serial.print ("8 "); 
    break;
    case ADXL345_RANGE_4_G:
    Serial.print ("4 "); 
    break;
    case ADXL345_RANGE_2_G:
    Serial.print ("2 "); 
    break;
    default:
    Serial.print ("?? "); 
    break;
  } 
  Serial.println(" g"); 
}

//속도계 변수
# define CIRCUMFERENCE 200.0 // 뒷바퀴의 둘레(cm)
# define WHITE_LENGTH 50.0 // 하얀색 마킹의 길이(cm)
# define WHITE_NO 4 // 요소(하얀색 마킹)의 갯수
# define BLACK_LENGTH 50.0 // 원둘레에서 마킹의 길이를 빼고 마킹갯수로 나눈 값
# define REEDPIN 3
bool lastbool, currbool; //1이 떨어져있을 때, 0이 가까이 있을 때 
unsigned long TIME, count, lastTime, currTime, delta; //열릴 때시간, 닫힐 때시간, 
float vel;

/*
// SD-CARD 변수
#include <SD.h>
#define SD_CS 53 // SD CARD 의 CS 핀
char FILE_NAME[10] = {'d','a','t','a','A','.','t','x','t','\0'};
char FILE_NO = 'A';
bool FILE_CHECK = 1;
*/

// 스위치 핀
#define SWITCH_PIN 7
#define LED_PIN 13
bool switchbool, ledbool;


void setup(void) 
{
  Serial.begin(115200);
  Serial.println("===========================Serial Start===========================");

/*
//SD 연결 검사
  Serial.println("Serial Port Connected..");
  Serial.println("SD Card Init Start..");
  if(!SD.begin(SD_CS)){
      Serial.println("SD-CARD Initialization failed");
      Serial.println("Exit Program..");
      while(1);
  }
  Serial.println(FILE_NAME);
  Serial.println(FILE_NO);
  while(FILE_CHECK){
    if (FILE_NO > 90){
      while(1);
    }
    else if (SD.exists(FILE_NAME)) {
      FILE_NO += 1;
      FILE_NAME[4] = FILE_NO;
    }
    else {
      File logFile = SD.open(FILE_NAME, FILE_WRITE);
      if(!logFile){        Serial.println("NOPEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE");        }
      logFile.println("Time(ms),Vel(km/h), Acc(x), Acc(y), Acc(z)");
      logFile.close();
      FILE_CHECK = 0;
    }
  }
  Serial.println("SD-CARD Initialization done.");
*/

  
  Serial.println("Accelerometer Test"); Serial.println("");
   
  /* Initialise the sensor */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  
    pinMode(REEDPIN, INPUT);                  
    lastbool = 1;
    currbool = 1;
    currTime = 0;
  
    Serial.println("\t Time(ms)\t Vel(km/h)\t Accx(m/s^2)\t Accy(m/s^2)\t Accz(m/s^2)");
  }
   
  /* Set the range to whatever is appropriate for your project */
  // accel.setRange(ADXL345_RANGE_16_G);
   accel.setRange(ADXL345_RANGE_8_G);
  // accel.setRange(ADXL345_RANGE_4_G);
  // accel.setRange(ADXL345_RANGE_2_G);
  
  /* Set the range to whatever is appropriate for your project */
  //accel.setDataRate(ADXL345_DATARATE_3200_HZ);
  //accel.setDataRate(ADXL345_DATARATE_1600_HZ);
  accel.setDataRate(ADXL345_DATARATE_800_HZ);
  //accel.setDataRate(ADXL345_DATARATE_400_HZ);
  //accel.setDataRate(ADXL345_DATARATE_200_HZ);
  //accel.setDataRate(ADXL345_DATARATE_100_HZ);
  //accel.setDataRate(ADXL345_DATARATE_50_HZ);
  //accel.setDataRate(ADXL345_DATARATE_25_HZ);
   
  /* Display some basic information on this sensor */
  displaySensorDetails();
   
  /* Display additional settings (outside the scope of sensor_t) */
  displayDataRate();
  displayRange();
  Serial.println("");

  
  pinMode(LED_PIN, OUTPUT);          // LED_PIN번 디지털 핀을 출력 모드로 설정
  pinMode(SWITCH_PIN, INPUT);            // SWITCH_PIN번 디지털 핀을 입력 모드로 설정
}



 
void loop(void) 
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
  
  else{  // 센서의 변화가 없으면
    count++;
    if(count > 300){ // 카운트가 60이 넘어가면(자전거가 멈췄을 때) 속도를 0으로 바꿔줍니다.
      vel = 0;
    }
  }
  
    
  /* Get a new sensor event */ 
  sensors_event_t event; 
  accel.getEvent(&event);

  switchbool = digitalRead(SWITCH_PIN);
  if(switchbool){
    digitalWrite(LED_PIN,HIGH);
  }
  else{
    digitalWrite(LED_PIN,LOW);
  //  /* Display the results (acceleration is measured in m/s^2) */
    Serial.print(TIME); Serial.print("\t");
    Serial.print(delta); Serial.print("\t");
    Serial.print(vel); Serial.print("\t");
    Serial.print(event.acceleration.x);Serial.print("\t");
    Serial.print(event.acceleration.y);Serial.print("\t");
    Serial.print(event.acceleration.z); Serial.print("\n");

/*
//  File logFile = SD.open(FILE_NAME, FILE_WRITE);
//  logFile.print(TIME); logFile.print(",");
//  logFile.print(delta); logFile.print(",");
//  logFile.print(vel); logFile.print(",");
//  logFile.print(event.acceleration.x);logFile.print(",");
//  logFile.print(event.acceleration.y);logFile.print(",");
//  logFile.print(event.acceleration.z); logFile.print("\n");
//  logFile.close();
*/
  }
}
