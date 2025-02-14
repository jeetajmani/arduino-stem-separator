// [0] pot pin
// [1] pot value
// [2] solo button pin
// [3] mute button pin
// [4] solo light byte
// [5] mute light byte
// [6] solo button current state
// [7] solo button last state
// [8] solo button status
// [9] mute button current state
// [10] mute button last state
// [11] mute button status

int vox[12]= {A0, 0, 2, 3, 7, 6, 0, 1, 0, 0, 1, 0};
int drums[12] = {A1, 0, 4, 5, 5, 4, 0, 1, 0, 0, 1, 0};
int bass[12] = {A2, 0, 6, 7, 3, 2, 0, 1, 0, 0, 1, 0};
int other[12] = {A3, 0, 8, 9, 1, 0, 0, 1, 0, 0, 1, 0};

int latchPin = 11;
int clockPin = 10;
int dataPin = 12;

byte leds = 0;

int soloed = 0;

void setup() {
  Serial.begin(9600);

  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  pinMode(vox[2], INPUT_PULLUP); // vox solo
  pinMode(drums[2], INPUT_PULLUP); // drums solo
  pinMode(bass[2], INPUT_PULLUP); // bass solo
  pinMode(other[2], INPUT_PULLUP); // other solo

  pinMode(vox[3], INPUT_PULLUP); // vox mute
  pinMode(drums[3], INPUT_PULLUP); // drums mute
  pinMode(bass[3], INPUT_PULLUP); // bass mute
  pinMode(other[3], INPUT_PULLUP); // other mute

  updateShiftRegister();
}

void loop() {
  // potentiometer
  vox[1] = analogRead(vox[0]);
  drums[1] = analogRead(drums[0]);
  bass[1] = analogRead(bass[0]);
  other[1] = analogRead(other[0]);

  // solo buttons
  vox[6] = digitalRead(vox[2]);
  drums[6] = digitalRead(drums[2]);
  bass[6] = digitalRead(bass[2]);
  other[6] = digitalRead(other[2]);

  // mute buttons
  vox[9] = digitalRead(vox[3]);
  drums[9] = digitalRead(drums[3]);
  bass[9] = digitalRead(bass[3]);
  other[9] = digitalRead(other[3]);

  if (soloed > 0) {
    if (vox[8] == 0) {
      vox[1] = 0;
    }
    if (drums[8] == 0) {
      drums[1] = 0;
    }
    if (bass[8] == 0) {
      bass[1] = 0;
    }
    if (other[8] == 0) {
      other[1] = 0;
    }
  }

    if (vox[11] == 1) {
      vox[1] = 0;
    }
    if (drums[11] == 1) {
      drums[1] = 0;
    }
    if (bass[11] == 1) {
      bass[1] = 0;
    }
    if (other[11] == 1) {
      other[1] = 0;
    }
  
  Serial.print(vox[1]);
  Serial.print(" ");
  Serial.print(drums[1]);
  Serial.print(" ");
  Serial.print(bass[1]);
  Serial.print(" ");
  Serial.println(other[1]);

  // --------------------------------------------------
  // SOLO BUTTONS
  // --------------------------------------------------
  if (vox[6] == LOW && vox[7] == HIGH) { // this code only runs when the button is first pressed
    if (vox[8] == 0) {
      vox[8] = 1;
      bitSet(leds, vox[4]);
      updateShiftRegister();
      soloed++;
    } else {
      vox[8] = 0;
      soloed--;
    }
  } else if (vox[6] == HIGH && vox[7] == LOW) { // this code only runs when the button is released
    if (vox[8] == 0) {
      bitClear(leds, vox[4]);
      updateShiftRegister();
    }
  }

  if (drums[6] == LOW && drums[7] == HIGH) { // this code only runs when the button is first pressed
    if (drums[8] == 0) {
      drums[8] = 1;
      bitSet(leds, drums[4]);
      updateShiftRegister();
      soloed++;
    } else {
      drums[8] = 0;
      soloed--;
    }
  } else if (drums[6] == HIGH && drums[7] == LOW) { // this code only runs when the button is released
    if (drums[8] == 0) {
      bitClear(leds, drums[4]);
      updateShiftRegister();
    }
  }

  if (bass[6] == LOW && bass[7] == HIGH) { // this code only runs when the button is first pressed
    if (bass[8] == 0) {
      bass[8] = 1;
      bitSet(leds, bass[4]);
      updateShiftRegister();
      soloed++;
    } else {
      bass[8] = 0;
      soloed--;
    }
  } else if (bass[6] == HIGH && bass[7] == LOW) { // this code only runs when the button is released
    if (bass[8] == 0) {
      bitClear(leds, bass[4]);
      updateShiftRegister();
    }
  }
  
  if (other[6] == LOW && other[7] == HIGH) { // this code only runs when the button is first pressed
    if (other[8] == 0) {
      other[8] = 1;
      bitSet(leds, other[4]);
      updateShiftRegister();
      soloed++;
    } else {
      other[8] = 0;
      soloed--;
    }
  } else if (other[6] == HIGH && other[7] == LOW) { // this code only runs when the button is released
    if (other[8] == 0) {
      bitClear(leds, other[4]);
      updateShiftRegister();
    }
  }

  // // --------------------------------------------------
  // // MUTE BUTTONS
  // // --------------------------------------------------
  if (vox[9] == LOW && vox[10] == HIGH) { // this code only runs when the button is first pressed
    if (vox[11] == 0) {
      vox[11] = 1;
      bitSet(leds, vox[5]);
      updateShiftRegister();
    } else {
      vox[11] = 0;
    }
  } else if (vox[9] == HIGH && vox[10] == LOW) { // this code only runs when the button is released
    if (vox[11] == 0) {
      bitClear(leds, vox[5]);
      updateShiftRegister();
    }
  }

  if (drums[9] == LOW && drums[10] == HIGH) { // this code only runs when the button is first pressed
    if (drums[11] == 0) {
      drums[11] = 1;
      bitSet(leds, drums[5]);
      updateShiftRegister();
    } else {
      drums[11] = 0;
    }
  } else if (drums[9] == HIGH && drums[10] == LOW) { // this code only runs when the button is released
    if (drums[11] == 0) {
      bitClear(leds, drums[5]);
      updateShiftRegister();
    }
  }

  if (bass[9] == LOW && bass[10] == HIGH) { // this code only runs when the button is first pressed
    if (bass[11] == 0) {
      bass[11] = 1;
      bitSet(leds, bass[5]);
      updateShiftRegister();
    } else {
      bass[11] = 0;
    }
  } else if (bass[9] == HIGH && bass[10] == LOW) { // this code only runs when the button is released
    if (bass[11] == 0) {
      bitClear(leds, bass[5]);
      updateShiftRegister();
    }
  }
  
  if (other[9] == LOW && other[10] == HIGH) { // this code only runs when the button is first pressed
    if (other[11] == 0) {
      other[11] = 1;
      bitSet(leds, other[5]);
      updateShiftRegister();
    } else {
      other[11] = 0;
    }
  } else if (other[9] == HIGH && other[10] == LOW) { // this code only runs when the button is released
    if (other[11] == 0) {
      bitClear(leds, other[5]);
      updateShiftRegister();
    }
  }

  vox[7] = vox[6];
  drums[7] = drums[6];
  bass[7] = bass[6];
  other[7] = other[6];

  vox[10] = vox[9];
  drums[10] = drums[9];
  bass[10] = bass[9];
  other[10] = other[9];

}

void updateShiftRegister() {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, leds);
  digitalWrite(latchPin, HIGH);
}