#include <LiquidCrystal.h> // LCD Function
#define triggerPin 8 
#define echoPin 9 //MicroWave Reciever, Transmeter설정

const int alcohol_sensor = A5;
const int GSR = A0;
float sensorValue = 0; // 센서가 측정한 날것의 전기전도도 값

LiquidCrystal LCD(4,6,10,11,12,13); //LCD초기화 핀, (RS,E,DB4,DB5,DB6,DB7)

void setup(){
  LCD.begin(16,2); // 16자리 2줄 사용하도록 초기화
  pinMode(triggerPin,OUTPUT);
  pinMode(echoPin,INPUT);
  Serial.begin(9600);
  delay(2000);
  Serial.println("Comport Connected...!");
  delay(500);
}

void loop(){
  static int step = 1;
  // 경찰차 빨강파랑 비상등 구현 필요

  static float standard = 0; // 거짓말 탐지 시, 5초 동안 측정값들의 평균값으로 기준이 됨
  static float total = 0; // standard 값을 구하기 위한 총합
  static int cycle = 1; // 거짓말 탐지 시, 몇번째 주기인지를 세기 위한 변수
  // 0.5초에 힌번씩 센서값을 측정할 것이므로, cycle = 11일때부터 거짓말 탐지를 시작한다.
  // 10초간 탐지한다. 

  static int crime = 0; // 마지막에 형량을 보여주는 값이다.

  if(step == 1){ // step 1 : 과속 측정 시작
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
    float Distance_mm = Duration1 / 5.8;
    if ((Distance_mm <4000) && (Distance_mm >2)){
      LCD.setCursor(0,0);
      String Distance = String(Distance_mm);
      String Vel = String(abs(velocity));
      LCD.print("dis:"+Distance+"mm");
      LCD.setCursor(0,1);
      LCD.print("vel :" +Vel+"cm/s");

      if(abs(velocity) > 5){ // 과속의 기준이 5
        LCD.setCursor(0,0);
        LCD.print("velocity : "+Vel);
        LCD.setCursor(4,1);
        LCD.print("Over speed limit");
        // 부저 울리게 하기
        for (int position = 0; position < 16; position++){
          LCD.scrollDisplayLeft(); // 경고 메시지가 움직인다.
          delay(5000); // 과속이면 계속 부저가 울리고 모니터가 보여야함
        }
        step++; // 다음 단계로 넘어갈 준비
        crime++; // 과속했으므로 crime에 1을 더한다.
        
      }
      // 과속 아닐 때도 따로 고려?
    }
    else{ // 에러의 기준이 무엇인지?
      LCD.print("Error");
    }
    delay(500); // 0.5초마다 속도 측정
    LCD.clear(); // 모니터 끄기
  } // step 1 종료

  else if(step == 2){
    // 부저 끄기
    int alc = analogRead(alcohol_sensor);
    Serial.println(alc);
    if(alc>=700){ // 알코올 음주 측정 기준
      // 부저 울리기
      LCD.setCursor(1,0);
      LCD.print("Driver's License Revocation");  //운전면허 취소
      LCD.setCursor(4,1);
      LCD.print("alcohol : ");
      LCD.print((int)alc); // (int)인지 (string)인지 헷갈려요ㅠ
      delay(5000); // 음주면 계속 부저가 울리고 모니터가 보여야함
      step++; // 다음 단계로 갈 준비
      crime = crime + 3;
      delay(10000); // 거짓말 탐지기 부착하는 시간 필요
    }
    else if(alc>=550 && alc<700){
      // 부저 울리기
      LCD.setCursor(1,0);       
      LCD.print("driver's license suspension"); //운전면허 정지
      LCD.setCursor(4,1);       
      LCD.print("alcohol : ");
      LCD.print((int)alc);
      delay(5000); // 음주면 계속 부저가 울리고 모니터가 보여야함
      step++; // 다음 단계로 갈 준비
      crime++;
      delay(10000); // 거짓말 탐지기 부착하는 시간 필요
    }
    else{
      LCD.setCursor(1,0);       
      LCD.print("fined for speeding"); //단순 과속
      LCD.setCursor(4,1);       
      LCD.print("alcohol : ");
      LCD.print((int)alc);
    }
    delay(500); // 0.5초마다 속도 측정
    LCD.clear(); // 모니터 끄기
  }
  else if(step == 3){
    // 부저 끄기
    if(cycle <= 10){ // 5초간 standard 값을 구하는 과정
      total += analogRead(GSR);
    }
    else if(cycle <= 30){ // standard값을 구한 후부터 10초간 거짓말을 탐지
      standard = total / 10; // 기준값
      sensorValue = analogRead(GSR); // 측정값
      if(sensorValue > 1.3 * standard){ // 30%의 오차 발생 시 거짓말로 판명
        // 부저 울리기
        LCD.setCursor(1,0);
        LCD.print("False");  // 거짓말쟁이
        delay(5000); // 거짓말이면 계속 부저가 울리고 모니터가 보여야함
        step++; // 다음 단계로 갈 준비
        crime++;
      }
      
    }
    else{ // 탐지 시간이 끝났는데도 false가 안떴으므로, 참을 말함
      LCD.setCursor(1,0);
      LCD.print("False");  // 거짓말쟁이
      delay(5000); // 참이어도 일정 시간동안은 모니터가 보여야함
      step++; // 다음 단계로 갈 준비
    }
    delay(500); // 0.5초마다 속도 측정
    LCD.clear(); // 모니터 끄기
  }
  else{ // step = 4로, 최종단계에 진입. 형량을 보여줘야함
    // 부저 끄기
    if(crime == 1){
      LCD.setCursor(1,0);
      LCD.print("Fine "+String(50000)+"Won");
    }
    else if(crime == 2){
      LCD.setCursor(0,0);
      LCD.print("Fine "+String(1000000)+"Won");
      LCD.setCursor(0,1);
      LCD.print(String(4)+"year of probation");
    }
    else if(crime == 3){
      LCD.setCursor(0,0);
      LCD.print(String(10)+"year of prison labor");
    }
    else if(crime == 4){
      LCD.setCursor(0,0);
      LCD.print(String(20)+"year of prison labor");
    }
    else{
      LCD.setCursor(0,0);
      LCD.print(String(30)+"year of prison labor");
    }
    delay(500);
  }
}
