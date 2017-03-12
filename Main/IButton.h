#include <OneWire.h>

class IButton {

  private:

    int IBUTTON_PIN;;
    OneWire ibtn;
    byte lastReadCode[8] = {
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
    };

  private:

    /*

    */
    void writeByteInIButton(byte data) {
      for (int data_bit = 0; data_bit < 8; data_bit++) {
        if (data & 1) {
          digitalWrite(IBUTTON_PIN, LOW);
          pinMode(IBUTTON_PIN, OUTPUT);
          delayMicroseconds(60);
          pinMode(IBUTTON_PIN, INPUT);
          digitalWrite(IBUTTON_PIN, HIGH);
          delay(10);
        }
        else {
          digitalWrite(IBUTTON_PIN, LOW);
          pinMode(IBUTTON_PIN, OUTPUT);
          pinMode(IBUTTON_PIN, INPUT);
          digitalWrite(IBUTTON_PIN, HIGH);
          delay(10);
        }
        data = data >> 1;
      }
    }

  public:

    IButton(int iBtnPin) : ibtn(iBtnPin) {
      IBUTTON_PIN = iBtnPin;
    }

    /*

    */
    void writeCode() {
      ibtn.skip();
      ibtn.reset();
      ibtn.write(0x33);
      // send reset
      ibtn.skip();
      ibtn.reset();
      // send 0xD1
      ibtn.write(0xD1);
      // send logical 0
      digitalWrite(IBUTTON_PIN, LOW);
      pinMode(IBUTTON_PIN, OUTPUT);
      delayMicroseconds(60);
      pinMode(IBUTTON_PIN, INPUT);
      digitalWrite(IBUTTON_PIN, HIGH);
      delay(10);
      ibtn.skip();
      ibtn.reset();
      ibtn.write(0xD5);
      for (int i = 0; i < 8; i++) {
        writeByteInIButton(lastReadCode[i]);
      }
      ibtn.reset();
      // send 0xD1
      ibtn.write(0xD1);
      //send logical 1
      digitalWrite(IBUTTON_PIN, LOW);
      pinMode(IBUTTON_PIN, OUTPUT);
      delayMicroseconds(10);
      pinMode(IBUTTON_PIN, INPUT);
      digitalWrite(IBUTTON_PIN, HIGH);
      delay(10);
    }

    /*

    */
    boolean isIButtonSearch() {
      byte data[8];
      if (ibtn.search(data)) {
        ibtn.reset_search();
        return true;
      }
      else {
        return false;
      }
    }

    void readCode() {
      ibtn.search(lastReadCode);
      ibtn.reset_search();
    }
};

