/*
* Copyright (C) 2018 by Godlike
* This code is licensed under the MIT license (MIT)
* (http://opensource.org/licenses/MIT)
*/

#ifndef MULE_LOGGER_HPP
#define MULE_LOGGER_HPP

#include <spdlog/logger.h>

#include <initializer_list>
#include <memory>

namespace mule
{

namespace LogLevel = spdlog::level;

class Logger
{
public:
    using Impl = spdlog::logger;
    using SinkPtr = spdlog::sink_ptr;

    Logger(std::string const& name, std::initializer_list<SinkPtr> sinks)
        : m_logger(name, sinks) {}

    template<class It>
        Logger(std::string const& name, It const& begin, It const& end)
        : m_logger(name, begin, end) {}

    template <typename... Args>
        inline void Log(LogLevel::level_enum lvl, char const* fmt, Args const&... args)
    {
        m_logger.log(lvl, fmt, args...);
    }

    template <typename... Args>
        inline void Log(LogLevel::level_enum lvl, char const* msg)
    {
        m_logger.log(lvl, msg);
    }

    template <typename... Args>
        inline void Trace(const char* fmt, Args const&... args)
    {
        Log(LogLevel::trace, fmt, args...);
    }

    template <typename... Args>
        inline void Trace(const char* fmt)
    {
        Log(LogLevel::trace, fmt);
    }

    template <typename... Args>
        inline void Debug(const char* fmt, Args const&... args)
    {
        Log(LogLevel::debug, fmt, args...);
    }

    template <typename... Args>
        inline void Debug(const char* fmt)
    {
        Log(LogLevel::debug, fmt);
    }

    template <typename... Args>
        inline void Info(const char* fmt, Args const&... args)
    {
        Log(LogLevel::info, fmt, args...);
    }

    template <typename... Args>
        inline void Info(const char* fmt)
    {
        Log(LogLevel::info, fmt);
    }

    template <typename... Args>
        inline void Warning(const char* fmt, Args const&... args)
    {
        Log(LogLevel::warn, fmt, args...);
    }

    template <typename... Args>
        inline void Warning(const char* fmt)
    {
        Log(LogLevel::warn, fmt);
    }

    template <typename... Args>
        inline void Error(const char* fmt, Args const&... args)
    {
        Log(LogLevel::err, fmt, args...);
    }

    template <typename... Args>
        inline void Error(const char* fmt)
    {
        Log(LogLevel::err, fmt);
    }

    template <typename... Args>
        inline void Critical(const char* fmt, Args const&... args)
    {
        Log(LogLevel::critical, fmt, args...);
    }

    template <typename... Args>
        inline void Critical(const char* fmt)
    {
        Log(LogLevel::critical, fmt);
    }

    void SetLevel(LogLevel::level_enum level) { m_logger.set_level(level); }
    void SetPattern(std::string const& pattern = std::string("%+")) { m_logger.set_pattern(pattern, spdlog::pattern_time_type::utc); }

private:
    Impl m_logger;
};

using LoggerPtr = std::shared_ptr<Logger>;

}

#endif // MULE_LOGGER_HPP
