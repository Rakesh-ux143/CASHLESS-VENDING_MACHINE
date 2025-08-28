..# Cashless Vending Machine (RFID-Based)

This project implements a **cashless vending machine** using **RFID technology**.  
Instead of cash or coins, users simply scan an **RFID tag** to access items.  
The system verifies the tag against pre-registered IDs, and if valid, the vending machine dispenses the product.  
No direct payments are required — making the process **quick, secure, and convenient**.

## Features
- RFID-based access control  
- Infrared sensor for object detection  
- Push buttons for manual control  
- Contactless and hygienic vending  
- Easy to use and manage authorized users  

## Components Used
- Arduino Microcontroller  
- RFID Reader (RC522)  
- RFID Tags/Cards  
- Infrared (IR) Sensor  
- Push Buttons  
- Servo Motor / Relay for dispensing mechanism  
- Wires and Power Supply  

## How It Works
1. User scans their RFID tag.  
2. Arduino checks the tag against stored IDs.  
3. If valid, the vending mechanism activates.  
4. IR sensor ensures proper item dispensing.  
5. Push buttons can be used for manual input/control.  

## File Info
- `raki.mini_project.ino` → Main Arduino code for the project  

## Future Improvements
- Add LCD display for live status  
- Store usage logs  
- Enable IoT-based remote monitoring  

---
🚀 Developed as a **Mini Project** on RFID and sensor-based automation.
