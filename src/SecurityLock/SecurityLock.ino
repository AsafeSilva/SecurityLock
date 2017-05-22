#include <Servo.h>

#define pinBeep 15
#define pinServo 9
#define pinInternalButton 11

#define servoClose 100
#define servoOpen  180

String password = "1234";
int countPassword = -1;

bool lockState = false;

Servo servo;

void setup() {
  servo.attach(pinServo);

  pinMode(pinInternalButton, INPUT_PULLUP);
  pinMode(pinBeep, OUTPUT);
  pinMode(18, OUTPUT);  digitalWrite(18, LOW);

  keyBegin();
}

void loop() {

  char val = getKey();

  if (val != 0) {

    countPassword++;

    if (val == '#') {
      // CANCELAR SENHA
      beep(pinBeep, 1, 100);
      countPassword = -1;

    } else if (val == password.charAt(countPassword)) {
      // DÍGITO CORRETO
      if (countPassword == password.length() - 1) {
        beep(pinBeep, 1, 700);
        countPassword = -1;
        lockState = !lockState;
      }
    } else {
      // DÍGITO INCORRETO
      if (countPassword == password.length() - 1) {
        beep(pinBeep, 2, 100);
        countPassword = -1;
      }
    }
  }

  servo.write(lockState ? servoOpen : servoClose);

  if (!digitalRead(pinInternalButton)) {
    delay(100);
    if (!digitalRead(pinInternalButton)) {
      lockState = !lockState;
      beep(pinBeep, 1, 700);
    }
  }
}

void beep(int pin, int count, int timeBeep) {
  for (int i = 0; i < count; i++) {
    digitalWrite(pin, 1);
    delay(timeBeep);
    digitalWrite(pin, 0);
    delay(timeBeep);
  }
}

