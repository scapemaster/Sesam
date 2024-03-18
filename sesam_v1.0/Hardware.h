class Door {
  public:
  int doorswitch = 5;

  void openthedoor(int dswitch){
    digitalWrite(dswitch, LOW);
  }//EoFunc

  void closethedoor(int dswitch){
    digitalWrite(dswitch, HIGH);
  }//EoFunc
};//EoClass

class modeButton {
  public:
  int modePin = 6;


};//EoClass

class Beep {
public:
  int buzzerPin = 7;
  // Accept Buzzer
  void acc_beep() {
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
  }//EoFunction

  // Reject Buzzer
  void rej_beep(int buzzerPin) {
    digitalWrite(buzzerPin, HIGH);
    delay(600);
    digitalWrite(buzzerPin, LOW);
    delay(300);
    digitalWrite(buzzerPin, HIGH);
    delay(600);
    digitalWrite(buzzerPin, LOW);
  }//EoFunction

  // Reject Buzzer
  void err_beep(int buzzerPin) {
    digitalWrite(buzzerPin, HIGH);
    delay(600);
    digitalWrite(buzzerPin, LOW);
    delay(300);
    digitalWrite(buzzerPin, HIGH);
    delay(600);
    digitalWrite(buzzerPin, LOW);
    delay(300);
    digitalWrite(buzzerPin, HIGH);
    delay(600);
    digitalWrite(buzzerPin, LOW);
    delay(300);
    digitalWrite(buzzerPin, HIGH);
    delay(600);
    digitalWrite(buzzerPin, LOW);
  }//EoFunction
  

};//EoClass