#include <LiquidCrystal.h> // LCD Function
#define triggerPin 8 
#define echoPin 9 //MicroWave Reciever, Transmeter설정

LiquidCrystal LCD(4,6,10,11,12,13); //LCD초기화 핀

int blue = 1;
int green = 2;
int red = 3;

void setup(){
  LCD.begin(16,2);// 16자리 2줄을 사용하도록 초기화
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

  float Duration1 = pulseIn(echoPin,HIGH);
  delay(100); //100밀리초 대기
  digitalWrite(triggerPin,LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin,LOW);
  
  float Duration2 = pulseIn(echoPin,HIGH);
  float velocity = ((float)(Duration2-Duration1)*340/2/10000);
  double Distance_mm = Duration / 5.8;


  if ((Distance_mm <4000) && (Distance_mm >2)){
    Serial.print("Distance = ");
    Serial.print(Distance_mm);
    Serial.println("mm");
    LCD.setCursor(0,0);
    LCD.print("dis : ");
    LCD.print(Distance_mm);
    LCD.setCursor(0,1);
    LCD.print("vel : ");
    LCD.print(abs(velocity));
    delay(500);
    LCD.clear();
    
    if(velocity>=5){     //얼마나 빨라야되는지 몰라서 아무 숫자나 넣었어요            
      analogWrite(red,255);   //빨간불  
      analogWrite(green,0);
      analogWrite(blue,0);
      delay(500);
      LCD.setCursor(0,0);
      LCD.print("velocity : ");
      LCD.print(velocity);
      LCD.setCursor(4,1);
      LCD.print("over speed limit"); 
      for (int position = 0; position < 16; position++) {
      LCD.scrollDisplayLeft(); //경고메시지 움직이면서 속도 출력
      delay(500);
      }
    }
    else if(velocity<5){               
      analogWrite(red,0);
      analogWrite(green,0);
      analogWrite(blue,255);  //파란불   
      delay(500);
      LCD.setCursor(1,0);
      LCD.print("velocity : ");
      LCD.print(velocity);
      LCD.setCursor(4,1);
      LCD.print("OK - under speed limit");
      delay(500);
      LCD.clear();
      }   
   }
  else{
    Serial.println("Error");
  }


delay(500);
LCD.clear();
}
