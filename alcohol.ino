int sensor = A5;
int blue = 1;
int green = 2;
int red = 3;

void setup(){
  Serial.begin(9600);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
}

void loop(){
  int alcohol=analogRead(sensor);
  Serial.println(alcohol);         
  if(alcohol>=700){                  
    analogWrite(red,255);     
    analogWrite(green,0);
    analogWrite(blue,0);
    delay(100);
  }  
  else if(alcohol>=550 && alcohol<700){  
    analogWrite(red,0);        
    analogWrite(green,255);    
    analogWrite(blue,0);
    delay(100);
  }
  else if(alcohol<550){               
    analogWrite(red,0);
    analogWrite(green,0);
    analogWrite(blue,255);     
    delay(100);
  }
}
