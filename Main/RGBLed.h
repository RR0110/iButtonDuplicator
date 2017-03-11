class RGBLed {

  private:

    byte RED_PIN;
    byte GREEN_PIN;
    byte BLUE_PIN;

  public:

    RGBLed(byte redPin, byte greenPin, byte bluePin) {
      RED_PIN = redPin;
      GREEN_PIN = greenPin;
      BLUE_PIN = bluePin;

      pinMode(RED_PIN, OUTPUT);
      pinMode(GREEN_PIN, OUTPUT);
      pinMode(BLUE_PIN, OUTPUT);
    }

    /*

    */
    void setColor(String clr) {
      if (clr == "OFF") {
        analogWrite(RED_PIN, 0);
        analogWrite(GREEN_PIN, 0);
        analogWrite(BLUE_PIN, 0);
      }
      else if (clr == "RED") {
        analogWrite(RED_PIN, 255);
        analogWrite(GREEN_PIN, 0);
        analogWrite(BLUE_PIN, 0);
      }
      else if (clr == "GREEN") {
        analogWrite(RED_PIN, 0);
        analogWrite(GREEN_PIN, 255);
        analogWrite(BLUE_PIN, 0);
      }
      else if (clr == "BLUE") {
        analogWrite(RED_PIN, 0);
        analogWrite(GREEN_PIN, 0);
        analogWrite(BLUE_PIN, 255);
      }
    }

    void setColor(byte clr) {
      if (clr == -1) {
        analogWrite(RED_PIN, 0);
        analogWrite(GREEN_PIN, 0);
        analogWrite(BLUE_PIN, 0);
      }
      else if (clr == 0) {
        analogWrite(RED_PIN, 255);
        analogWrite(GREEN_PIN, 0);
        analogWrite(BLUE_PIN, 0);
      }
      else if (clr == 1) {
        analogWrite(RED_PIN, 0);
        analogWrite(GREEN_PIN, 255);
        analogWrite(BLUE_PIN, 0);
      }
      else if (clr == 2) {
        analogWrite(RED_PIN, 0);
        analogWrite(GREEN_PIN, 0);
        analogWrite(BLUE_PIN, 255);
      }
    }

    /*

    */
    void ledBlink(int delayTime, String clr) {
      static unsigned long blinkTimer = millis();
      static boolean ledState = 0;
      if (delayTime == 0) {
        setColor(clr);
      }
      if (delayTime == -1) {
        setColor("OFF");
      }
      else {
        if (millis() - blinkTimer > delayTime) {
          if (ledState == 0) {
            setColor(clr);
            ledState = 1;
          }
          else if (ledState == 1) {
            setColor("OFF");
            ledState = 0;
          }
          blinkTimer = millis();
        }
      }
    }

    void ledBlink(int delayTime, byte clr) {
      static unsigned long blinkTimer = millis();
      static boolean ledState = 0;
      if (delayTime == 0) {
        setColor(clr);
      }
      if (delayTime == -1) {
        setColor("OFF");
      }
      else {
        if (millis() - blinkTimer > delayTime) {
          if (ledState == 0) {
            setColor(clr);
            ledState = 1;
          }
          else if (ledState == 1) {
            setColor("OFF");
            ledState = 0;
          }
          blinkTimer = millis();
        }
      }
    }
};

