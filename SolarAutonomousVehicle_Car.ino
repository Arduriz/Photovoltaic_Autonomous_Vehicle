// 블루투스 & 자율주행자동차

int rightMoter = 10;    //센서, 모듈, 모터 핀번호
int leftMoter = 11;    
int led = 5;
int buzzer = 8;
int hall = 9; 

int trigPin = 7;   //초음파 센서
int echoPin = 6;

char command;      //블루투스로부터 수신

int stance = 0;     //상태를 나타내는 변수
int charge = 0;
int station = 0;

int batteryInput = 0;      //배터리 잔량
float batteryVoltage = 0;

void setup(){                    //핀모드 설정 & 시리얼 통신 시작
  pinMode(rightMoter,OUTPUT);
  pinMode(leftMoter,OUTPUT);

  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void run(){     // 전진
  if(stance==1){
    analogWrite(rightMoter,255);
    analogWrite(leftMoter,255);
  } 
}

void brake(){         //제동, 정지
  if(stance==1){
    analogWrite(rightMoter,0);
    analogWrite(leftMoter,0);
    charge = 0;
  }
}

void left(){         //좌회전(좌측정지，우측직진)
  if(stance==1){
    analogWrite(rightMoter,255);
    analogWrite(leftMoter,0);
  }
}

void right(){        //우회전(우측정지, 좌측직진)
  if(stance==1){
    analogWrite(rightMoter,0);
    analogWrite(leftMoter,255);
  }
}

void loop(){
  float duration, distance;      //초음파 거리 측정
  digitalWrite(trigPin, HIGH);
  delay(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = ((float)(340 * duration) / 10000) / 2;

  while(!(distance  >= 20) && stance==1){    //장애물 감지 & 회피
    analogWrite(rightMoter,0);
    analogWrite(leftMoter,100);
    delay(100);
    charge = 0;
    analogWrite(rightMoter,0);
    analogWrite(leftMoter,0);
    break;
  }
    
  if(Serial.available() > 0){     //블루투스 조작
    if(distance > 20){ 
      command = Serial.read(); 
      brake();
      switch(command){
        case 'Y':
          stance = 1;
          break;
        case 'N':
          stance = 0;
          break;
        case 'C':
          charge = 1;
          break;
        case 'F':  
          run();
          break;
        case 'B':  
          brake();
          break;
        case 'L':  
          right();
          break;
        case 'R':
          left();
          break;
      }
    }
  }

  if(stance==1){                  //on
    digitalWrite(led, HIGH);
  }
  
  if(stance==0){                  //off
    analogWrite(rightMoter,0);
    analogWrite(leftMoter,0);
    digitalWrite(led, LOW);
    charge = 0;
    station = 0;
  }

  int cds = analogRead(A0);
  
  if(charge==1){                  //충전소 탐지 & 이동
    digitalWrite(buzzer, HIGH);
    analogWrite(rightMoter,100);
    analogWrite(leftMoter,0);

    if(cds>=700){
      station = 1;
      analogWrite(rightMoter,0);
      analogWrite(leftMoter,0);     
    }

    if(station==1){
      while(!(hall==LOW)){
        analogWrite(rightMoter,100);
        analogWrite(leftMoter,100);
      }
      if(hall==LOW){
        analogWrite(rightMoter,0);
        analogWrite(leftMoter,0);
        station = 0;
        charge = 0;
      }
    }
  }

  if(charge==0){
    digitalWrite(buzzer, LOW);
  }

  int batteryInput = analogRead(A1);          //배터리 잔량 체크 & 송신
  batteryVoltage = ((float)batteryInput/1023.0)*5.0;
  if(batteryVoltage==4.2){
    Serial.println("100%");
    delay(500);
  }
  if(batteryVoltage<4.2 && batteryVoltage>=4.1){
    Serial.println("91%");
    delay(500);
  }
  if(batteryVoltage<4.1 && batteryVoltage>=4.0){
    Serial.println("79%");
    delay(500);
  }
  if(batteryVoltage<4.0 && batteryVoltage>=3.9){
    Serial.println("62%");
    delay(500);
  }
  if(batteryVoltage<3.9 && batteryVoltage>=3.8){
    Serial.println("42%");
    delay(500);
    if(distance > 20){
      charge = 1;
    }
  }
  if(batteryVoltage<3.8 && batteryVoltage>=3.7){
    Serial.println("12%");
    delay(500);
    if(distance > 20){
      charge = 1;
    }
  }
  if(batteryVoltage<3.7 && batteryVoltage>=3.6){
    Serial.println("2%");
    delay(500);
    if(distance > 20){
      charge = 1;
    }
  }
  if(batteryVoltage<3.5){
    Serial.println("0%");
    delay(500);
    } 
  
}
