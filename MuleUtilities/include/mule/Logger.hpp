/*
* Copyright (C) 2018 by Godlike
* This code is licensed under the MIT license (MIT)
* (http://opensource.org/licenses/MIT)
*/

#ifndef MULE_LOGGER_HPP
#define MULE_LOGGER_HPP

#include <tuple>

#define LOG_ERROR(...) (void)(std::make_tuple(__VA_ARGS__))
#define LOG_WARNING(...) (void)(std::make_tuple(__VA_ARGS__))
#define LOG_INFO(...) (void)(std::make_tuple(__VA_ARGS__))
#define LOG_DEBUG(...) (void)(std::make_tuple(__VA_ARGS__))

#include <spdlog/logger.h>

namespace mule
{

namespace LogLevel = spdlog::level;

class Logger
{
public:
    using SinkPtr = spdlog::sink_ptr;

    Logger(const std::string& name, std::initializer_list<SinkPtr> sinks);

    void SetLevel(LogLevel::level_enum lvl);

    template <typename... Args>
        inline void log(LogLevel::level_enum lvl, const char* fmt, const Args&... args)
    {
        m_logger.log(lvl, fmt, args...);
    }

    template <typename... Args>
        inline void log(LogLevel::level_enum lvl, const char* msg)
    {
        m_logger.log(lvl, msg);
    }

private:
    spdlog::logger m_logger;
};

}

#endif // MULE_LOGGER_HPP
