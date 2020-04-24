#pragma once

// Precompiled header file. We include this in every C++ file.
// It exists to improve compilation time.

#pragma warning(push, 0)

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <vector>
#include <unordered_map>
#include <string>
#include <cassert>
#include <algorithm>
#include <unordered_set>

#pragma warning(pop)

using namespace sf;
using namespace std;

#define stdin  (__acrt_iob_func(0))
#define stdout (__acrt_iob_func(1))
#define stderr (__acrt_iob_func(2))

FILE _iob[] = { *stdin, *stdout, *stderr };
extern "C" FILE * __cdecl __iob_func(void) { return _iob; }
