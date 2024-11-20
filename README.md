# Bluetooth-Controlled-LED-Matrix

This project enables you to control an LED matrix via Bluetooth. You can send commands from a Bluetooth-enabled device to adjust the display on the matrix, enabling various animations, text, and patterns. The system uses an LED matrix, Bluetooth module, and an Arduino microcontroller to interface with the hardware.

## Features:
- **Bluetooth control** for LED matrix.
- Display **custom text** or **animations**.
- Supports **Automatic** and **Manual** modes.
- Easy setup with a **compatible Bluetooth module** (HC-05 or HC-06).

## Basic Workflow:

### 1. Hardware Setup:
   - Connect the **Bluetooth module** (HC-05) to your **Arduino**. Use the **TX** and **RX** pins for communication.
   - Connect the **LED matrix** to your Arduino according to the wiring diagram.
   - Connect any necessary sensors, such as the **LM35 temperature sensor** or **RTC DS1307** for date/time.

### 2. Upload the Code:
   - Open the Arduino IDE and upload the provided code to your Arduino board.

### 3. Bluetooth Setup:
   - Turn on **Bluetooth** on your mobile device and search for the **Bluetooth module** (e.g., HC-05).
   - Pair with the device. The default PIN is usually **1234** or **0000**.

### 4. Control the LED Matrix:
   - Use a Bluetooth-enabled device (smartphone/tablet) to connect and control the LED matrix.
   - You can send commands to display custom text or switch between Automatic and Manual modes.

## Technologies Used:
- **Bluetooth** (e.g., HC-05 module)
- **LED Matrix** (e.g., 8x32 matrix)
- **Microcontroller** (e.g., Arduino Uno)
- **Temperature Sensor** (e.g., LM35)
- **RTC** (e.g., DS1307)

## Hardware Components:
- **Bluetooth Module** (e.g., HC-05 or HC-06)
- **LED Matrix** (e.g., 8x32)
- **Arduino Uno**
- **LM35 Temperature Sensor**
- **RTC DS1307** (optional)
- **Jumper wires and breadboard**

## Code Structure:

