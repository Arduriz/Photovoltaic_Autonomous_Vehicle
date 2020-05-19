#include <Servo.h>

float angle = 0;
int on = 0;
char sound = A0+0;

Servo servo;

void setup() {
  pinMode(sound,INPUT);
  while(1) {
      if(analogRead(sound) > 500){
          if(on == 0){
              on = 1;

          }
          
          else{
              on = 0;

          }
      }
      
      if(on == 1){
          pinMode(7,OUTPUT);
          digitalWrite(7,1);
          
          while(!(179 < angle)){
            _loop();
            servo.attach(9);
            servo.write(angle);
            angle += 1;
            delay(0.03);

          }
          
          while(!(angle < 1)){
            _loop();
            servo.attach(9);
            servo.write(angle);
            angle -= 1;
            delay(0.03);

          }

      }
      
      if(on == 0){
          pinMode(7,OUTPUT);
          digitalWrite(7,0);
          angle = 0;
          servo.attach(9);
          servo.write(angle);
          delay(0.03);

      }

      _loop();
  }

}

void _loop() {
}

void loop() {
  _loop();
}
