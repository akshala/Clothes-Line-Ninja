#include <SimpleDHT.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(11,12);
int potentiometer = A5;
int trigger = 5;
int echo = 6;
int in_touch1 = 2;
int in_touch2 = 4;
int state = HIGH;
int value1;
int value2;
int pinDHT11 =7;
String tempCondition;
String humidityCondition;
SimpleDHT11 dht11;
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(potentiometer,INPUT);
  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(in_touch1, INPUT);
  pinMode(in_touch2, INPUT);
  pinMode(3, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(13, OUTPUT);
  //int distance = 0;
}

void loop() {

  byte temperature = 0;
  byte humidity = 0;
  if (dht11.read(pinDHT11, &temperature, &humidity, NULL))
  {
    return;
  }
  if(temperature > 25){
    tempCondition = "Sunny";
  }
  else if(temperature < 15){
    tempCondition = "Cold";
  }
  else{
    tempCondition = "Moderate";
  }
  if(humidity > 70){
    humidityCondition = "Cloudy";
  }
  else if (humidity < 40){
    humidityCondition = "Clear";
  }
  else{
    humidityCondition = "Moderate";
  }
//  mySerial.print((int)temperature);
  mySerial.print(tempCondition + " " + String(temperature));
  mySerial.print(",");
//  mySerial.print((int)humidity);
  mySerial.print(humidityCondition + " " + String(humidity));
  mySerial.print(",");

  int sensor = analogRead(potentiometer);

  if(sensor >= 512 ){
  
    value1 = digitalRead(in_touch1);
    value2 = digitalRead(in_touch2);
    if(value1 == 1){
      digitalWrite(9,HIGH);
      digitalWrite(10,LOW);
      analogWrite(3, 150);
      digitalWrite(8, HIGH);
      digitalWrite(13, LOW);
    }
  
    else if (value1==0 && value2==1){
      digitalWrite(9,LOW);
      digitalWrite(10,HIGH);
      analogWrite(3, 150);
      digitalWrite(8, LOW);
      digitalWrite(13, HIGH);
    }
    else if (value1==0 && value2==0){
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      analogWrite(3, 150);
      digitalWrite(8, LOW);
      digitalWrite(13, LOW);
    }
    delay(1000);
  }
  else{
    int newdistance;
    digitalWrite(trigger,LOW);
    delayMicroseconds(2);
    digitalWrite(trigger,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger,LOW);
    int timetaken = pulseIn(echo,HIGH);
    newdistance = timetaken*0.034/2;
    Serial.println(newdistance);
    if(newdistance > 0 && newdistance < 19){
  
      digitalWrite(9,HIGH);
      digitalWrite(10,LOW);
      analogWrite(3, 150);
      digitalWrite(8, HIGH);
      digitalWrite(13, LOW);
      
    }
    
    else if(newdistance > 19 && newdistance < 41  ){
  
      digitalWrite(9,LOW);
      digitalWrite(10,HIGH);
      analogWrite(3, 150);
      digitalWrite(8, LOW);
      digitalWrite(13, HIGH);
      
    }
    else{
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      analogWrite(3, 150);
      digitalWrite(8, LOW);
      digitalWrite(13, LOW);
    }
  
    delay(500);
  }
}
