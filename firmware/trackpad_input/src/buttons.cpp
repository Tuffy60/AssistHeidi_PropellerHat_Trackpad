#include "Buttons.h"
#include <Mouse.h>
#include <Keyboard.h>

/// @brief Executes the press action for a configured button
/// @param act ButtonAction defining which mouse or keyboard action to trigger
/// @details This function maps a logical ButtonAction to the corresponding
///          USB HID press event. It supports mouse buttons and keyboard keys.
void executePressAction(ButtonAction act) {
    switch (act) {

        case ACT_MOUSE_LEFT:    Mouse.press(MOUSE_LEFT); break;
        case ACT_MOUSE_RIGHT:   Mouse.press(MOUSE_RIGHT); break;
        case ACT_MOUSE_MIDDLE:  Mouse.press(MOUSE_MIDDLE); break;
        case ACT_MOUSE_BACK:    Mouse.press(4); break;
        case ACT_MOUSE_FORWARD: Mouse.press(5); break;

        case ACT_KEYBOARD_SPACE:   Keyboard.press(' '); break;
        case ACT_KEYBOARD_ENTER:   Keyboard.press(KEY_RETURN); break;
        case ACT_KEYBOARD_ESCAPE:  Keyboard.press(KEY_ESC); break;
        case ACT_KEYBOARD_TAB:     Keyboard.press(KEY_TAB); break;

        case ACT_KEYBOARD_W: Keyboard.press('w'); break;
        case ACT_KEYBOARD_A: Keyboard.press('a'); break;
        case ACT_KEYBOARD_S: Keyboard.press('s'); break;
        case ACT_KEYBOARD_D: Keyboard.press('d'); break;

        case ACT_KEYBOARD_UP:    Keyboard.press(KEY_UP_ARROW); break;
        case ACT_KEYBOARD_DOWN:  Keyboard.press(KEY_DOWN_ARROW); break;
        case ACT_KEYBOARD_LEFT:  Keyboard.press(KEY_LEFT_ARROW); break;
        case ACT_KEYBOARD_RIGHT: Keyboard.press(KEY_RIGHT_ARROW); break;

        case ACT_KEYBOARD_SHIFT: Keyboard.press(KEY_LEFT_SHIFT); break;
        case ACT_KEYBOARD_CTRL:  Keyboard.press(KEY_LEFT_CTRL); break;
        case ACT_KEYBOARD_ALT:   Keyboard.press(KEY_LEFT_ALT); break;

        case ACT_KEYBOARD_F1:  Keyboard.press(KEY_F1); break;
        case ACT_KEYBOARD_F2:  Keyboard.press(KEY_F2); break;
        case ACT_KEYBOARD_F3:  Keyboard.press(KEY_F3); break;
        case ACT_KEYBOARD_F4:  Keyboard.press(KEY_F4); break;
        case ACT_KEYBOARD_F5:  Keyboard.press(KEY_F5); break;
        case ACT_KEYBOARD_F6:  Keyboard.press(KEY_F6); break;
        case ACT_KEYBOARD_F7:  Keyboard.press(KEY_F7); break;
        case ACT_KEYBOARD_F8:  Keyboard.press(KEY_F8); break;
        case ACT_KEYBOARD_F9:  Keyboard.press(KEY_F9); break;
        case ACT_KEYBOARD_F10: Keyboard.press(KEY_F10); break;
        case ACT_KEYBOARD_F11: Keyboard.press(KEY_F11); break;
        case ACT_KEYBOARD_F12: Keyboard.press(KEY_F12); break;

        default: break;
    }
}

