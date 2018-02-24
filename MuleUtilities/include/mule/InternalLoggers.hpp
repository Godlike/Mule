/*
* Copyright (C) 2018 by Godlike
* This code is licensed under the MIT license (MIT)
* (http://opensource.org/licenses/MIT)
*/

#ifndef MULE_INTERNAL_LOGGERS_HPP
#define MULE_INTERNAL_LOGGERS_HPP

#include <mule/Logger.hpp>

#include <array>
#include <cstdint>

namespace mule
{

struct Log
{
    static constexpr uint32_t mule = 0;
    static constexpr uint32_t mule_storage = 1;

    static constexpr uint32_t size = 2;
};

extern std::array<mule::LoggerPtr, Log::size> g_loggers;

}

#define LOG ::mule::g_loggers[::mule::Log::mule]
#define LOG_STORAGE ::mule::g_loggers[::mule::Log::mule_storage]

#endif // MULE_INTERNAL_LOGGERS_HPP
