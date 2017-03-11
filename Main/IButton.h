class IButton {
  
  private:
  
  byte IBUTTON_PIN = 11;

  public:

  IButton(byte ibtn_pin) {
    IBUTTON_PIN = ibtn_pin;
  }
  
};

