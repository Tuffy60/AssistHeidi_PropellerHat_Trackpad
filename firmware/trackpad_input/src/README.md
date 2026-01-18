# Assistive Trackpad & Button Input Module (Arduino / USB HID)

This repository contains the implementation of an **assistive input system**
developed as part of the **ASSIST HEIDI** project.
The system is designed for people with **motor impairments affecting hands,
arms or overall body coordination** and provides an alternative way to
interact with a computer using minimal and controlled movements.

The device behaves as a standard USB mouse and keyboard and does not require
any special drivers on the host system.

---

## Overview

The system consists of the following components:

- A Cirque capacitive trackpad used as a pointing device  
- Two hardware buttons configurable as mouse or keyboard inputs  
- A USB HID interface exposing mouse and keyboard functionality  

The implementation focuses on:

- Accessible and low-fatigue interaction  
- Stable and predictable cursor movement  
- Suppression of involuntary micro movements  
- Deterministic behavior without automatic guessing  
- Clear separation of software modules  

---

## Features

- USB HID mouse and keyboard support  
- Configurable hardware buttons  
- Trackpad movement with deadzone, acceleration and smoothing  
- Controlled edge scrolling  
- Explicit rotation modes (0°, 90°, 180°, 270°)  
- Non-blocking input handling  
- Fully documented and modular code structure  

---

## Project Structure
.
├── main.cpp # Application entry point
├── trackpad.h # Trackpad interface and data structures
├── trackpad.cpp # Trackpad processing logic
├── buttons.h # Button configuration and action definitions
├── buttons.cpp # Button handling and HID actions
├── cirque.h # Cirque trackpad driver (external)
├── cirque.cpp # Cirque trackpad driver (external)
└── README.md


---

## Hardware Requirements

- Arduino-compatible microcontroller with native USB support  
  (e.g. RP2040, ATmega32U4, etc.)
- Cirque capacitive trackpad
- Two momentary push buttons
- USB connection to host PC

---

## Software Requirements

- Arduino framework
- USB HID support (`Mouse.h`, `Keyboard.h`)
- Compatible board package for the target microcontroller

---

### Supported Mouse Actions

The hardware buttons can be mapped to:

- Left mouse click  
- Right mouse click  
- Middle mouse click  
- Back and forward navigation buttons  

These actions enable basic system interaction without requiring precise or
fast finger movements.

### Supported Keyboard Actions

Buttons can also be mapped to keyboard inputs, including:

- Alphanumeric keys (e.g. W, A, S, D)  
- Arrow keys (Up, Down, Left, Right)  
- Modifier keys (Shift, Ctrl, Alt)  
- Common control keys (Space, Enter, Escape, Tab)  
- Function keys (F1 – F12)  

Each button generates a **press event when activated** and a **release event
when released**, ensuring stable and predictable USB HID behavior.

---

## Configuration Overview

### Button Configuration

Button behavior is configured in `buttons.h` using preprocessor definitions:

cpp
#define BUTTON1_ACTION   ACT_MOUSE_LEFT
#define BUTTON2_ACTION   ACT_MOUSE_RIGHT

Changing these values assigns a different mouse or keyboard action to the
corresponding hardware button.

This allows caregivers or developers to adapt the device to individual user
needs without modifying the button logic itself.

## Trackpad Movement and Accessibility Tuning

The trackpad behavior can be adjusted via `#define` parameters in
`trackpad.cpp` to match individual motor abilities.

Key parameters include:

- `SENS` – overall cursor movement speed  
- `SMOOTHING` – balance between responsiveness and stability  
- `DEADZONE_CENTER` – suppression of involuntary micro movements  
- `EDGE_SPEED_BASE` / `EDGE_SPEED_MAX` – controlled edge scrolling  

All parameters are documented directly in the source code.

---

## Assistive Design Principles

- Focus on stability rather than raw speed  
- Deterministic input behavior without automatic guessing  
- Minimal required movement for common actions  
- Adaptable configuration for different physical limitations  
- Designed for long-term and everyday use  

This module represents the technical implementation of the assistive input
concept developed within the **ASSIST HEIDI** project.

---

## Usage

1. Flash the firmware to the target microcontroller  
2. Connect the device to a PC via USB  
3. The device appears as a standard mouse and keyboard  
4. Use the trackpad for cursor movement  
5. Use the hardware buttons for mouse or keyboard actions  

No additional drivers are required.

---

This module was implemented and documented as part of an academic project.

Propeller-Controller
