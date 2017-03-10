#include <OneWire.h>

const int button = 5;
const int redPin = 6;
const int greenPin = 10;
const int bluePin = 9;
const int ibuttonPin = 11;

OneWire ibutton (ibuttonPin);

int writeByte(byte data);
void writeCode(byte code[], int activeColor);
void setLedColor(String color);
void setLed(int red, int green, int blue);
void activeLedColor(int activeColor);
void blinkLed(int delayTime, int activeColor);

void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT_PULLUP);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  static int activeLevel = 0;
  static int activeKeyCode = 0;
  static byte readAddress[8] = { 
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF      };
  static byte saveAddress[8];

  //ОБРАБОТЧИК НАЖАТИЙ КЛАВИШИ
  static boolean buttonLock = false;
  if(digitalRead(button) == LOW && buttonLock == false) {
    unsigned long buttonTime = millis();
    while(digitalRead(button) == LOW) {
      if(millis() - buttonTime > 500) break;
    }
    //Fast push
    if(millis() - buttonTime < 500) {
      if(activeKeyCode + 1 > 5) activeKeyCode = 0;
      else activeKeyCode++;
    }
    //Long push
    else if(millis() - buttonTime > 200) {
      if(activeLevel + 1 > 1) activeLevel = 0;
      else activeLevel++;
    }
    buttonLock = true;
  }
  if(buttonLock == true && digitalRead(button) == HIGH) {
    buttonLock = false;
    delay(100);
  }
  //----------//

  //Режим чтения
  if(activeLevel == 0) {
    if(ibutton.search(readAddress)) {
      blinkLed(10, activeKeyCode);
    }
    else {
      blinkLed(-1, activeKeyCode);
    }
  }
  //Режим записи
  else if(activeLevel == 1) {
    blinkLed(0, activeKeyCode);
    for (int i = 0; i < 8; i++) {
      saveAddress[i] = readAddress[i];
    }
    if (ibutton.search(readAddress)) {
      blinkLed(-1, activeKeyCode);
      delay(300);
      writeCode(saveAddress, activeKeyCode);
      activeLevel = 0;
    }
  }
}

//Функуция записи одельных битов
int writeByte(byte data) {
  for (int data_bit = 0; data_bit < 8; data_bit++) {
    if (data & 1) {
      digitalWrite(ibuttonPin, LOW); 
      pinMode(ibuttonPin, OUTPUT);
      delayMicroseconds(60);
      pinMode(ibuttonPin, INPUT); 
      digitalWrite(ibuttonPin, HIGH);
      delay(10);
    }
    else {
      digitalWrite(ibuttonPin, LOW); 
      pinMode(ibuttonPin, OUTPUT);
      pinMode(ibuttonPin, INPUT); 
      digitalWrite(ibuttonPin, HIGH);
      delay(10);
    }
    data = data >> 1;
  }
  return 0;
}

//Функуция записи адреса в ключ
void writeCode(byte code[], int activeColor) {
  ibutton.skip(); 
  ibutton.reset(); 
  ibutton.write(0x33);
  // send reset
  ibutton.skip();
  ibutton.reset();
  // send 0xD1
  ibutton.write(0xD1);
  // send logical 0
  digitalWrite(ibuttonPin, LOW); 
  pinMode(ibuttonPin, OUTPUT); 
  delayMicroseconds(60);
  pinMode(ibuttonPin, INPUT); 
  digitalWrite(ibuttonPin, HIGH); 
  delay(10);
  ibutton.skip();
  ibutton.reset();
  ibutton.write(0xD5);
  for (int i = 0; i < 8; i++) {
    writeByte(code[i]);
  }
  ibutton.reset();
  // send 0xD1
  ibutton.write(0xD1);
  //send logical 1
  digitalWrite(ibuttonPin, LOW); 
  pinMode(ibuttonPin, OUTPUT); 
  delayMicroseconds(10);
  pinMode(ibuttonPin, INPUT); 
  digitalWrite(ibuttonPin, HIGH); 
  delay(10);
}

void activeLedColor(int activeColor) {
  if(activeColor == 0) setLedColor("GRAY");
  else if(activeColor == 1) setLedColor("RED");
  else if(activeColor == 2) setLedColor("GREEN");
  else if(activeColor == 3) setLedColor("BLUE");
  else if(activeColor == 4) setLedColor("PINK");
  else if(activeColor == 5) setLedColor("YELLOW");
  else if(activeColor == -1) setLedColor("OFF");
}

void setLedColor(String color) {
  if(color == "OFF") setLed(0, 0, 0);
  else if(color == "RED") setLed(255, 0, 0);
  else if(color == "ORANGE") setLed(218, 104, 28);
  else if(color == "YELLOW") setLed(255, 255, 0);
  else if(color == "GREEN") setLed(0, 128, 0);
  else if(color == "BLUE") setLed(0, 100, 255);
  else if(color == "INDIGO") setLed(0, 0, 50);
  else if(color == "VIOLET") setLed(128, 0, 128);
  else if(color == "WHITE") setLed(255, 255, 255);
  else if(color == "GRAY") setLed(128, 128, 128);
  else if(color == "OLIVE") setLed(128, 128, 0);
  else if(color == "TEAL") setLed(0, 128, 128);
  else if(color == "PINK") setLed(255, 0, 255);
}

void setLed(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void blinkLed(int delayTime, int activeColor) {
  static unsigned long blinkTimer = millis();
  static boolean ledState = 0;
  if(delayTime == 0) {
    activeLedColor(activeColor);
  }
  if(delayTime == -1) {
    setLedColor("OFF");
  }
  else {
    if(millis() - blinkTimer > delayTime) {
      if(ledState == 0) {
        activeLedColor(activeColor);
        ledState = 1;
      }
      else if(ledState == 1) {
        setLedColor("OFF");
        ledState = 0;
      }
      blinkTimer = millis();
    }
  }
}
