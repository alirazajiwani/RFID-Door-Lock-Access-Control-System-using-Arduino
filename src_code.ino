#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define RST_PIN 9
#define SS_PIN  10

MFRC522 mfrc522(SS_PIN, RST_PIN); // RFID instance
String MasterTag = "95 86 11 7B"; // Set your MasterTag UID here

String UIDCard = "";

LiquidCrystal_I2C lcd(0x3F, 16, 2);

Servo servo;

#define BlueLED  2
#define GreenLED 3
#define RedLED 4

#define Buzzer 5

void setup() {
  Serial.begin(9600);

  SPI.begin();

 mfrc522.PCD_Init();
  lcd.init();
  lcd.backlight();
  lcd.clear();

  servo.attach(6);
  servo.write(0); // Initial servo position

  pinMode(GreenLED, OUTPUT);
  pinMode(BlueLED, OUTPUT);
  pinMode(RedLED, OUTPUT);
  pinMode(Buzzer, OUTPUT);

  digitalWrite(BlueLED, HIGH);

  lcd.clear();
  lcd.print(" Access Control ");

  lcd.setCursor(0, 1);
  lcd.print("Scan Your Card>>");
}
void loop() {
  // Default state: LEDs and servo in idle position
  digitalWrite(BlueLED, HIGH);
  digitalWrite(RedLED, LOW);
  digitalWrite(GreenLED, LOW);
  noTone(Buzzer);
  servo.write(10);

  // Check for a scanned card
  if (getUID()) {
    Serial.print("UID: ");
    Serial.println(UIDCard);

    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Permission:");
    lcd.setCursor(0, 1);

    if (UIDCard == MasterTag) {
      // Access granted
      lcd.print(" Access Granted!");
      digitalWrite(GreenLED, HIGH);
      digitalWrite(BlueLED, LOW);
      digitalWrite(RedLED, LOW);

      servo.write(180); // Open servo
      for (int i = 0; i < 2; i++) {
        tone(Buzzer, 2000);
        delay(250);
        noTone(Buzzer);
        delay(250);
      }
      delay(2000); // Keep door open for 2 seconds
      servo.write(0); // Close servo
    } else {
      // Access denied
      lcd.print(" Access Denied!");
      digitalWrite(BlueLED, LOW);
      digitalWrite(GreenLED, LOW);
      tone(Buzzer, 2000);
      for (int i = 0; i < 10; i++) {
        digitalWrite(RedLED, HIGH);
        delay(250);
        digitalWrite(RedLED, LOW);
        delay(250);
      }
      noTone(Buzzer);
    }

    delay(2000);

    // Reset LCD for next scan
    lcd.clear();
    lcd.print(" Access Control ");
    lcd.setCursor(0, 1);
    lcd.print("Scan Your Card>>");
  }
}

boolean getUID() {
  // Check for a new card
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }

// Try reading the card's UID
  if (!mfrc522.PICC_ReadCardSerial()) {
    return false;
  }

  // Convert the UID to a string
  UIDCard = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    UIDCard.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
    UIDCard.concat(String(mfrc522.uid.uidByte[i], HEX));
    UIDCard.concat(" "); // Add space between bytes
  }
  UIDCard.toUpperCase();
  UIDCard.trim(); // Remove trailing space

  mfrc522.PICC_HaltA(); // Halt the card
return true; 

