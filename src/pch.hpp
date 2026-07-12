// A place to store global includes
//
// adding or removing something from here does cause
// a full rebuild of the project

#pragma once

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
#endif

#ifdef __cplusplus
    #include <deque>
    #include <filesystem>
    #include <print>

// convience
namespace fs = std::filesystem;
#endif
