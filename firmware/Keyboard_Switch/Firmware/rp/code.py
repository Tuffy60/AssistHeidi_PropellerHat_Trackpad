import board
import digitalio
import time
import usb_hid
from adafruit_hid.keyboard import Keyboard
from adafruit_hid.keycode import Keycode

# --- Setup USB HID Keyboard ---
keyboard = Keyboard(usb_hid.devices)

# --- CONFIGURATION ---

# Keycode list for easy assignment of 0-9
NUMBERS_0_TO_9_KEYCODES = [
    Keycode.ZERO, Keycode.ONE, Keycode.TWO, Keycode.THREE, Keycode.FOUR,
    Keycode.FIVE, Keycode.SIX, Keycode.SEVEN, Keycode.EIGHT, Keycode.NINE
]

# Fixed pin ordering (IMPORTANT!)
PIN_ORDER = [
    board.GP0, board.GP1, board.GP2, board.GP3, board.GP4,
    board.GP5, board.GP6, board.GP7, board.GP8, board.GP9
]

# Single-key mapping
SINGLE_KEY_PINS = {
    board.GP0: NUMBERS_0_TO_9_KEYCODES[0],
    board.GP1: NUMBERS_0_TO_9_KEYCODES[1],
    board.GP2: NUMBERS_0_TO_9_KEYCODES[2],
    board.GP3: NUMBERS_0_TO_9_KEYCODES[3],
    board.GP4: NUMBERS_0_TO_9_KEYCODES[4],
    board.GP5: NUMBERS_0_TO_9_KEYCODES[5],
    board.GP6: NUMBERS_0_TO_9_KEYCODES[6],
    board.GP7: NUMBERS_0_TO_9_KEYCODES[7],
    board.GP8: NUMBERS_0_TO_9_KEYCODES[8],
    board.GP9: NUMBERS_0_TO_9_KEYCODES[9]
}

# Two-button combinations
COMBINATION_PINS_NUMERIC = {
    (0, 1): Keycode.A, (0, 2): Keycode.B, (0, 3): Keycode.C, (0, 4): Keycode.D,
    (0, 5): Keycode.E, (0, 6): Keycode.F, (0, 7): Keycode.G, (0, 8): Keycode.H,
    (0, 9): Keycode.I, (1, 2): Keycode.J,

    (1, 3): Keycode.K, (1, 4): Keycode.L, (1, 5): Keycode.M, (1, 6): Keycode.N,
    (1, 7): Keycode.O, (1, 8): Keycode.P, (1, 9): Keycode.Q, (2, 4): Keycode.R,
    (2, 5): Keycode.S, (2, 6): Keycode.T, (2, 7): Keycode.U, (2, 8): Keycode.V,
    (2, 9): Keycode.W, (3, 4): Keycode.X, (3, 5): Keycode.Y, (3, 6): Keycode.Z,

    (3, 7): Keycode.SPACE,
    (3, 8): Keycode.ENTER,
    (3, 9): Keycode.ESCAPE,
    (4, 5): Keycode.DELETE,
    (4, 6): Keycode.TAB,
    (4, 7): Keycode.LEFT_SHIFT,
    (4, 8): Keycode.LEFT_CONTROL,
    (4, 9): Keycode.LEFT_ALT,
    (5, 6): Keycode.F1,
    (5, 7): Keycode.F12,
}

# --- Initialization ---

pin_to_number_map = {}
button_pins = []
SINGLE_PIN_KEYCODES_LOOKUP = {}

# Guarantee correct numbering 0–9
for i, board_pin_object in enumerate(PIN_ORDER):
    button = digitalio.DigitalInOut(board_pin_object)
    button.direction = digitalio.Direction.INPUT
    button.pull = digitalio.Pull.UP
    button_pins.append(button)

    pin_to_number_map[button] = i
    SINGLE_PIN_KEYCODES_LOOKUP[button] = SINGLE_KEY_PINS[board_pin_object]

# Current pressed state
currently_pressed_keys = []

print("Keyboard script running with correct combination detection.")

# --- Stabilization Debounce ---

def stabilize_input(buttons):
    """Waits 50ms to allow multi-button presses to settle."""
    is_pressed = any(not b.value for b in buttons)
    if is_pressed:
        time.sleep(0.05)
    return is_pressed

# --- Determine desired keycode ---

def get_desired_keycode(current_pressed_pin_numbers):

    pressed_combo_tuple = tuple(sorted(list(current_pressed_pin_numbers)))

    # Try combos (2 or more buttons)
    if len(pressed_combo_tuple) >= 2:
        if pressed_combo_tuple in COMBINATION_PINS_NUMERIC:
            return COMBINATION_PINS_NUMERIC[pressed_combo_tuple]

    # Single button
    if len(pressed_combo_tuple) == 1:
        pin_index = pressed_combo_tuple[0]
        pin_object = button_pins[pin_index]
        return SINGLE_PIN_KEYCODES_LOOKUP[pin_object]

    return None


# --- Main Loop ---

while True:

    if not stabilize_input(button_pins):
        if currently_pressed_keys:
            keyboard.release_all()
            currently_pressed_keys = []
            print("All Released")
        time.sleep(0.01)
        continue

    # Gather pressed inputs
    current_pressed_pin_numbers = set()
    for pin in button_pins:
        if not pin.value:
            current_pressed_pin_numbers.add(pin_to_number_map[pin])

    # Look up output key
    desired_keycode = get_desired_keycode(current_pressed_pin_numbers)

    # Send HID output
    if desired_keycode is not None:
        if currently_pressed_keys != [desired_keycode]:
            keyboard.release_all()
            keyboard.press(desired_keycode)
            currently_pressed_keys = [desired_keycode]
            print("Key Sent:", desired_keycode)

    time.sleep(0.01)
