#include <LiquidCrystal.h> // LCD Function
#define triggerPin 8 
#define echoPin 9 //MicroWave Reciever, Transmeter설정

LiquidCrystal LCD(4,6,10,11,12,13); //LCD초기화 핀

void setup(){
  LCD.begin(16,2);
  pinMode(triggerPin,OUTPUT);
  pinMode(echoPin,INPUT);
  Serial.begin(9600);
  delay(2000);
  Serial.println("Comport Connected...!");
  delay(500);
}

void loop(){
  double Duration;
  digitalWrite(triggerPin,LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin,LOW);

Duration = pulseIn(echoPin,HIGH);

double Distance_mm = Duration / 5.8;
double Distance_inch = Duration /148;


if ((Distance_mm <4000) && (Distance_mm >2)){
  Serial.print("Distance = ");
  Serial.print(Distance_mm);
  Serial.println("mm");
  Serial.print("Distance = ");
  Serial.print(Distance_inch);
  Serial.println(" inch");
  
}
else{
  Serial.println("Error");
  
}


delay(500);

}
