#pragma once

// Our coordinate system works in world units. 1 unit
// is 32x32. We can multiply world units by this value
// to get the pixels when drawing.
static constexpr float PIXELS_PER_UNIT = 32.0f;

// Used to prevent floating precision errors during collision.
constexpr float EPSILON = 0.0001f;
