#pragma once

namespace lumin {

/**
 * Math utilities and constants for the engine
 */
namespace math {

// Constants
constexpr float PI = 3.14159265359f;
constexpr float TWO_PI = 6.28318530718f;
constexpr float HALF_PI = 1.57079632679f;
constexpr float EPSILON = 0.0001f;

// Utility functions
inline float toRadians(float degrees) {
    return degrees * (PI / 180.0f);
}

inline float toDegrees(float radians) {
    return radians * (180.0f / PI);
}

inline float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

inline float clamp(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

} // namespace math

} // namespace lumin
