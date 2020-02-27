#pragma once

enum Direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

// Macro to make it easier to print to the Visual Studio console.
// Printf will not print to this console (we don't run via command line).
#define Print(...) { \
    char buf[256]; \
    snprintf(buf, sizeof(buf), __VA_ARGS__); \
    OutputDebugStringA(buf); \
}

inline float Square(float value)
{
    return value * value;
}

inline Vector2i TilePos(Vector2f pos)
{
    return Vector2i((int)floorf(pos.x), (int)floorf(pos.y));
}

// Vector math functions, since SFML lacks them.
inline Vector2f Mul(Vector2f a, Vector2f b)
{
    return Vector2f(a.x * b.x, a.y * b.y);
}

inline float Dot(Vector2f a, Vector2f b)
{
    Vector2f tmp = Mul(a, b);
    return tmp.x + tmp.y;
}

inline float Length2(Vector2f v)
{
    return Dot(v, v);
}

inline float Distance2(Vector2f a, Vector2f b)
{
    return Length2(b - a);
}

inline float Distance(Vector2f a, Vector2f b)
{
    return sqrtf(Distance2(a, b));
}

inline float InverseSqrt(float v)
{
    return 1.0f / sqrtf(v);
}

inline Vector2f Normalize(Vector2f v)
{
    return v * InverseSqrt(Dot(v, v));
}

inline int randomInRange(int a, int b)
{
    return (rand() % (b + 1 - a)) + a;
}

inline float randomUnit()
{
    return rand() / (float)RAND_MAX;
}
