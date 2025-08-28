#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MFRC522.h>
#include <Servo.h>

// RFID settings
#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN);

// LCD settings
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Push Button settings
#define BUTTON1_PIN 2
#define BUTTON2_PIN 3

// Servo settings
Servo servo1;
Servo servo2;
#define SERVO1_PIN 5
#define SERVO2_PIN 6

// IR Sensor settings
#define IR_SENSOR_PIN 7

// Authorized RFID UIDs
String authorizedUIDs[] = {"23c864f7", "30f36"};

void setup() {
  Serial.begin(9600);
  
  // Initialize RFID
  SPI.begin();
  rfid.PCD_Init();
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  
  // Initialize Servos
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  
  // Initialize Push Buttons
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);

  // Initialize IR Sensor
  pinMode(IR_SENSOR_PIN, INPUT);
  
  // Initial messages
  lcd.setCursor(0, 0);
  lcd.print("Scan RFID Tag");
  lcd.setCursor(0, 1);
  lcd.print("to Start");
  Serial.println('Scan rfid tag to start');
}

void loop() {
  // RFID Scanning
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    String rfidUid = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
      rfidUid += String(rfid.uid.uidByte[i], HEX);
    }
    Serial.print("RFID UID: ");
    Serial.println(rfidUid);

    // Check if the RFID UID is authorized
    bool authorized = false;
    for (String uid : authorizedUIDs) {
      if (rfidUid == uid) {
        authorized = true;
        break;
      }
    }

    if (authorized) {
      // Display authorized message on LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Authorized User"); 
      Serial.println('authorized user');
      delay(2000);

      // Product selection using buttons
      lcd.setCursor(0, 0);
      lcd.print("1:Product1");
      Serial.println('select product 1 or product 2');
      lcd.setCursor(0, 1);
      lcd.print("2:product 2");


      int selectedProduct = 0;
      while (selectedProduct == 0) {
        if (digitalRead(BUTTON1_PIN) == HIGH) {
          selectedProduct = 1;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Product1 ");
          Serial.println('selected product 1');
          lcd.setCursor(0, 1);
          lcd.print("SELECTED");
          servo1.attach(SERVO1_PIN);
          servo2.detach();

          servo1.write(0); // Adjust this to push the product
          delay(1000);
          servo1.write(90);
          delay(1000);
          servo1.writeMicroseconds(1500);
          servo1.detach();
          // Adjust this to push the product
          
        } else if (digitalRead(BUTTON2_PIN) == HIGH) {
          selectedProduct = 2;
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Product2 ");
          Serial.println('selected product 2');
          lcd.setCursor(0,1);
          lcd.print("SELECTED ");
          servo2.attach(SERVO2_PIN); // black to orange,white to red,grey to brown
          servo1.detach();
          servo2.write(0); // Adjust this to push the product
          delay(1000);
          servo2.write(90);
          delay(1000);
          servo2.writeMicroseconds(1500);
          servo2.detach();
           // Adjust this to push the product
          
        }
      }

      delay(2000);

      // Check if the product is vended using IR sensor
      lcd.setCursor(0, 1);
      lcd.print("Checking...");
      bool productVended = false;
      for (int i = 0; i < 10; i++) { // Check for 10 iterations
        if (digitalRead(IR_SENSOR_PIN) == LOW) {
          productVended = true;
          break;
        }
        delay(100);
      }

      lcd.clear();
      if (productVended) {
        lcd.setCursor(0, 0);
        lcd.print("Product Vended");
        Serial.println('Product vended');
      } else {
        lcd.setCursor(0, 0);
        lcd.print("Vending Failed");
        Serial.println('Product vending failed');
      }

      // Reset for next use
      delay(2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Scan RFID Tag");
      lcd.setCursor(0, 1);
      lcd.print("to Start");
    } else {
      // Display unauthorized message on LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Unauthorized");
      lcd.setCursor(0, 1);
      Serial.println("unauthorized user");
      lcd.print("Try Again");
      Serial.println("try again");
      delay(2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Scan RFID Tag");
      Serial.println('Scan RFID card ');
      lcd.setCursor(0, 1);
      lcd.print("to Start");
    }

    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
  }
}