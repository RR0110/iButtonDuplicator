class Menu {

  private:

    byte BUTTON_PIN;
    byte verticalLevel = 0;
    byte horizontalLevel = 0;
    byte verticalLevelMax = 2;
    byte horizontalLevelMax = 3;

  public:

    Menu(byte btnPin) {
      BUTTON_PIN = btnPin;

      pinMode(BUTTON_PIN, INPUT_PULLUP);
    }

    byte getVerticalLevel() {
      return verticalLevel;
    }

    byte getHorizontalLevel () {
      return horizontalLevel;
    }

    /*

    */
    void clickListenerAndHandler() {
      static boolean buttonLock = false;
      byte typeOfPress;
      if (digitalRead(BUTTON_PIN) == LOW && buttonLock == false) {
        unsigned long buttonActiveTime = millis();
        while (digitalRead(BUTTON_PIN) == LOW) {
          if (millis() - buttonActiveTime > 500) 
          break;
        }
        //Fast push
        if (millis() - buttonActiveTime < 500) {
          menuHorizontalNext();
        }
        //Long push
        else if (millis() - buttonActiveTime > 200) {
          menuVerticalNext();
        }
        buttonLock = true;
      }
      if (buttonLock == true && digitalRead(BUTTON_PIN) == HIGH) {
        buttonLock = false;
        delay(100);
      }
    }

    /*

    */
    void menuHorizontalNext() {
      if (horizontalLevel + 1 < horizontalLevelMax) {
        horizontalLevel++;
      }
      else {
        horizontalLevel = 0;
      }
    }

    /*

    */
    void menuVerticalNext() {
      if (verticalLevel + 1 < verticalLevelMax) {
        verticalLevel++;
      }
      else {
        verticalLevel = 0;
      }
    }
};

