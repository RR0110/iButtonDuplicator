#include "Head.h"
#include "IButton.h"

IButton butt;

void setup() {
  pinMode(BLUE_PIN, OUTPUT);
}

void loop() {
  butt.ledStart();
}
