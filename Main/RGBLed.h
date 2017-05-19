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
      if (clr == -3) {
        analogWrite(RED_PIN, 30);
        analogWrite(GREEN_PIN, 30);
        analogWrite(BLUE_PIN, 30);
      }
      else if (clr == -2) {
        analogWrite(RED_PIN, 255);
        analogWrite(GREEN_PIN, 0);
        analogWrite(BLUE_PIN, 255);
      }
      else if (clr == -1) {
        analogWrite(RED_PIN, 0);
        analogWrite(GREEN_PIN, 0);
        analogWrite(BLUE_PIN, 0);
      }
      else if (clr == 0 || clr == 3  || clr == 6  || clr == 9  || clr == 12  || clr == 16  || clr == 18) {
        analogWrite(RED_PIN, 255);
        analogWrite(GREEN_PIN, 0);
        analogWrite(BLUE_PIN, 0);
      }
      else if (clr == 1 || clr == 4  || clr == 7  || clr == 10  || clr == 13  || clr == 16) {
        analogWrite(RED_PIN, 0);
        analogWrite(GREEN_PIN, 255);
        analogWrite(BLUE_PIN, 0);
      }
      else if (clr == 2  || clr == 5  || clr == 8  || clr == 11  || clr == 14  || clr == 17) {
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
      if (delayTime == 0) {
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

