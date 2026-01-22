# ASSIST HEIDI – Assistive Input System

ASSIST HEIDI is an assistive input system developed to provide alternative and accessible input devices for users who experience difficulties using standard mouse and keyboard setups.  
The project focuses on reducing physical strain while maintaining precise and responsive control, especially for fast-paced applications such as shooter games.

This repository contains the complete firmware, hardware design files, and documentation created as part of the ASSIST HEIDI project.

---

## Project Background

The project was developed in close collaboration with a user who experiences rapid fatigue and reduced precision when using conventional input devices.  
Standard gaming peripherals often require continuous hand positioning, repetitive movements, and frequent button presses, which can significantly limit comfort and usability over longer sessions.

ASSIST HEIDI aims to address these challenges by offering customizable and modular input solutions that adapt to individual needs rather than forcing the user to adapt to the device.

---

## Features

- Assistive **trackpad-based controller** for precise cursor movement
- **Two easily accessible buttons** for mouse or keyboard actions
- **Seven-switch mini keyboard controller** with fully customizable mappings
- Adjustable firmware parameters:
  - cursor speed
  - sensitivity
  - rotation (0°, 90°, 180°, 270°)
- Standard **USB Human Interface Device (HID)** behavior
- Plug & Play – no additional drivers required
- Platform independent (Windows, macOS, Linux)

---

## Repository Structure

- [firmware/trackpad_input](firmware/trackpad_input/) – Assistive trackpad and button input module
- [firmware/Keyboard_Switch](firmware/Keyboard_Switch/) – Assistive Keyboard for game controls  
- [hardware/3D_prints](hardware/3D_print/) – 3D printable parts

---
## Firmware

The firmware is implemented using the **Arduino framework** and runs on the **Raspberry Pi Pico W**.  
All configuration parameters are defined directly in the source code:

- `.h` files contain configurable mappings and feature definitions  
- `.cpp` files control behavior such as sensitivity, speed, and smoothing  

The device is recognized by the host system as a standard mouse and keyboard using USB HID.

---

## Hardware

The controllers are built using off-the-shelf components and 3D-printed enclosures.  
No specialized manufacturing tools are required, making the system easy to reproduce and modify.

3D printing files are provided in the `hardware/3D_print` directory.

---

## Documentation

A detailed project documentation including:
- problem description
- solution overview
- materials and costs
- technical details
- assembly instructions

is available as a PDF in this repository:

📄 [PropellerHat-Controller_Documentation.pdf](PropellerHat-Controller_Documentation.pdf)

---

## License

This project is released under the **MIT License**.  
You are free to use, modify, and distribute the code and design files.

---

## Contributors

- Ates Tufan  
- Jakob Brandstetter  
- Matteo Fachino

---

## Acknowledgements

This project was developed as part of the **ASSIST HEIDI** initiative and builds upon previous assistive controller concepts.  
Special thanks to the user involved in the co-creation process for valuable feedback and continuous testing.
