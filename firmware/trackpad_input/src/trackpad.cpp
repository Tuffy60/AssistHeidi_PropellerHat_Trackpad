#include "Trackpad.h"
#include "cirque.h"

// TRACKPAD CONFIGURATION DEFINES

// Maximum X value reported by the Cirque trackpad
// Change ONLY if a different trackpad model is used
#define X_MAX 1350

// Maximum Y value reported by the Cirque trackpad
// Change ONLY if a different trackpad model is used
#define Y_MAX 1500

// Deadzone to suppress micro jitter around the center
// Increase to reduce jitter, decrease for more sensitivity
// Recommended range: 3 - 6
#define DEADZONE_CENTER   4

// Base movement sensitivity
// Increase for faster cursor movement
// Decrease for slower and more controlled movement
// Recommended range: 0.4 - 0.8
#define SENS              0.60

// Smoothing factor for movement
// Increase for smoother but slower response
// Decrease for more direct but noisier movement
// Recommended range: 0.2 - 0.4
#define SMOOTHING         0.25

// Distance from physical edge where edge scrolling starts
#define EDGE_DISTANCE      100

// Extra margin on the left side for hardware tolerance
#define EDGE_LEFT_EXTRA    300

// Extra margin on the bottom side for hardware tolerance
#define EDGE_TOP_EXTRA     200

// Base speed of edge scrolling
#define EDGE_SPEED_BASE    1.10

// Maximum additional speed at the edge
#define EDGE_SPEED_MAX     2.60

// Minimum edge speed required to activate scrolling
#define EDGE_MIN_TRIGGER   1

// INTERNAL STATE VARIABLES

static int lastX = -1;
static int lastY = -1;

static int xMinDetected = 9999;
static int yMinDetected = 9999;

static float smoothDX = 0;
static float smoothDY = 0;

static uint8_t rotationMode = TRACKPAD_ROTATION;

// INITIALIZATION

/// @brief Initializes the trackpad hardware
/// @details This function initializes the Cirque trackpad and must be
///          called once during system startup before using updateTrackpad().
void initTrackpad() {
    initCirque();
}

/// @brief Sets the rotation of the trackpad coordinate system
/// @param rot Rotation mode (0 = normal, 1 = 90°, 2 = 180°, 3 = 270°)
/// @details The rotation affects only the output movement direction.
///          Valid values are limited to 0–3.
void setRotation(uint8_t rot) {
    rotationMode = rot & 3;
}

// MAIN TRACKPAD UPDATE FUNCTION

/// @brief Reads and processes trackpad input
/// @return TrackpadProcessed structure containing finger state and movement
/// @details This function reads the raw Cirque trackpad data, applies
///          deadzone filtering, acceleration, smoothing, edge scrolling
///          and rotation, and returns relative cursor movement values.
///          It should be called continuously in the main loop.
TrackpadProcessed updateTrackpad() {

    TrackpadProcessed out;
    out.fingerPresent = false;
    out.dx = 0;
    out.dy = 0;

    int xAbs, yAbs;
    updateCirquePad(&xAbs, &yAbs);

    // NO FINGER DETECTED
    if (xAbs < 5 && yAbs < 5) {
        lastX = -1;
        lastY = -1;
        smoothDX = 0;
        smoothDY = 0;
        return out;
    }

    out.fingerPresent = true;

    // AUTO CALIBRATION
    if (xAbs < xMinDetected) xMinDetected = xAbs;
    if (yAbs < yMinDetected) yMinDetected = yAbs;

    // FIRST TOUCH EVENT
    if (lastX < 0) {
        lastX = xAbs;
        lastY = yAbs;
        return out;
    }

    // RAW MOVEMENT DELTAS
    int dx = xAbs - lastX;
    int dy = yAbs - lastY;

    lastX = xAbs;
    lastY = yAbs;

    if (abs(dx) < DEADZONE_CENTER) dx = 0;
    if (abs(dy) < DEADZONE_CENTER) dy = 0;

    // GAMING ACCELERATION
    float accel = 1.0f;
    int mag = abs(dx) + abs(dy);

    if (mag > 15) accel = 1.4f;
    if (mag > 30) accel = 1.9f;
    if (mag > 50) accel = 2.5f;

    float fdx = dx * SENS * accel;
    float fdy = dy * SENS * accel;

    // SMOOTHING
    smoothDX = smoothDX * (1.0f - SMOOTHING) + fdx * SMOOTHING;
    smoothDY = smoothDY * (1.0f - SMOOTHING) + fdy * SMOOTHING;

    // EDGE SCROLLING
    float edgeX = 0;
    float edgeY = 0;

    if (xAbs > X_MAX - EDGE_DISTANCE) {
        float a = float(xAbs - (X_MAX - EDGE_DISTANCE)) / EDGE_DISTANCE;
        edgeX = EDGE_SPEED_BASE + a * EDGE_SPEED_MAX;
    }

    int leftEdge = xMinDetected + EDGE_LEFT_EXTRA;
    if (xAbs < leftEdge) {
        float a = float(leftEdge - xAbs) / EDGE_LEFT_EXTRA;
        edgeX = -(EDGE_SPEED_BASE + a * EDGE_SPEED_MAX);
    }

    int topEdge = Y_MAX - EDGE_DISTANCE;
    if (yAbs > topEdge) {
        float a = float(yAbs - topEdge) / EDGE_DISTANCE;
        edgeY = EDGE_SPEED_BASE + a * EDGE_SPEED_MAX;
    }

    int bottomEdge = yMinDetected + EDGE_TOP_EXTRA;
    if (yAbs < bottomEdge) {
        float a = float(bottomEdge - yAbs) / EDGE_TOP_EXTRA;
        edgeY = -(EDGE_SPEED_BASE + a * EDGE_SPEED_MAX);
    }

    if (abs(edgeX) < EDGE_MIN_TRIGGER) edgeX = 0;
    if (abs(edgeY) < EDGE_MIN_TRIGGER) edgeY = 0;

    float outDX = smoothDX + edgeX;
    float outDY = smoothDY + edgeY;

    // ROTATION HANDLING
    switch (rotationMode) {
        case 0:
            out.dx = outDX;
            out.dy = outDY;
            break;
        case 1:
            out.dx =  outDY;
            out.dy = -outDX;
            break;
        case 2:
            out.dx = -outDX;
            out.dy = -outDY;
            break;
        case 3:
            out.dx = -outDY;
            out.dy =  outDX;
            break;
    }

    return out;
}
