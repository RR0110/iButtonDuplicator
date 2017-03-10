class IButton {

  public:
  
  void ledStart() {
  digitalWrite(BLUE_PIN, HIGH);
  delay(1000);
  digitalWrite(BLUE_PIN, LOW);
  delay(1000);
  }
  
};
