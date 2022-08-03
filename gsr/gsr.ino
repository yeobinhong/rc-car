#define BLUE 11
#define GREEN 10
#define RED 9

const int GSR=A0;
float sensorValue=0; // 센서가 측정한 날 것의 전기전도도 값
float gsr_average = 0; // 50ms에 한번씩 도출할 수 있는 평균값으로, 이를 일반적인 측정값으로 취급할 것이다.
 
void setup(){
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  
  Serial.begin(9600);
}
 
void loop(){
  static float standard = 0; // 5초 동안의 gsr_average 값들의 평균값으로, 101번째 loop부터 참/거짓 판별의 기준이 된다.
  static int cycle = 1; // 몇번째 loop를 돌고 있는지 체크하는 값이다. 100번째 loop가 끝나기 직전에, standard를 계산한다.
  static float total = 0; // 5초 동안의 gsr_average 값들의 총합이다. 100번째 loop가 끝나기 직전에, standard를 계산한다.
  
  float sum=0;
  for(int i=0;i<10;i++)           // 오차를 줄이기 위해 10개의 측정값의 평균을 구한다.
      {
      sensorValue=analogRead(GSR) / 10; // 측정값을 할당
      sum += sensorValue; // for문을 다 돌게 되면, sum에 10개의 측정값의 합이 할당된다.
      delay(5); // 5ms마다 한번씩 for loop를 돌게 된다.
      }
  gsr_average = sum/10; // 10개의 측정값의 평균값이므로, 이 값은 50ms에 한번씩 출력된다.

  if(cycle > 100){ // 5초가 지나서 참/거짓 판별을 해야 한다.
      if(gsr_average > 1.005 * standard || gsr_average < 0.995 * standard){
        // 기준치로부터 30퍼센트 이상 벗어났을 때, 거짓으로 판정
        // LED 빨간불 켠다.  
        analogWrite(RED, 255);
        analogWrite(GREEN, 0);
      }
      else{ // 기준치로부터 크게 벗어나지 않았으므로, 참으로 판정
        // LED 초록불 켠다.
        analogWrite(RED, 0);
        analogWrite(GREEN, 255);
      }
  }
   
   total = total + gsr_average; // 101번째 loop부터는 standard 계산이 불필요
   
   Serial.println(gsr_average); // 구한 평균값을 출력한다.
   Serial.println(standard);
   
   if(cycle == 100){ // 100번째 loop를 돌아, 5초가 지났으므로 standard 값을 계산한다.
      standard = total / cycle;
   }
   cycle++; // loop가 한번 돌 때마다 1을 더한다. 
}
