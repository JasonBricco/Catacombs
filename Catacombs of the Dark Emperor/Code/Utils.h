#pragma once

#include <iostream>
#include <fstream>

struct GameState
{
    bool paused;
    bool newLevel;
    bool restart;
    bool showOutlines, showPathGrid;
    int newLevelPrevDir;
};

inline GameState g_state;

inline const int totalItemsInInventory = 9;

inline Vector2f playerPosition;

inline bool* playershield;

inline int score = 0;

inline int topscore = 0;

enum Direction
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT
};

const Vector2i directions[] =
{
    Vector2i(-1, 0), Vector2i(1, 0), Vector2i(0, 1), Vector2i(0, -1),
    Vector2i(-1, 1), Vector2i(1, 1), Vector2i(-1, -1), Vector2i(1, -1)
};

inline int GetOppositeDir(int dir)
{
    switch (dir)
    {
        case LEFT: return RIGHT;
        case RIGHT: return LEFT;
        case UP: return DOWN;
        case DOWN: return UP;
    }

    return -1;
}

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

template <typename T>
inline void Shuffle(T* arr, int n)
{
    while (n > 1)
    {
        n--;
        int k = randomInRange(0, n);
        T value = arr[k];
        arr[k] = arr[n];
        arr[n] = value;
    }
}

inline GameState& getGameState()
{
    return g_state;
}

// In order to use sf::Vector2i as a key in an std::unordered_map, 
// a hash function and comparison function must be provided.
// The Vector2iHash and Vector2iCompare structures provide this. 
// They are passed as template parameters when declaring the map.
struct Vector2iHash
{
    int operator()(Vector2i v) const
    {
        return v.y * 31 + v.x;
    }
};

struct Vector2iCompare
{
    bool operator()(Vector2i a, Vector2i b) const
    {
        return a.x == b.x && a.y == b.y;
    }
};

inline void setTopScore()
{
    ofstream savefile;
    savefile.open("save.txt");
    if (savefile.is_open())
    {
        savefile << topscore;
        savefile.close();
    }
}

typedef std::unordered_set<Vector2i, Vector2iHash, Vector2iCompare> Vector2iSet;
