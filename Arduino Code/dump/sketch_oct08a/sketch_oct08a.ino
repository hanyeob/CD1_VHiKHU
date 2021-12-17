int trig = 2;
int echo = 3;
void setup () {
  Serial.begin(9600);
  pinMode(trig,OUTPUT);
  pinMode(echo, INPUT);
}
void loop() {
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  int distance = pulseIn(echo,HIGH)*340 / 2/10000;
  Serial.print(distance);
  Serial.println("cm");
  delay(100);
}
