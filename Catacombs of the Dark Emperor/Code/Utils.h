#pragma once

// Macro to make it easier to print to the Visual Studio console.
// Printf will not print to this console (we don't run via command line).
#define Print(...) { \
    char buf[256]; \
    snprintf(buf, sizeof(buf), __VA_ARGS__); \
    OutputDebugStringA(buf); \
}