/// @brief Executes the release action for a configured button
/// @param act ButtonAction defining which mouse or keyboard action to release
/// @details This function maps a logical ButtonAction to the corresponding
///          USB HID release event. It must be called after a press action
///          to ensure correct button and key states.
void executeReleaseAction(ButtonAction act) {
    switch (act) {

        case ACT_MOUSE_LEFT:    Mouse.release(MOUSE_LEFT); break;
        case ACT_MOUSE_RIGHT:   Mouse.release(MOUSE_RIGHT); break;
        case ACT_MOUSE_MIDDLE:  Mouse.release(MOUSE_MIDDLE); break;
        case ACT_MOUSE_BACK:    Mouse.release(4); break;
        case ACT_MOUSE_FORWARD: Mouse.release(5); break;

        case ACT_KEYBOARD_SPACE:   Keyboard.release(' '); break;
        case ACT_KEYBOARD_ENTER:   Keyboard.release(KEY_RETURN); break;
        case ACT_KEYBOARD_ESCAPE:  Keyboard.release(KEY_ESC); break;
        case ACT_KEYBOARD_TAB:     Keyboard.release(KEY_TAB); break;

        case ACT_KEYBOARD_W: Keyboard.release('w'); break;
        case ACT_KEYBOARD_A: Keyboard.release('a'); break;
        case ACT_KEYBOARD_S: Keyboard.release('s'); break;
        case ACT_KEYBOARD_D: Keyboard.release('d'); break;

        case ACT_KEYBOARD_UP:    Keyboard.release(KEY_UP_ARROW); break;
        case ACT_KEYBOARD_DOWN:  Keyboard.release(KEY_DOWN_ARROW); break;
        case ACT_KEYBOARD_LEFT:  Keyboard.release(KEY_LEFT_ARROW); break;
        case ACT_KEYBOARD_RIGHT: Keyboard.release(KEY_RIGHT_ARROW); break;

        case ACT_KEYBOARD_SHIFT: Keyboard.release(KEY_LEFT_SHIFT); break;
        case ACT_KEYBOARD_CTRL:  Keyboard.release(KEY_LEFT_CTRL); break;
        case ACT_KEYBOARD_ALT:   Keyboard.release(KEY_LEFT_ALT); break;

        case ACT_KEYBOARD_F1:  Keyboard.release(KEY_F1); break;
        case ACT_KEYBOARD_F2:  Keyboard.release(KEY_F2); break;
        case ACT_KEYBOARD_F3:  Keyboard.release(KEY_F3); break;
        case ACT_KEYBOARD_F4:  Keyboard.release(KEY_F4); break;
        case ACT_KEYBOARD_F5:  Keyboard.release(KEY_F5); break;
        case ACT_KEYBOARD_F6:  Keyboard.release(KEY_F6); break;
        case ACT_KEYBOARD_F7:  Keyboard.release(KEY_F7); break;
        case ACT_KEYBOARD_F8:  Keyboard.release(KEY_F8); break;
        case ACT_KEYBOARD_F9:  Keyboard.release(KEY_F9); break;
        case ACT_KEYBOARD_F10: Keyboard.release(KEY_F10); break;
        case ACT_KEYBOARD_F11: Keyboard.release(KEY_F11); break;
        case ACT_KEYBOARD_F12: Keyboard.release(KEY_F12); break;

        default: break;
    }
}

/// @brief Initializes the hardware button inputs
/// @details This function configures the button GPIO pins as inputs
///          with internal pull-up resistors. It must be called once
///          during system startup.
void initButtons() {
    pinMode(BUTTON1_PIN, INPUT_PULLUP);
    pinMode(BUTTON2_PIN, INPUT_PULLUP);
}

/// @brief Updates button states and triggers actions
/// @details This function reads the current button states and detects
///          rising and falling edges. On a press event, the configured
///          press action is executed. On a release event, the corresponding
///          release action is executed. The function is non-blocking and
///          should be called continuously in the main loop.
void updateButtons() {

    static bool last1 = HIGH;
    static bool last2 = HIGH;

    bool b1 = digitalRead(BUTTON1_PIN);
    bool b2 = digitalRead(BUTTON2_PIN);

    // Button 1 press detection
    if (b1 == LOW && last1 == HIGH) {
        executePressAction(BUTTON1_ACTION);
    }

    // Button 1 release detection
    if (b1 == HIGH && last1 == LOW) {
        executeReleaseAction(BUTTON1_ACTION);
    }

    // Button 2 press detection
    if (b2 == LOW && last2 == HIGH) {
        executePressAction(BUTTON2_ACTION);
    }

    // Button 2 release detection
    if (b2 == HIGH && last2 == LOW) {
        executeReleaseAction(BUTTON2_ACTION);
    }

    last1 = b1;
    last2 = b2;
}
