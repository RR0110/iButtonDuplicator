class Menu {

  private:

    int BUTTON_PIN;
    int verticalLevel = 0;
    int horizontalLevel = 0;
    int verticalLevelMax = 2;
    int horizontalLevelMax = 3;

  public:

    Menu(int btnPin) {
      BUTTON_PIN = btnPin;

      pinMode(BUTTON_PIN, INPUT_PULLUP);
    }

    int getVerticalLevel() {
      return verticalLevel;
    }

    int getHorizontalLevel () {
      return horizontalLevel;
    }

    /*

    */
    void clickListenerAndHandler() {
      static boolean buttonLock = false;
      int typeOfPress;
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

