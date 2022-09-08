#pragma once

// Game config global variables.
namespace Config
{
    const int REF_SCREEN_W = 360;
    const int REF_SCREEN_H = 640;

    // Scrolling velocity (positive = left direction)
    const float SCROLL_VEL = 70.0f;
    // Space between each barrier
    const float BARRIER_SPACING = 250.0f;
    // Size of the gap in the barriers
    const float GAP_SIZE = 120.0f;
    // Minimum random Y for barrier spawn
    const float BARRIER_MIN_SPAWN = -150.0f;
    // Maximum random Y for barrier spawn
    const float BARRIER_MAX_SPAWN = 200.0f;

    // Upwards velocity when bird flaps
    const float BIRD_JUMP = 500.0f;
    // Gravity
    const float BIRD_GRAVITY = 1200.0f;
} // namespace Config