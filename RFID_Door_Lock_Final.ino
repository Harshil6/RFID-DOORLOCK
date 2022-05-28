// Copyright@ The Creator's Channel //
// Please install all the necessary libraries, links are next to them if you need to download //
// Please follow the steps shown in the video and don't skip parts in it //
// Please leave a comment if you are facing any issue in the project //
// Enjoy! //

#include <SPI.h> // https://github.com/PaulStoffregen/SPI
#include <MFRC522.h> // https://github.com/miguelbalboa/rfid
 
#define SS_PIN 5
#define RST_PIN 9
#define RELAY 3 // connect the relay tirgger pin (I.N pin) to pin number 3 
#define BUZZER 6 // connect the buzzer to 6 pin(Optional Buzzer intregation)
#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  pinMode(RELAY, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  noTone(BUZZER);
  digitalWrite(RELAY, HIGH);
  Serial.println("Put your card to the reader for identification ...");
  Serial.println();

}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "E3 05 2E 19") // Copy your Tag number from serial monitor and paste it here
  {
    Serial.println("Access Authorised- Please proced");
    Serial.println();
    delay(500);
    digitalWrite(RELAY, LOW);
    delay(ACCESS_DELAY);
    digitalWrite(RELAY, HIGH);
    
  }
 
 else   {
    Serial.println("Access denied- Authorities Alerted");
    tone(BUZZER, 300);
    delay(DENIED_DELAY);
    noTone(BUZZER);
  }
}
