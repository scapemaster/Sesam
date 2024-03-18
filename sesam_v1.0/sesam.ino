// Inkludieren der Libraries
#include "FP_Sensor.h"
#include "Hardware.h"
#include "NFC.h"
#include "config.h"

// Klassen instanzieren
Door door;
Beep beep;


 // Variablen initiieren
int mode       = 0;
int p          = 0;
int noFinger   = 0;
int v          = 0;

void setup()
{
  // GPIO einrichten
    // Türrelais
  pinMode(door.doorswitch, OUTPUT);
  digitalWrite(door.doorswitch, HIGH);
    // Buzzer
  pinMode(beep.buzzerPin, OUTPUT); //Buzzerpin
  digitalWrite(beep.buzzerPin, LOW);

  // Serielle Kommunikation Starten
  Serial.begin(9600);
  while (!Serial);  
  delay(100);

  // SPI aktivieren
  SPI.begin();			// Init SPI bus

  // RFID Reader aktivieren
  mfrc522.PCD_Init();		// Init MFRC522
  delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme

  // Fingerprint Sensor einrichten
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    finger.LEDcontrol(FINGERPRINT_LED_BREATHING, 300, FINGERPRINT_LED_BLUE);
    Serial.println("Found fingerprint sensor!");
    delay(3000);
    finger.LEDcontrol(FINGERPRINT_LED_OFF, 0, FINGERPRINT_LED_BLUE);
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    beep.err_beep(beep.buzzerPin);
    while (1) { delay(1); }
  }

  // FP-Database prüfen
  if( ! checkdatabase()) {
    finger.LEDcontrol(FINGERPRINT_LED_FLASHING, 80, FINGERPRINT_LED_RED);
    delay(2500);
    finger.LEDcontrol(FINGERPRINT_LED_OFF, 80, FINGERPRINT_LED_RED);
    noFinger = 1;
    Serial.println("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
  }
  else {
    Serial.println("Waiting for valid finger...");
      Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  }
}//EoSetup

void loop()                     // run over and over again
{
  v = verify_tag(admin_tag);
  if(noFinger == 1 || v == 1)        {mode = 1;}
  if(v == 2)                         {beep.err_beep(beep.buzzerPin);}

  switch(mode) {
    case 0: //Secure Mode
      if(getFingerprintIDez() > 0) {
        door.openthedoor(door.doorswitch);
        delay(3000);
        door.closethedoor(door.doorswitch);
      }
      break;
    
    case 1: // Enrolle Mode
      beep.acc_beep();
        if(getFingerprintEnroll()){p = 1;} else {p = 0;}
          if(p == 1) {noFinger = 0;}
          if(p == 0) {
            finger.LEDcontrol(FINGERPRINT_LED_FLASHING, 30, FINGERPRINT_LED_RED);
            delay(2500);
            finger.LEDcontrol(FINGERPRINT_LED_OFF, 0, FINGERPRINT_LED_RED);
          }
      break;
  }
  mode = 0;
  finger.LEDcontrol(FINGERPRINT_LED_OFF, 0, FINGERPRINT_LED_RED);
}//EoLoop
