#include "IButton.h"
#include "Menu.h"
#include "RGBLed.h"

const byte BUTTON_PIN = 5;
const byte RED_PIN = 6;
const byte GREEN_PIN = 10;
const byte BLUE_PIN = 9;
const byte IBUTTON_PIN = 11;

IButton ibutton(IBUTTON_PIN);
RGBLed led(RED_PIN, GREEN_PIN, BLUE_PIN);
