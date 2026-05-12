#pragma once

// Just used for a safer compilation to abort the application whenever
// an unreachable code is reached (avoid exceptions)
#ifndef _UNREACHABLE
#if defined(__cpp_lib_unreachable) && (__cpp_lib_unreachable >= 202202L)
    #define _UNREACHABLE() std::unreachable()
#elif defined(_MSC_VER)
    #define _UNREACHABLE() __assume(0)
#elif defined(__GNUC__) || defined(__clang__)
    #define _UNREACHABLE() __builtin_unreachable()
#else
    #define _UNREACHABLE() abort()
#endif
#endif