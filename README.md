# Bluetooth-Controlled-LED-Matrix

This project allows you to control an LED matrix via Bluetooth. You can send commands from a Bluetooth-enabled device to adjust the display on the matrix, enabling various animations, text, and patterns. It uses an LED matrix, Bluetooth module, and microcontroller (e.g., Arduino) to interface with the hardware.

### Features:
- **Bluetooth control** for LED matrix.
- Display **custom text** or **animations**.
- Easy setup with a **compatible Bluetooth module**.

### Installation:

1. **Connect the Bluetooth module** to the microcontroller (e.g., Arduino).
2. **Wire the LED matrix** to the microcontroller.
3. **Upload the control code** to the microcontroller.
4. Use a **Bluetooth-enabled device** (smartphone, tablet, etc.) to connect and control the matrix.

### Technologies Used:
- **Bluetooth**
- **LED Matrix**
- **Microcontroller** (e.g., Arduino)

### Hardware Components:
- **Bluetooth Module** (e.g., HC-05 or HC-06)
- **LED Matrix**
- **Arduino Uno** or compatible microcontroller
- **Jumper wires** and **breadboard**

### Code:
```cpp
// Group5_Project.ino - Bluetooth-Controlled-LED-Matrix

#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

// Define hardware pins and setup
SoftwareSerial BTSerial(10, 11); // RX, TX for Bluetooth communication
Max72xxPanel matrix = Max72xxPanel(8, 9, 10, 1); // Pin setup for LED matrix

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);  // Start Bluetooth communication
  matrix.setIntensity(5); // Set matrix brightness level
}

void loop() {
  if (BTSerial.available()) {
    char command = BTSerial.read();
    
    // Example: Control the LED matrix based on Bluetooth command
    if (command == 'A') {
      displayAnimation();  // Function to display an animation
    } else if (command == 'T') {
      displayText("Hello!");  // Function to display text
    }
  }
}

void displayAnimation() {
  // Example animation code
  for (int i = 0; i < 8; i++) {
    matrix.clear();
    matrix.setPixel(i, 0, HIGH);  // Turn on LEDs in a pattern
    matrix.write();
    delay(100);
  }
}

void displayText(const char* text) {
  // Example text display code
  matrix.clear();
  matrix.setCursor(0, 0);
  matrix.print(text);
  matrix.write();
  delay(1000);
}
