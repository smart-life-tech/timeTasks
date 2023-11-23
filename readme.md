
# BCCode Processor and LED Controller

## Overview

This Arduino project implements BCCode encoding and decoding, LED transmission, and command message handling. It allows users to transmit messages using BCCode, control LEDs, and execute specific commands.

## Features

- **BCCode Encoding/Decoding:** Convert ASCII text to BCCode and vice versa.
- **LED Transmission:** Visualize BCCode transmission through LEDs.
- **Command Handling:** Respond to specific command messages.

## How to Use

1. **BCCode Encoding:**
   - Send ASCII text via Serial, prepended with '*', '?', or '<'.
   - Receive BCCode-encoded message and visualize it on the green LED.

2. **BCCode Decoding:**
   - Send BCCode via Serial, starting with '*', '?', or '<'.
   - Receive the decoded ASCII message and visualize it on the blue LED.

3. **Command Messages:**
   - Send command messages starting with 'B', 'P', 'C', or 'B'.
   - Execute actions based on the command type.

4. **LED Flashing (BB Command):**
   - Use 'BB' followed by 4 decimal digits.
   - LEDs flash synchronously based on the numerical value.

## Setup

1. Connect Arduino and upload the sketch.
2. Adjust potentiometer for LED transmission speed.
3. Interact via Serial Monitor.

## Commands

- **BxB:**
  - If x is even, read potentiometer and transmit as BCCode.

- **PBxxx:**
  - Sum three decimal digits; if < 10, transmit IR receiver value as 'HIGH'/'LOW'; else, 'UNKNOWN'.

- **BCxxx:**
  - Set red LED brightness to 3-digit number; reset after 250ms.

- **BBxxxx:**
  - Flash LEDs based on 4-digit value.



### Challenges and Notes

1. **BCCode Decoding:**
   - Initial issues with the `decodeFromBCCode` function not correctly handling the BCCode format.
   - Debugging involved checking the substring extraction and character comparison.

2. **LED Flashing (BB Command):**
   - Understanding the synchronization of LED flashes based on the 4-digit value.
   - Iterative testing and adjustments to achieve the desired flashing pattern.

3. **Serial Communication:**
   - Serial input reading and handling messages required careful attention.
   - Ensuring that commands and BCCode messages are correctly identified.

4. **Code Structure:**
   - Refactoring the code to improve readability and organization.
   - Ensuring functions are modular and easy to understand.

### Self-Assessment

#### Completed Tasks:

1. **BCCode Encoding/Decoding:** Successfully implemented and tested.
2. **LED Transmission:** Visualized BCCode on green/blue LEDs after encoding/decoding.
3. **Command Handling:** Executed actions based on command messages.
4. **LED Flashing (BB Command):** Implemented synchronous LED flashes based on the 4-digit value.

#### Justification for the Mark:

- **Understanding of BCCode Encoding/Decoding:** Demonstrated by successful BCCode transmission and reception.
- **Command Handling:** Efficiently processed command messages, considering various scenarios.
- **LED Transmission:** Visualized BCCode on LEDs, adjusting transmission speed based on the potentiometer.
- **Challenges Addressed:** Identified challenges in decoding, LED flashing, and serial communication, addressing them through debugging and iterative improvements.
- **Code Structure:** Ensured code readability and modularity, facilitating easier maintenance.

Considering the successful implementation of core features, overcoming challenges, and maintaining clean code, I would award myself a mark of 85%. Room for improvement lies in handling unexpected scenarios more gracefully and providing more detailed comments in the code.
---

