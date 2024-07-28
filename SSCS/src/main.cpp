#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Sensor.h>
#include <IRremote.h>
#include <LiquidCrystal_I2C.h>
DHT dht(DHTPIN, DHTTYPE);
#define on  3910598400 // แก้ค่าปุ่มกดที่ 1
#define off  4077715200 // แก้ค่าปุ่มกดที่ 2

LiquidCrystal_I2C lcd(0x27,16,2);
const int IR_PIN = 8;
const int Update = 1;
const int UpdateEEPROM = 2;
const int IR = 3;
const int LCD = 4;
IRrecv irrecv(IR_PIN);
int state;
void setup() {
  Wire.begin();
  state = Update;
  lcd.begin(16, 2);
  lcd.noDisplay();
  Serial.begin(9600);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
  pinMode(LDR_pin,INPUT);
  pinMode(moisture_pin,INPUT);
  dht.begin();
  Serial.println(mois);
  Serial.println(temp);
  Serial.println(LDR);
}
 
void loop()
{
  if(state == Update){
    updateMoisture();
    updateTemp();
    updateLDR();
    Serial.print("Soil Moisture: ");
    Serial.println(mois);
    Serial.print("Temperature: ");
    Serial.println(temp);
    Serial.print("LDR: ");
    Serial.println(LDR);
    state = IR;
  }else if(state == IR){
    if (IrReceiver.decode()) {
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); // Print "old" raw data
      Serial.println(IrReceiver.decodedIRData.decodedRawData); // Print "old" raw data
      IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
      IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
      IrReceiver.resume(); // Enable receiving of the next value
      if (IrReceiver.decodedIRData.decodedRawData == on) {
        lcd.backlight();
        lcd.display();
        state = LCD;
      } else if (IrReceiver.decodedIRData.decodedRawData == off) {
        lcd.noDisplay();
        lcd.noBacklight();
        state = Update;
      }
    }
      irrecv.resume();
  }else if(state == LCD){
    lcd.clear(); // Clear the LCD screen
    lcd.setCursor(0, 0); // Set cursor to start of first line
    lcd.print("M:");
    lcd.print(mois);
    
    lcd.setCursor(0, 1); // Set cursor to start of second line
    lcd.print("Temp:");
    lcd.print(temp);
    lcd.print(" C");
    
    lcd.setCursor(8, 0); // Set cursor to start of third line
    lcd.print("LDR:");
    lcd.print(LDR);

    delay(2000); // Delay for readability (optional)
    state = Update; // Return to update state
  }
}
 