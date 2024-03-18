// Bibliotheken einbinden
#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>

// Setup der Anschlusspins
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.


  // Admin-NFC-Tag finden und verifizieren
  int verify_tag(String admin_tag) {
    String   id_txt = "";
    int   verify = false;
    
    if (mfrc522.PICC_IsNewCardPresent()) {                  // Kann kein Tag erkannt werden, fängt if von vorne an.
      if (! mfrc522.PICC_ReadCardSerial()) {return;}        // Kann kein Tag gelesen werden, fängt if von vorne an.
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        id_txt = id_txt + mfrc522.uid.uidByte[i];
      }
      if(id_txt == admin_tag)                 {verify = 1;} //accepted
      if(id_txt != admin_tag && id_txt != "") {verify = 2;} //rejected
    }
    return verify;
  }//EoFunction


// Tag ID lesen

String getTagID() {
    String   id_txt;
    
    if (mfrc522.PICC_IsNewCardPresent()) {                  // Kann kein Tag erkannt werden, fängt if von vorne an.
      if (! mfrc522.PICC_ReadCardSerial()) {return;}        // Kann kein Tag gelesen werden, fängt if von vorne an.
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        id_txt = id_txt + mfrc522.uid.uidByte[i];
      }
    }
    return id_txt;
}