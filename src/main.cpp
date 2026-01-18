#include <Arduino.h>
#include <Mouse.h>
#include <Keyboard.h>
#include "Buttons.h"
#include "Trackpad.h"

/// @brief Arduino setup function
/// @details This function initializes all required hardware modules.
///          It starts the USB HID interfaces (mouse and keyboard),
///          initializes the button handling logic and the trackpad.
void setup() {
    Mouse.begin();
    Keyboard.begin();
    initButtons();
    initTrackpad();
}

/// @brief Arduino main loop
/// @details This function is executed continuously.
///          It updates the button states, reads and processes trackpad
///          input and sends mouse movement events via USB HID.
///          The loop runs without blocking delays to ensure responsive
///          input handling.
void loop() {

    // Update button states and trigger mouse/keyboard actions
    updateButtons();

    // Read processed trackpad movement
    TrackpadProcessed p = updateTrackpad();

    // Send mouse movement only if a finger is detected
    if (p.fingerPresent) {

        // Limit movement values to valid HID range
        int8_t mx = constrain((int)p.dx, -127, 127);
        int8_t my = constrain((int)p.dy, -127, 127);

        // Send relative mouse movement
        Mouse.move(mx, my);
    }

    // Small delay to stabilize USB HID communication
    delay(1);
}
