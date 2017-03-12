#include "IButton.h"
#include "Menu.h"
#include "RGBLed.h"

const int BUTTON_PIN = 5;
const int RED_PIN = 6;
const int GREEN_PIN = 10;
const int BLUE_PIN = 9;
const int IBUTTON_PIN = 11;

IButton ibutton(IBUTTON_PIN);
Menu menu(BUTTON_PIN);
RGBLed led(RED_PIN, GREEN_PIN, BLUE_PIN);

void setup() {
  
}

void loop() {

  menu.clickListenerAndHandler();
  //Уровень чтения read
  if (menu.getVerticalLevel() == 0) {
    if(ibutton.isIButtonSearch() == true) {
      led.setColor(-2);
    }
    else{
      led.setColor(menu.getHorizontalLevel());
    }
  }
  //Уровень записи write
  else if (menu.getVerticalLevel() == 1) {
    led.ledBlink(200, menu.getHorizontalLevel());
  }

}
