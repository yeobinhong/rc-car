#include <LiquidCrystal.h> // LCD Function
#include <SoftwareSerial.h> 
#define triggerPin 8 
#define echoPin 9 //MicroWave Reciever, Transmeter설정

#define BT_RXD 2                                         // 아두이노의 4번핀을 RX(받는 핀)로 설정
#define BT_TXD 3

int alcohol_sensor = A5;
int GSR = A0;
int BUZ = 7;
int RightMotor_E_pin = 30;                               // 오른쪽 모터의 Enable & PWM
int LeftMotor_E_pin = 31;                               // 왼쪽 모터의 Enable & PWM
int RightMotor_1_pin = 32;                              // 오른쪽 모터 제어선 IN1
int RightMotor_2_pin = 33;                                // 오른쪽 모터 제어선 IN2
int LeftMotor_3_pin = 34;                                // 왼쪽 모터 제어선 IN3
int LeftMotor_4_pin = 35;    
int L_MotorSpeed = 185; // 왼쪽 모터 속도
int R_MotorSpeed = 160; // 오른쪽 모터 속도

int R_Motor = 0;
int L_Motor = 0;
int mode = 0;
SoftwareSerial bluetooth(BT_RXD,BT_TXD); 
LiquidCrystal LCD(4,6,10,11,12,13); //LCD초기화 핀, (RS,E,DB4,DB5,DB6,DB7)

