#include "cube.h"

#define CUBE_SIDE 5
const uint8_t PixelPin = 2; // Pas utilisé sur ESP8266 (Le pin est RXD)


Cube cube(CUBE_SIDE, CUBE_SIDE, CUBE_SIDE);

void setupTestLeds() {
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
}

void loopTestLeds(int loopNumber) {
  digitalWrite(4, loopNumber%2);
}

void endSetupTestLeds() {
  digitalWrite(4, LOW);
}

void setup() { 
  Serial.begin(115200);
  while (!Serial); // wait for serial attach

  setupTestLeds();
  cube.setup();
  endSetupTestLeds();
}

int loopCount = 0;
void loop() { 
  loopCount++;
  loopTestLeds(loopCount);
  //cube.loop(loopCount);
  cube.colorPlanes(loopCount);
  cube.show();
  delay(300);                      // wait for a second
}