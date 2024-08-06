
# Environmental Monitoring Project

## Overview

This project aims to create a user-friendly interface for monitoring environmental conditions over time. The system is designed to measure temperature and humidity using an Arduino Uno and display the data on an LCD screen. The data is then transmitted to a computer for further analysis and visualization using a graphical user interface (GUI) built with LabWindows/CVI.

## Components

- **Arduino Uno**: A microcontroller board used for processing and controlling the system.
- **DHT11 Sensor**: A sensor used to measure temperature and humidity.
- **16x2 LCD Display**: A screen used to display the sensor readings.
- **Breadboard**: Used for initial prototyping and connections.
- **3D Printed Enclosure**: A custom-made case to house the Arduino and sensor setup.

## How It Works

1. **Data Collection**: The Arduino collects temperature and humidity data from the DHT11 sensor.
2. **Data Transmission**: The collected data is transmitted to the computer via a serial RS-232 connection.
3. **GUI Visualization**: The LabWindows/CVI interface captures the data, allowing the user to set temperature thresholds, visualize the readings in real-time, and save the data for further analysis.

## Setup Instructions

### Hardware Setup

1. Connect the DHT11 sensor and the LCD display to the Arduino Uno as per the provided wiring diagram.
2. Place the setup on a breadboard for initial testing.
3. Once confirmed, transfer the setup into the 3D printed enclosure for a compact and stable configuration.

### Software Setup

1. **Arduino Code**: Upload the provided Arduino code to the Arduino Uno to start data collection.
2. **LabWindows/CVI Application**:
   - Open the LabWindows/CVI project.
   - Configure the COM port for serial communication.
   - Set the desired temperature thresholds.
   - Start the data collection by clicking the "Connect" button.

### Using the GUI

1. Launch the LabWindows/CVI application.
2. Enter the appropriate COM port number and temperature thresholds.
3. Click "Connect" to start receiving data from the Arduino.
4. View real-time temperature and humidity data on the GUI.
5. Save the graphs by clicking the respective save buttons.
6. Disconnect from the Arduino when finished by clicking "Disconnect".

## Key Algorithms and Functions

### `ConnectFunc`

- Establishes RS-232 communication with the selected COM port.
- Key Functions:
  - `GetCtrlVal`: Stores the COM port and temperature threshold values.
  - `OpenComConfig`: Opens the selected COM port.
  - `MessagePopup`: Displays connection status messages.
  - `SetCtrlAttribute`: Updates the status indicator based on connection status.
  - `FlushInQ`: Clears existing data from the COM port.
  - `InstallComCallback`: Installs a callback function to handle incoming data.

### `DisconnectFunc`

- Terminates the RS-232 communication with the Arduino.
- Key Functions:
  - `CloseCom`: Closes the COM port.
  - `SetCtrlVal`: Resets the display bars for temperature and humidity.
  - `SetCtrlAttribute`: Re-enables the "Connect" button and disables the "Disconnect" button.

### `Load_Data`

- Continuously receives and processes data from the Arduino.
- Key Functions:
  - `ComRd`: Reads data from the COM port.
  - `Sscanf`: Parses the received data to extract temperature and humidity values.
  - `PlotY`: Plots the temperature and humidity data in real-time.

### `Save_Humi_GraphFunc` and `Save_Temp_GraphFunc`

- Allows the user to save the temperature and humidity graphs as PNG files.
- Key Functions:
  - `GetCtrlDisplayBitmap`: Captures the bitmap of the graph.
  - `SaveBitmapToPNGFile`: Saves the bitmap as a PNG file.
  - `DiscardBitmap`: Frees the bitmap resources after saving.

## Challenges

- Ensuring stable communication between the Arduino and the computer.
- Correctly parsing and displaying real-time data.
- Designing an intuitive and user-friendly GUI.

## Gallery

### Initial Breadboard Setup
![Initial Breadboard Setup](path/to/image1.png)

### 3D Printed Enclosure
![3D Printed Enclosure](path/to/image2.png)

### Final Assembly
![Final Assembly](path/to/image3.png)

