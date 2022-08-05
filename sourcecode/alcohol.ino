#include <LiquidCrystal.h>
LiquidCrystal LCD(4,6,10,11,12,13);// (RS, E, DB4,DB5,DB6,DB7)

int sensor = A5;
int blue = 1;
int green = 2;
int red = 3;

void setup(){
  LCD.begin(16,2);
  Serial.begin(9600);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
}

void loop(){
  int alc=analogRead(sensor);
  Serial.println(alc);         
  if(alc>=700){  //이거도 아무숫자예요                
    analogWrite(red,255);     
    analogWrite(green,0);
    analogWrite(blue,0);
    delay(1000);
    LCD.setCursor(1,0);       
    LCD.print("Driver's License Revocation");        //운전면허 취소
    LCD.setCursor(4,1);
    LCD.print("alcohol : ");
    LCD.print((int)alc);
    delay(500);
    LCD.clear();// LCD 문자열 삭제
  }  
  else if(alc>=550 && alc<700){  
    analogWrite(red,0);        
    analogWrite(green,255);    
    analogWrite(blue,0);
    delay(1000);
    LCD.setCursor(1,0);       
    LCD.print("driver's license suspension"); //운전면허 정지
    LCD.setCursor(4,1);       
    LCD.print("alcohol : ");
    LCD.print((int)alc);
    delay(500);
    LCD.clear();
  }
  else if(alc<550){               
    analogWrite(red,0);
    analogWrite(green,0);
    analogWrite(blue,255);     
    delay(1000);
    LCD.setCursor(1,0);       
    LCD.print("fined for speeding"); //단순 과속
    LCD.setCursor(4,1);       
    LCD.print("alcohol : ");
    LCD.print((int)alc);
    delay(500);
    LCD.clear();
  }
}
