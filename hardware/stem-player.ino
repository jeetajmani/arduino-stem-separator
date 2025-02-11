// INPUT: Potentiometer should be connected to 5V and GND
int vox[4]= {A0, 0, 2, 3};
int drums[4] = {A1, 0, 4, 5};
int bass[4] = {A2, 0, 6, 7};
int instruments[4] = {A3, 0, 8, 9};

void setup() {
  Serial.begin(9600);

}

void loop() {
  vox[1] = analogRead(vox[0]);
  drums[1] = analogRead(drums[0]);
  bass[1] = analogRead(bass[0]);
  instruments[1] = analogRead(instruments[0]);

  Serial.print(vox[1]);
  Serial.print(" ");
  Serial.print(drums[1]);
  Serial.print(" ");
  Serial.print(bass[1]);
  Serial.print(" ");
  Serial.println(instruments[1]);

}
