class RGBLed {

  private:

    int RED_PIN;
    int GREEN_PIN;
    int BLUE_PIN;

  public:

    RGBLed(int redPin, int greenPin, int bluePin) {
      RED_PIN = redPin;
      GREEN_PIN = greenPin;
      BLUE_PIN = bluePin;

      pinMode(RED_PIN, OUTPUT);
      pinMode(GREEN_PIN, OUTPUT);
      pinMode(BLUE_PIN, OUTPUT);
    }

    /*

    */
    void setColor(int clr) {
      if (clr == -2) {
        analogWrite(RED_PIN, 100);
        analogWrite(GREEN_PIN, 100);
        analogWrite(BLUE_PIN, 100);
      }
      else if (clr == -1) {
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
    void ledBlink(int delayTime, int clr) {
      static unsigned long blinkTimer = millis();
      static boolean ledState = false;
      if(delayTime == 0) {
        setColor(-1);
      }
      else if (millis() - blinkTimer > delayTime) {
        if (ledState == false) {
          setColor(clr);
          ledState = true;
        }
        else if (ledState == true) {
          setColor(-1);
          ledState = false;
        }
        blinkTimer = millis();
      }
    }

};

