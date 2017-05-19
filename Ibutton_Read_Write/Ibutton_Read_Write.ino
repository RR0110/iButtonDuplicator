#include <OneWire.h>
int ibutton_pin = 13;
OneWire ibutton (ibutton_pin);

byte address[8];
byte addressBase[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01};

void setup() {
  Serial.begin(9600);
}

int writeByte(byte data, int i_pin);
void Read(byte addr[], int i_pin);
void Write(byte base[], int i_pin);

void loop() {
  static int modState = 0;
  if (ibutton.search(address) && modState == 0) {
    Read(address, ibutton_pin);
  }
  if (Serial.read() == 'w') {
    modState = 1;
    Serial.println("Write mod!");
  }
  if (modState == 1) {
    Write(addressBase, ibutton_pin);
    modState = 0;
  }
}

int writeByte(byte data, int i_pin) {
  for (int data_bit = 0; data_bit < 8; data_bit++) {
    if (data & 1) {
      digitalWrite(i_pin, LOW); pinMode(i_pin, OUTPUT);
      delayMicroseconds(60);
      pinMode(i_pin, INPUT); digitalWrite(i_pin, HIGH);
      delay(10);
    }
    else {
      digitalWrite(i_pin, LOW); pinMode(i_pin, OUTPUT);
      pinMode(i_pin, INPUT); digitalWrite(i_pin, HIGH);
      delay(10);
    }
    data = data >> 1;
  }
}

void Read(byte addr[], int i_pin) {
  for (int i = 0; i < 8; i++) {
    Serial.print(addr[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}

void Write(byte base[], int i_pin) {
  ibutton.skip(); ibutton.reset(); ibutton.write(0x33);
  ibutton.skip();
  ibutton.reset();
  ibutton.write(0xD1);
  digitalWrite(i_pin, LOW); pinMode(i_pin, OUTPUT); delayMicroseconds(60);
  pinMode(i_pin, INPUT); digitalWrite(i_pin, HIGH); delay(10);
  ibutton.skip();
  ibutton.reset();
  ibutton.write(0xD5);
  for (int i = 0; i < 8; i++) {
    writeByte(base[i], i_pin);
    Serial.print('*');
  }
  Serial.print('\n');
  ibutton.reset();
  ibutton.write(0xD1);
  digitalWrite(i_pin, LOW); pinMode(i_pin, OUTPUT); delayMicroseconds(i_pin);
  pinMode(i_pin, INPUT); digitalWrite(i_pin, HIGH); delay(i_pin);
}
