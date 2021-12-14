
  //속도계 변수
  # define LENGTH 25.125 
  # define IRPIN 2
  bool lastbool=0, currbool=0; 
  float count, lastTime = 0, currTime, delta; //열릴 때시간, 닫힐 때시간, 
  float vel = 0;
  
  
  unsigned long currserialTime,lastserialTime=0 ;
 
void setup() {

  Serial.begin(9600);
  
}

void loop()
{        
    //속도 측정
    currbool = digitalRead(IRPIN); // 리드스위치의 상태를 확인합니다.        //검정색 위 1, 하얀색 0
    
    if(currbool == 1 && lastbool == 0){  
      currTime = millis();  
      delta = currTime - lastTime;
  //  Serial.println(delta);
      vel = (LENGTH*36.0/delta); // 마킹의 길이를 시간으로 나누어 속도를 구해줍니다.(단위는 Km/h입니다.)
      currserialTime = millis();
      if ((currserialTime - lastserialTime) > 400){
        Serial.println(vel);
        lastserialTime=currserialTime;
      }
      lastbool = currbool;  
      lastTime = currTime;  
      count = 0;
    }    
    else if(currbool == lastbool){  
      count++;
      if(count > 1000){ 
        vel = 0;
      }
    }
    else { 
      lastbool = currbool;  
      count = 0;
    }
    

//    Serial.println(vel);
}
