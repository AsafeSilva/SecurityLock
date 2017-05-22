#define numLin 4
#define numCol 3
#define timeDebounce 50

char teclado[numLin][numCol] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

int pinLin[numLin] = {5, 6, 7, 8};
int pinCol[numCol] = {2, 3, 4};

unsigned long beepTime = 0;

void keyBegin() {

  for (int col = 0; col < numCol; col++) {
    pinMode(pinCol[col], OUTPUT);
  }

  for (int lin = 0; lin < numLin; lin++) {
    pinMode(pinLin[lin], INPUT_PULLUP);
  }
}

char getKey() {

  char key = 0;

  for (int col = 0; col < numCol; col++) {

    digitalWrite(pinCol[0], 1);
    digitalWrite(pinCol[1], 1);
    digitalWrite(pinCol[2], 1);
    digitalWrite(pinCol[col], 0);


    for (int lin = 0; lin < numLin; lin++) {

      if (digitalRead(pinLin[lin]) == LOW) {

        beepTime = millis();
        digitalWrite(pinBeep, 1);
        delay(timeDebounce);

        while (digitalRead(pinLin[lin]) == LOW) {
          if (millis() - beepTime > 400) digitalWrite(pinBeep, 0);
          key = teclado[lin][col];
        }

        digitalWrite(pinBeep, 0);
        delay(timeDebounce + 50);
      }
    }
  }

  return key;
}

