#ifndef TRACKPAD_H
#define TRACKPAD_H

#include <Arduino.h>

/// Trackpad rotation configuration
/// 0 = normal orientation
/// 1 = rotated 90° clockwise
/// 2 = rotated 180°
/// 3 = rotated 270° clockwise
/// This value defines the default rotation at startup
#ifndef TRACKPAD_ROTATION
#define TRACKPAD_ROTATION 1
#endif

/// @brief Processed output data from the trackpad
/// @details This structure contains the processed movement values
///          and the current finger detection state.
struct TrackpadProcessed {

    /// True if a finger is currently detected on the trackpad
    bool fingerPresent;

    /// Relative movement in X direction
    /// Positive values move the cursor to the right
    float dx;

    /// Relative movement in Y direction
    /// Positive values move the cursor downward
    float dy;
};

/// @brief Initializes the trackpad hardware
/// @details This function initializes the underlying Cirque trackpad
///          and must be called once during system startup.
void initTrackpad();

/// @brief Updates the trackpad and processes finger movement
/// @return TrackpadProcessed structure containing movement and state
/// @details This function reads the raw trackpad data, applies filtering,
///          acceleration, edge scrolling and rotation, and returns
///          relative cursor movement values.
///          It should be called continuously in the main loop.
TrackpadProcessed updateTrackpad();

/// @brief Sets the rotation of the trackpad coordinate system
/// @param rot Rotation mode (0 = normal, 1 = 90°, 2 = 180°, 3 = 270°)
/// @details The rotation affects only the output movement direction
///          and can be changed at runtime via code.
void setRotation(uint8_t rot);

#endif
