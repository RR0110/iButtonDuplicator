#include <OneWire.h>

class IButton {

  private:

    const byte IBUTTON_PIN = 11;
    OneWire ibtn{IBUTTON_PIN};

  private:

    /*
     * 
    */
    void writeByteInKey(byte data) {
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

    /*
     * 
    */
    void writeCodeInIButton(byte code[]) {
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
      for (byte i = 0; i < 8; i++) {
        writeByteInKey(code[i]);
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


};

