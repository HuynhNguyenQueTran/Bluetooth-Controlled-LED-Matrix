#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"
#include <SoftwareSerial.h>
#include <Servo.h>
#include <EEPROM.h>


#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define CS_PIN 10
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);


RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = { "Su", "Mo", "Tu", "We", "Th", "Fr", "Sa" };
const int bluetoothTx = 2;
const int bluetoothRx = 3;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
const int LM35Pin = A0;


char output[200];
char Temp[200];


char outputStr[200];
#define EEPROM_ADDRESS 0
#define EEPROM_SIZE 200
int tmp;
int mode = 0;
int style = 1;




char serialData[200];
int serialDataIndex = 0;


void setup() {
  Serial.begin(9600);
  myDisplay.begin();
  myDisplay.setIntensity(4);
  myDisplay.displayClear();




  if (!rtc.begin()) {
    Serial.print("Couldn't find RTC");
    while (1)
      ;
  }


  if (!rtc.isrunning()) {
    Serial.print("RTC is NOT running!");
    Serial.println();
  }
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  bluetooth.begin(9600);
  readFromEEPROM(outputStr, EEPROM_SIZE);
}


void loop() {
  //Reading time and date
  DateTime now = rtc.now();


  // Check if data is available from Bluetooth
  if (bluetooth.available()) {
    String command = bluetooth.readStringUntil('\n');
    processCommand(command);
  }


  // Check if data is available from Serial
  if (Serial.available()) {
    char receivedChar = Serial.read();


    if (receivedChar == '\n') {
      serialData[serialDataIndex] = '\0';  // Null-terminate the string
      processCommand(serialData);
      serialDataIndex = 0;  // Reset index for next message
    } else {
      if (serialDataIndex < 199) {  // Ensure buffer overflow protection
        serialData[serialDataIndex++] = receivedChar;
      }
    }
  }


  //Reading temp
  int reading = analogRead(LM35Pin);
  float voltage = reading * 5.0 / 1024.0;
  int temp = int(voltage * 100.0);


  if (mode == 0) {
    sprintf(output, "%dC - %02d:%02d - %s,%02d.%02d.%02d", temp, now.hour(), now.minute(), daysOfTheWeek[now.dayOfTheWeek()], now.day(), now.month(), now.year() % 100);
    if (tmp != now.second()) {
      Serial.println(output);
      bluetooth.println(output);
      tmp = now.second();
    }
  }


  if (myDisplay.displayAnimate()) {
    myDisplay.displayReset();
    if (mode == 0) {
      if (style == 1) {
        myDisplay.displayText(output, PA_CENTER, 0, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
      } else {
        // myDisplay.displayText(output, PA_CENTER, 0, 0, PA_OPENING, PA_OPENING);
        myDisplay.displayText(output, PA_CENTER, 0, 0, PA_SCROLL_RIGHT, PA_SCROLL_RIGHT);
      }
    } else {
      if (style == 1) {
        myDisplay.displayText(outputStr, PA_CENTER, 0, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
      } else {
        myDisplay.displayText(outputStr, PA_CENTER, 0, 0, PA_SCROLL_RIGHT, PA_SCROLL_RIGHT);
      }
    }
  }
  delay(150);
}


void processCommand(String command) {
  if (command == "Auto") {
    Serial.println("Mode Automatic");
    bluetooth.println("Mode Automatic");
    mode = 0;
  } else if (command == "Manual") {
    mode = 1;
    delay(500);
    Serial.println("Mode Manual");
    Serial.print("Custom Text: ");
    Serial.println(outputStr);
    bluetooth.println("Mode Manual");
    bluetooth.print("Custom Text: ");
    bluetooth.println(outputStr);
  } else {
    if (mode == 0) {
      if (command == "Style1" || command == "Style2") {
        if (command == "Style1") {
          Serial.println("Style1");
          style = 1;
        } else {
          Serial.println("Style2");
          style = 2;
        }
      } else {
        Serial.println("Enter Auto/Manual!");
        bluetooth.println("Enter Auto / Manual !");
      }
    } else {
      if (command == "Style1" || command == "Style2") {
        if (command == "Style1") {
          Serial.println("Style1");
          style = 1;
        } else {
          Serial.println("Style2");
          style = 2;
        }
      } else {
        strcpy(outputStr, command.c_str());
        writeToEEPROM(outputStr, strlen(outputStr));
        Serial.print("Custom Text Updated: ");
        Serial.println(outputStr);
        bluetooth.print("Custom Text Updated: ");
        bluetooth.println(outputStr);
      }
    }
  }
}


void writeToEEPROM(const char* data, int length) {
  for (int i = 0; i < length; ++i) {
    EEPROM.write(EEPROM_ADDRESS + i, data[i]);
    delay(5);
  }
  for (int i = length; i < 255; ++i) {
    EEPROM.write(EEPROM_ADDRESS + i, '\0');
    delay(5);
  }
}


void readFromEEPROM(char* buffer, int length) {
  for (int i = 0; i < length; ++i) {
    buffer[i] = EEPROM.read(EEPROM_ADDRESS + i);
  }
  buffer[length] = '\0';  // Null-terminate the string
}




