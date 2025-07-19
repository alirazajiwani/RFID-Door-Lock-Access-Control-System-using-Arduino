# RFID Door Lock Access Control System using Arduino

The integration of RFID technology with the Arduino platform offers a significant advancement in access control systems. This project moves beyond traditional lock-and-key mechanisms by providing a more secure, efficient, and scalable solution. The system utilizes RFID tags, which act as digital keys, to grant access only to authorized users. It is designed to be flexible and adaptable, allowing for future expansion and the integration of new technologies. 

## Objectives

The primary goals of this project are: 

**User Identification and Authentication:** To create a reliable system for identifying and authenticating users via RFID tags. 
**Multi-Door Access Control:** To develop a comprehensive solution for managing access across multiple doors.
**Audit Log Generation:** To implement a detailed logging mechanism for all access events to ensure accountability.
**Scalability and Extensibility:** To design an adaptable system that can easily accommodate future growth.

## Key Features

- User Identification & Authentication: Recognizes and authenticates users via RFID tags.
- Multi-Door Access Control: Manages access across various entry points.
- Audit Log Generation: Logs detailed access events for accountability.
- Scalability & Extensibility: Designed to accommodate future expansions.

## How it Works
The system utilizes an RFID reader to capture unique identifiers from RFID tags. This data is sent to an Arduino microcontroller, which verifies if the tag is authorized. If authorized, the Arduino triggers an action, such as unlocking a door via a servo motor; otherwise, access is denied. The communication between the RFID tags and the reader primarily uses Amplitude Shift Keying (ASK) modulation.

## Components

- Arduino UNO: The central microcontroller.
- RFID Module: Reads RFID tags.
- MG945 Servomotor: Controls the door lock mechanism.
- 16x2 LCD with I2C Module: Displays system status and messages.
- LEDs & Buzzer: Provide visual and audible feedback for access status.
