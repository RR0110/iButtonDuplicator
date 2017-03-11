class RGBLed {

  private:
  
  byte RED_PIN;
  byte GREEN_PIN;
  byte BLUE_PIN;

  public:

  RGBLed(byte red_pin, byte green_pin, byte blue_pin) {
    RED_PIN = red_pin;
    GREEN_PIN = green_pin;
    BLUE_PIN = blue_pin;
  }
  
};