void setup(){
  LCD.begin(16,2); // 16자리 2줄 사용하도록 초기화
  pinMode(triggerPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(BUZ,OUTPUT);
  digitalWrite(BUZ,LOW);
  LCD.setCursor(0,0);
  LCD.print("Setup");
  pinMode(RightMotor_E_pin, OUTPUT);                                  // 출력모드로 설정
  pinMode(RightMotor_1_pin, OUTPUT);
  pinMode(RightMotor_2_pin, OUTPUT);
  pinMode(LeftMotor_3_pin, OUTPUT);
  pinMode(LeftMotor_4_pin, OUTPUT);
  pinMode(LeftMotor_E_pin, OUTPUT);
  Serial.begin(9600);                          //PC와 아두이노간 시리얼 통신 속도를 9600bps로 설정 
  bluetooth.begin(9600);                               //블루투스와 아두이노간 시리얼 통신 속도를 9600bps로 설정
   delay(1000);
}
void control_SmartCar(char Blue_val){ 
  if( Blue_val == 'g' ){                             // "g" 버튼, 명령 : 전진
    R_Motor = HIGH; L_Motor = HIGH; mode = 0;
    //Serial.print("Forward : ");
  }  
  
  else if( Blue_val == 'r' ){                         // "r" 버튼, 명령 : 우회전
    mode = 1;
    //Serial.print("Turn Right : "); 
  }
  
  else if( Blue_val == 'l' ){                       // "l" 버튼, 명령 : 좌회전
    mode = 2;
    //Serial.print("Turn Left : "); 
  }
  
  else if( Blue_val == 'b' ){                             // "b" 버튼, 명령 : 후진
    R_Motor = LOW; L_Motor = LOW; mode = 0;
    //Serial.print("Backward : "); 
  }

  else if( Blue_val == 's' ){                             // "s" 버튼, 명령 : 정지
    R_Motor = HIGH; L_Motor = HIGH; mode = 3;
    //Serial.print("Stop : ");  
  }
  
  else if( Blue_val == 'q' ){                          // "q" 버튼, 명령 : 제자리 좌회전
    mode = 4;
    //Serial.print("Left Rotation : "); 
  }
  
  else if( Blue_val == 'w' ){                     // "w" 버튼, 명령 : 제자리 우회전
    mode = 5;
    //Serial.print("Right Rotation : ");
  }
  
  else{
    //Serial.print("Not Defined : ");                                          // 지정하지 않은 주소입력.
  }

}

void motor_role(int R_motor, int L_motor){
   digitalWrite(RightMotor_1_pin, R_motor);
   digitalWrite(RightMotor_2_pin, !R_motor);
   digitalWrite(LeftMotor_3_pin, L_motor);
   digitalWrite(LeftMotor_4_pin, !L_motor);
   
   analogWrite(RightMotor_E_pin, R_MotorSpeed);                                           // 우측 모터 속도값
   analogWrite(LeftMotor_E_pin, L_MotorSpeed);                                         // 좌측 모터 속도값  
}

void Right_role(int R_motor, int L_motor){
   digitalWrite(RightMotor_1_pin, R_motor);
   digitalWrite(RightMotor_2_pin, !R_motor);
   digitalWrite(LeftMotor_3_pin, L_motor);
   digitalWrite(LeftMotor_4_pin, !L_motor);
   
   analogWrite(RightMotor_E_pin, max(R_MotorSpeed*0.4,90));                                            // 우측 모터 속도값
   analogWrite(LeftMotor_E_pin, 255);                                            // 좌측 모터 속도값
}

void Left_role(int R_motor, int L_motor){
   digitalWrite(RightMotor_1_pin, R_motor);
   digitalWrite(RightMotor_2_pin, !R_motor);
   digitalWrite(LeftMotor_3_pin, L_motor);
   digitalWrite(LeftMotor_4_pin, !L_motor);
   
   analogWrite(RightMotor_E_pin, 255);                        // 우측 모터 속도값
   analogWrite(LeftMotor_E_pin, max(L_MotorSpeed*0.4,90));                               // 좌측 모터 속도값   
}

void left_rotation(int R_motor, int L_motor){
   digitalWrite(RightMotor_1_pin, HIGH);
   digitalWrite(RightMotor_2_pin, LOW);
   digitalWrite(LeftMotor_3_pin, LOW);
   digitalWrite(LeftMotor_4_pin, HIGH);
   
   analogWrite(RightMotor_E_pin, R_MotorSpeed);                         // 우측 모터 속도값
   analogWrite(LeftMotor_E_pin, L_MotorSpeed);                               // 좌측 모터 속도값
}

void right_rotation(int R_motor, int L_motor){
   digitalWrite(RightMotor_1_pin, LOW);
   digitalWrite(RightMotor_2_pin, HIGH);
   digitalWrite(LeftMotor_3_pin, HIGH);
   digitalWrite(LeftMotor_4_pin, LOW);
   
   analogWrite(RightMotor_E_pin, R_MotorSpeed);                         // 우측 모터 속도값
   analogWrite(LeftMotor_E_pin, L_MotorSpeed);                               // 좌측 모터 속도값
}
void loop(){
  static int step = 1;
  // 경찰차 빨강파랑 비상등 구현 필요

  static float standard = 0; // 거짓말 탐지 시, 5초 동안 측정값들의 평균값으로 기준이 됨
  static float total = 0; // standard 값을 구하기 위한 총합
  static int cycle = 1; // 각 단계에서 몇번째 주기인지 확인하기 위한 변수
  // 0.5초에 힌번씩 센서값을 측정할 것이므로, cycle = 11일때부터 거짓말 탐지를 시작한다.
  // 10초간 탐지한다. 

  static int crime = 0; // 마지막에 형량을 보여주는 값이다.

  float sensorValue = 0; // 거짓말센서가 측정한 전기전도도 값

  if(step == 1){ // step 1 : 과속 측정 시작
    Serial.println("step = "+String(step));
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

    LCD.setCursor(0,0);
      String Distance = String(Distance_mm);
      String Vel = String(abs(velocity));
      //LCD.setCursor(0,1);
      LCD.print(Vel);
      LCD.print("cm/s");

      if(abs(velocity) > 10){ // 과속의 기준이 5
        LCD.setCursor(16,0);
        LCD.print(Vel);
        LCD.print("cm/s");
        LCD.setCursor(16,1);
        LCD.print("Over speed");
        digitalWrite(BUZ,HIGH);
        for (int position = 0; position < 16; position++){
          LCD.scrollDisplayLeft(); // 경고 메시지가 움직인다.
          delay(200);
        }
        delay(5000); // 과속이면 계속 부저가 울리고 모니터가 보여야함
        step++; // 다음 단계로 넘어갈 준비
        crime++; // 과속했으므로 crime에 1을 더한다.
        
      }
    
    delay(500); // 0.5초마다 속도 측정
    LCD.clear(); // 모니터 끄기
  } // step 1 종료

  else if(step == 2){
    Serial.println("step = "+String(step));
    digitalWrite(BUZ,LOW);
    int alc;
    if(cycle <21){ // 10초 동안
      alc = analogRead(alcohol_sensor);
      Serial.println("alcohol = "+String(alc));
      if(alc>=1000){ // 알코올 음주 측정 기준
        digitalWrite(BUZ,HIGH);
        LCD.setCursor(0,0);
        LCD.print("License cancel");  //운전면허 취소
        LCD.setCursor(0,1);
        LCD.print("alcohol : ");
        LCD.print((int)alc); // lcd에서는 int로 하는게 맞음
        delay(5000); // 음주면 계속 부저가 울리고 모니터가 보여야함
        step++; // 다음 단계로 갈 준비
        crime = crime + 3;
        delay(10000); // 거짓말 탐지기 부착하는 시간 필요
      }
      else if(alc>=300 && alc<1000){
        digitalWrite(BUZ,HIGH);
        LCD.setCursor(0,0);       
        LCD.print("License stop"); //운전면허 정지
        LCD.setCursor(0,1);       
        LCD.print("alcohol : ");
        LCD.print((int)alc);
        delay(5000); // 음주면 계속 부저가 울리고 모니터가 보여야함
        step++; // 다음 단계로 갈 준비
        crime++;
        delay(10000); // 거짓말 탐지기 부착하는 시간 필요
      }
      else{
        LCD.setCursor(0,0);       
        LCD.print("Speeding"); //단순 과속
        LCD.setCursor(0,1);       
        LCD.print("alcohol : ");
        LCD.print((int)alc);
      }
    }
    else{ // 10초동안 알코올 측정이 안되었으므로 음주가 아님
      step = 4; // 단순 과속일뿐이므로 거짓말탐지할 필요가 없음 바로 4단계로 넘어감
    }
    
    delay(500); // 0.5초마다 속도 측정
    
    LCD.clear(); // 모니터 끄기
    cycle = 1; // cycle 초기화
  }
  else if(step == 3){
    Serial.println("step = "+String(step));
    digitalWrite(BUZ,LOW);
    if(cycle <= 10){ // 5초간 standard 값을 구하는 과정
      total += analogRead(GSR);
    }
    else if(cycle <= 30){ // standard값을 구한 후부터 10초간 거짓말을 탐지
      standard = total / 10; // 기준값
      sensorValue = analogRead(GSR); // 측정값
      if(sensorValue > 1.3 * standard){ // 30%의 오차 발생 시 거짓말로 판명
        digitalWrite(BUZ,HIGH);
        LCD.setCursor(0,0);
        LCD.print("False");  // 거짓말쟁이
        delay(5000); // 거짓말이면 계속 부저가 울리고 모니터가 보여야함
        step++; // 다음 단계로 갈 준비
        crime++;
      }
      
    }
    else{ // 탐지 시간이 끝났는데도 false가 안떴으므로, 참을 말함
      LCD.setCursor(0,0);
      LCD.print("True"); 
      delay(5000); // 참이어도 일정 시간동안은 모니터가 보여야함
      step++; // 다음 단계로 갈 준비
    }
    cycle++;
    delay(500); // 0.5초마다 속도 측정
    LCD.clear(); // 모니터 끄기
  }
  else{ // step = 4로, 최종단계에 진입. 형량을 보여줘야함
    Serial.println("step = "+String(step));
    digitalWrite(BUZ,LOW);
    if(crime == 1){
      LCD.setCursor(0,0);
      LCD.print("Fine 50000Won");
    }
    else if(crime == 2){
      LCD.setCursor(0,0);
      LCD.print("Fine 1000000Won");
    }
    else if(crime == 3){
      LCD.setCursor(0,0);
      LCD.print("10year prison");
    }
    else if(crime == 4){
      LCD.setCursor(0,0);
      LCD.print("20year prison");
    }
    else{
      LCD.setCursor(0,0);
      LCD.print("30year prison");
    }
    delay(500);
  }
}
