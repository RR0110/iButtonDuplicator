#include <OneWire.h>
#include <EEPROM.h>

class IButton {

  private:

    int IBUTTON_PIN;
    OneWire ibtn;
    byte lastReadCodeOfKey[8] = {
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
    };
    byte lastReadCodeOfEEPROM[8] = {
      0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
    };
    //byte defaultCode1[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    //byte defaultCode2[8] = {0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD};
    //byte defaultCode3[8] = {0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE};

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
    void writeCodeInIButton() {
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
        writeByteInIButton(lastReadCodeOfKey[i]);
        delay(1);
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

    void writeCodeInIButton(int cell) {
      readCodeOfEEPROM(cell);
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
        writeByteInIButton(lastReadCodeOfEEPROM[i]);
        delay(1);
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

    void writeCodeInEEPROM(int cell) {
      for (int i = 0; i < 8; i++) {
        EEPROM.update((cell * 8) + i, lastReadCodeOfKey[i]);
      }
    }

    void readCodeOfEEPROM(int cell) {
      for (int i = 0; i < 8; i++) {
        lastReadCodeOfEEPROM[i] = EEPROM.read((cell * 8) + i);
      }
    }

    /*

    */
    boolean isIButtonSearch(int flag = 0) {
      if (flag == 1)
      {
        if (ibtn.search(lastReadCodeOfKey))
        {
          ibtn.reset_search();
          return true;
        }
        else
        {
          return false;
        }
      }
      else
      {
        byte data[8];
        if (ibtn.search(data)) {
          ibtn.reset_search();
          return true;
        }
        else
        {
          return false;
        }
      }
    }
};

