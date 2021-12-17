# define DIAMETER 64 //(cm)
# define ELEM_LENGTH 25.0 //cm
# define REEDPIN 3

bool lastbool, currbool, error; //1이 떨어져있을 때, 0이 가까이 있을 때 
unsigned long lasttime, currtime, delta;
double vel;

void setup() {
  pinMode(REEDPIN, INPUT);                  // 디지털 3번핀을 입력모드로 설정
  currbool = 1;
  lasttime = 0;
  Serial.begin(9600);                 // 시리얼 통신을 시작하며, 속도는 9600으로 설정
}
 
 
void loop() {
  error = 0;
  lastbool = currbool;
  currbool = digitalRead(REEDPIN);             // 변수 a를 선언하여 디지털 3번핀의 값을 입력
  if(lastbool && !currbool){              //1에서 0으로 바뀔 때
    currtime = millis();
    delta = currtime - lasttime; 
    lasttime = currtime;
    Serial.println(delta);

    vel = (ELEM_LENGTH/float(delta))*36;      //km/h
    
    Serial.print ("Velocity(km/h): ");
    Serial.println(vel);                  // 변수 a를 시리얼 모니터에 출력
  }
}
