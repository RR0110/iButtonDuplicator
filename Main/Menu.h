class Menu {

  private:

    int BUTTON_PIN;
    int verticalLevel = 0;
    int horizontalLevel = 0;
    int verticalLevelMax = 2;
    int horizontalLevelMax = 18;
    boolean longPushFlag = false;
    boolean horizontalNextBlock = false;

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

    boolean getLongPushFlag() {
      return longPushFlag;
    }

    void resetLongPushFlag() {
      longPushFlag = false;
    }

    void setHorizontalNextBlock() {
      horizontalNextBlock = true;
    }

    void resetHorizontalNextBlock() {
      horizontalNextBlock = false;
    }
    /*

    */
    void clickListenerAndHandler() {
      static boolean buttonLock = false;
      if (digitalRead(BUTTON_PIN) == LOW && buttonLock == false) {
        unsigned long buttonActiveTime = millis();
        while (digitalRead(BUTTON_PIN) == LOW) {
          if (millis() - buttonActiveTime > 800)
            break;
        }
        //Fast & double push
        if (millis() - buttonActiveTime < 300) {
          buttonActiveTime = millis();
          while (true) {
            if (millis() - buttonActiveTime > 100) {
              break;
            }
            if (digitalRead(BUTTON_PIN) == LOW) {
              menuVerticalNext();
              goto end;
            }
          }
          if (horizontalNextBlock != true) {
            menuHorizontalNext();
          }
        }
        //Long push
        else if (millis() - buttonActiveTime > 600) {
          longPushFlag = !longPushFlag;
        }
end:
        buttonLock = true;
      }
      if (buttonLock == true && digitalRead(BUTTON_PIN) == HIGH) {
        buttonLock = false;
        delay(50);
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