```cpp
// Group5_Project.ino - Bluetooth-Controlled-LED-Matrix

// Global variable declarations
char daysOfTheWeek[7][12] = { "Su", "Mo", "Tu", "We", "Th", "Fr", "Sa" }; // Days of the week
const int bluetoothTx = 2; // Bluetooth TX pin
const int bluetoothRx = 3; // Bluetooth RX pin
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx); // SoftwareSerial object for Bluetooth communication
const int LM35Pin = A0; // Temperature sensor pin
char output[200]; // Output string for display
char Temp[200]; // Temperature string
char outputStr[200]; // Custom text string
#define EEPROM_ADDRESS 0 // EEPROM address
#define EEPROM_SIZE 200 // EEPROM size
int tmp; // Temporary variable for time comparison
int mode = 0; // Mode (0 = Automatic, 1 = Manual)
int style = 1; // Display style (1 = Style1, 2 = Style2)
char serialData[200]; // Buffer for Serial input
int serialDataIndex = 0; // Index for Serial buffer

// setup() - Initializes the system, sets up the display, RTC, and Bluetooth connection.
void setup();

// loop() - Main function that runs continuously, reads input from Bluetooth or Serial, 
// updates the temperature, and handles the display and command processing.
void loop();

// processCommand(String command) - Processes commands received from Bluetooth or Serial input.
void processCommand(String command);

// writeToEEPROM(const char* data, int length) - Writes data to EEPROM for persistent storage.
void writeToEEPROM(const char* data, int length);

// readFromEEPROM(char* buffer, int length) - Reads data from EEPROM and stores it in a buffer.
void readFromEEPROM(char* buffer, int length);

# Bluetooth-Controlled-LED-Matrix

This project enables you to control an LED matrix via Bluetooth. You can send commands from a Bluetooth-enabled device to adjust the display on the matrix, enabling various animations, text, and patterns. The system uses an LED matrix, Bluetooth module, and an Arduino microcontroller to interface with the hardware.

## Features:
- **Bluetooth control** for LED matrix.
- Display **custom text** or **animations**.
- Supports **Automatic** and **Manual** modes.
- Easy setup with a **compatible Bluetooth module** (HC-05 or HC-06).

## Basic Workflow:

### 1. Hardware Setup:
   - Connect the **Bluetooth module** (HC-05) to your **Arduino**. Use the **TX** and **RX** pins for communication.
   - Connect the **LED matrix** to your Arduino according to the wiring diagram.
   - Connect any necessary sensors, such as the **LM35 temperature sensor** or **RTC DS1307** for date/time.

### 2. Upload the Code:
   - Open the Arduino IDE and upload the provided code to your Arduino board.

### 3. Bluetooth Setup:
   - Turn on **Bluetooth** on your mobile device and search for the **Bluetooth module** (e.g., HC-05).
   - Pair with the device. The default PIN is usually **1234** or **0000**.

### 4. Control the LED Matrix:
   - Use a Bluetooth-enabled device (smartphone/tablet) to connect and control the LED matrix.
   - You can send commands to display custom text or switch between Automatic and Manual modes.

## Technologies Used:
- **Bluetooth** (e.g., HC-05 module)
- **LED Matrix** (e.g., 8x32 matrix)
- **Microcontroller** (e.g., Arduino Uno)
- **Temperature Sensor** (e.g., LM35)
- **RTC** (e.g., DS1307)

## Hardware Components:
- **Bluetooth Module** (e.g., HC-05 or HC-06)
- **LED Matrix** (e.g., 8x32)
- **Arduino Uno**
- **LM35 Temperature Sensor**
- **RTC DS1307** (optional)
- **Jumper wires and breadboard**

## Code Structure:

```cpp
// Group5_Project.ino - Bluetooth-Controlled-LED-Matrix

// Global variable declarations
char daysOfTheWeek[7][12] = { "Su", "Mo", "Tu", "We", "Th", "Fr", "Sa" }; // Days of the week
const int bluetoothTx = 2; // Bluetooth TX pin
const int bluetoothRx = 3; // Bluetooth RX pin
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx); // SoftwareSerial object for Bluetooth communication
const int LM35Pin = A0; // Temperature sensor pin
char output[200]; // Output string for display
char Temp[200]; // Temperature string
char outputStr[200]; // Custom text string
#define EEPROM_ADDRESS 0 // EEPROM address
#define EEPROM_SIZE 200 // EEPROM size
int tmp; // Temporary variable for time comparison
int mode = 0; // Mode (0 = Automatic, 1 = Manual)
int style = 1; // Display style (1 = Style1, 2 = Style2)
char serialData[200]; // Buffer for Serial input
int serialDataIndex = 0; // Index for Serial buffer

// setup() - Initializes the system, sets up the display, RTC, and Bluetooth connection.
void setup();

// loop() - Main function that runs continuously, reads input from Bluetooth or Serial, 
// updates the temperature, and handles the display and command processing.
void loop();

// processCommand(String command) - Processes commands received from Bluetooth or Serial input.
void processCommand(String command);

// writeToEEPROM(const char* data, int length) - Writes data to EEPROM for persistent storage.
void writeToEEPROM(const char* data, int length);

// readFromEEPROM(char* buffer, int length) - Reads data from EEPROM and stores it in a buffer.
void readFromEEPROM(char* buffer, int length);
```
## Potential Improvements
- Cloud data storage
- Real-time attendance tracking
- Multiple authentication methods

## Troubleshooting
- Check wire connections
- Verify library installations
- Ensure proper power supply

## Contributors
-  Lê Văn Tiến
-  Lưu Thùy Dương
-  Huỳnh Ngọc Kỳ
-  Huỳnh NguyTrân
