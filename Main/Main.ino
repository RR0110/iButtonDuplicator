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
  //===Уровень чтения и быстрой записи===
  if (menu.getVerticalLevel() == 0) {
    menu.setHorizontalNextBlock();
    if (menu.getLongPushFlag() != true) {
      if (ibutton.isIButtonSearch() == true) {
        ibutton.readCode();
        led.ledBlink(100, -3);
        delay(100);
      }
      else {
        led.setColor(-3);
      }
    }
    /*
       Быстрая запись считанного кода
    */
    else if (menu.getLongPushFlag() == true) {
      while (menu.getLongPushFlag() == true) {
        menu.clickListenerAndHandler();
        led.setColor(-2);
        if (ibutton.isIButtonSearch() == true) {
          delay(400);
          ibutton.writeCodeInIButton();
          delay(100);
          menu.resetLongPushFlag();
        }
      }
    }
  }
  //===Уровень записи из памяти или в память EEPROM===
  else if (menu.getVerticalLevel() == 1) {
    menu.resetHorizontalNextBlock();
    led.setColor(menu.getHorizontalLevel());
    /*
       Если ключ на контактной площадке, произвести запись
       кода в ключ из EEPROM
    */
    if (ibutton.isIButtonSearch() == true) {
      led.setColor(-2);
      delay(400);
      ibutton.writeCodeInIButton(menu.getHorizontalLevel());
      menu.menuVerticalNext();
      delay(100);
    }

    /*
       Если EEPROM активен (длинное нажатие),
       записать последний считанный ключ в EEPROM
    */
    if (menu.getLongPushFlag() == true) {
      led.setColor(-2);
      ibutton.writeCodeInEEPROM(menu.getHorizontalLevel());
      menu.resetLongPushFlag();
      delay(200);
    }
  }

}
