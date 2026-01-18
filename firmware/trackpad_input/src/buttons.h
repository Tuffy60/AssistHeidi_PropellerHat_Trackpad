#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>
#include <Keyboard.h>

/// Button 1 action configuration
/// Change this value to assign a different mouse or keyboard action
/// Example: ACT_MOUSE_LEFT, ACT_KEYBOARD_W, ACT_KEYBOARD_SPACE
#define BUTTON1_ACTION   ACT_MOUSE_LEFT

/// Button 2 action configuration
/// Change this value to assign a different mouse or keyboard action
#define BUTTON2_ACTION   ACT_MOUSE_RIGHT

/// GPIO pin number for button 1
/// The pin is configured as INPUT_PULLUP
#define BUTTON1_PIN   0

/// GPIO pin number for button 2
/// The pin is configured as INPUT_PULLUP
#define BUTTON2_PIN   1

/// @brief Enumeration of all supported button actions
/// @details This enum defines all possible actions that can be triggered
///          by a hardware button. Actions include mouse buttons and
///          keyboard keys. The enum is used to configure button behavior
///          without changing the button handling logic.
enum ButtonAction {

    /// No action assigned
    ACT_NONE = 0,

    /// Mouse left button
    ACT_MOUSE_LEFT,

    /// Mouse right button
    ACT_MOUSE_RIGHT,

    /// Mouse middle button
    ACT_MOUSE_MIDDLE,

    /// Mouse back button
    ACT_MOUSE_BACK,

    /// Mouse forward button
    ACT_MOUSE_FORWARD,

    /// Keyboard space key
    ACT_KEYBOARD_SPACE,

    /// Keyboard enter key
    ACT_KEYBOARD_ENTER,

    /// Keyboard escape key
    ACT_KEYBOARD_ESCAPE,

    /// Keyboard tab key
    ACT_KEYBOARD_TAB,

    /// Keyboard W key
    ACT_KEYBOARD_W,

    /// Keyboard A key
    ACT_KEYBOARD_A,

    /// Keyboard S key
    ACT_KEYBOARD_S,

    /// Keyboard D key
    ACT_KEYBOARD_D,

    /// Keyboard arrow up key
    ACT_KEYBOARD_UP,

    /// Keyboard arrow down key
    ACT_KEYBOARD_DOWN,

    /// Keyboard arrow left key
    ACT_KEYBOARD_LEFT,

    /// Keyboard arrow right key
    ACT_KEYBOARD_RIGHT,

    /// Keyboard shift modifier key
    ACT_KEYBOARD_SHIFT,

    /// Keyboard control modifier key
    ACT_KEYBOARD_CTRL,

    /// Keyboard alt modifier key
    ACT_KEYBOARD_ALT,

    /// Keyboard function key F1
    ACT_KEYBOARD_F1,

    /// Keyboard function key F2
    ACT_KEYBOARD_F2,

    /// Keyboard function key F3
    ACT_KEYBOARD_F3,

    /// Keyboard function key F4
    ACT_KEYBOARD_F4,

    /// Keyboard function key F5
    ACT_KEYBOARD_F5,

    /// Keyboard function key F6
    ACT_KEYBOARD_F6,

    /// Keyboard function key F7
    ACT_KEYBOARD_F7,

    /// Keyboard function key F8
    ACT_KEYBOARD_F8,

    /// Keyboard function key F9
    ACT_KEYBOARD_F9,

    /// Keyboard function key F10
    ACT_KEYBOARD_F10,

    /// Keyboard function key F11
    ACT_KEYBOARD_F11,

    /// Keyboard function key F12
    ACT_KEYBOARD_F12
};

/// @brief Initializes the hardware buttons
/// @details This function configures the button GPIO pins
///          as input pins with internal pull-up resistors.
///          It must be called once during system startup.
void initButtons();

/// @brief Updates button states and executes actions
/// @details This function reads the current button states,
///          detects press and release events and triggers
///          the configured mouse or keyboard actions.
///          It is non-blocking and should be called continuously.
void updateButtons();

/// @brief Executes the press action of a button
/// @param action The ButtonAction to execute
/// @details This function is used internally to trigger
///          mouse or keyboard press events.
void executePressAction(ButtonAction action);

/// @brief Executes the release action of a button
/// @param action The ButtonAction to release
/// @details This function is used internally to release
///          mouse or keyboard actions.
void executeReleaseAction(ButtonAction action);

#endif
