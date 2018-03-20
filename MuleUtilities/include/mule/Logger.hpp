/*
* Copyright (C) 2018 by Godlike
* This code is licensed under the MIT license (MIT)
* (http://opensource.org/licenses/MIT)
*/

#ifndef MULE_LOGGER_HPP
#define MULE_LOGGER_HPP

#include <spdlog/logger.h>
#include <spdlog/fmt/ostr.h>

#include <initializer_list>
#include <memory>

namespace mule
{

namespace LogLevel = spdlog::level;

/** @brief  Public interface for a logger category */
class Logger
{
public:
    using Impl = spdlog::logger;
    using SinkPtr = spdlog::sink_ptr;

    /** @brief  Constructs a logger category object
     *
     *  @param  name    category name
     *  @param  sinks   sinks that should process log entries
     */
    Logger(std::string const& name, std::initializer_list<SinkPtr> sinks)
        : m_logger(name, sinks) {}

    /** @brief  Constructs a logger category object
     *
     *  @tparam It      sink iterator
     *
     *  @param  name    category name
     *  @param  begin   iterator to first sink
     *  @param  end     end iterator for sinks
     */
    template<class It>
        Logger(std::string const& name, It const& begin, It const& end)
        : m_logger(name, begin, end) {}

    /** @brief  Processes log entry
     *
     *  @tparam Args    entry arguments
     *
     *  @param  lvl     entry level
     *  @param  fmt     format string
     *  @param  args    arguments for @p fmt
     */
    template <typename... Args>
        inline void Log(LogLevel::level_enum lvl, char const* fmt, Args const&... args)
    {
        m_logger.log(lvl, fmt, args...);
    }

    /** @brief  Processes log entry
     *
     *  @tparam Args    entry arguments
     *
     *  @param  lvl     entry level
     *  @param  msg     message
     */
    template <typename... Args>
        inline void Log(LogLevel::level_enum lvl, char const* msg)
    {
        m_logger.log(lvl, msg);
    }

    /** @brief  Processes trace log entry
     *
     *  @tparam Args    entry arguments
     *
     *  @param  fmt     format string
     *  @param  args    arguments for @p fmt
     *
     *  @sa Log
     */
    template <typename... Args>
        inline void Trace(char const* fmt, Args const&... args)
    {
        Log(LogLevel::trace, fmt, args...);
    }

    /** @brief  Processes trace log entry
     *
     *  @tparam Args    entry arguments
     *
     *  @param  msg     message
     *
     *  @sa Log
     */
    template <typename... Args>
        inline void Trace(char const* msg)
    {
        Log(LogLevel::trace, msg);
    }

    /** @brief  Processes debug log entry
     *
     *  @tparam Args    entry arguments
     *
     *  @param  fmt     format string
     *  @param  args    arguments for @p fmt
     *
     *  @sa Log
     */
    template <typename... Args>
        inline void Debug(char const* fmt, Args const&... args)
    {
        Log(LogLevel::debug, fmt, args...);
    }

    /** @brief  Processes debug log entry
     *
     *  @tparam Args    entry arguments
     *
     *  @param  msg     message
     *
     *  @sa Log
     */
    template <typename... Args>
        inline void Debug(char const* msg)
    {
        Log(LogLevel::debug, msg);
    }

    /** @brief  Processes info log entry
     *
     *  @tparam Args    entry arguments
     *
     *  @param  fmt     format string
     *  @param  args    arguments for @p fmt
     *
     *  @sa Log
     */
    template <typename... Args>
        inline void Info(char const* fmt, Args const&... args)
    {
        Log(LogLevel::info, fmt, args...);
    }

    /** @brief  Processes info log entry
     *
     *  @tparam Args    entry arguments
     *
     *  @param  msg     message
     *
     *  @sa Log
     */
    template <typename... Args>
        inline void Info(char const* msg)
    {
        Log(LogLevel::info, msg);
    }

    /** @brief  Processes warning log entry
     *
     *  @tparam Args    entry arguments
     *
     *  @param  fmt     format string
     *  @param  args    arguments for @p fmt
     *
     *  @sa Log
     */
    template <typename... Args>
        inline void Warning(char const* fmt, Args const&... args)
    {
        Log(LogLevel::warn, fmt, args...);
    }

    /** @brief  Processes warning log entry
     *
     *  @tparam Args    entry arguments
     *
     *  @param  msg     message
     *
     *  @sa Log
     */
    template <typename... Args>
        inline void Warning(char const* msg)
    {
        Log(LogLevel::warn, msg);
    }

    /** @brief  Processes error log entry
     *
     *  @tparam Args    entry arguments
     *
     *  @param  fmt     format string
     *  @param  args    arguments for @p fmt
     *
     *  @sa Log
     */
    template <typename... Args>
        inline void Error(char const* fmt, Args const&... args)
    {
        Log(LogLevel::err, fmt, args...);
    }

    /** @brief  Processes error log entry
     *
     *  @tparam Args    entry arguments
     *
     *  @param  msg     message
     *
     *  @sa Log
     */
    template <typename... Args>
        inline void Error(char const* msg)
    {
        Log(LogLevel::err, msg);
    }

    /** @brief  Processes critical log entry
     *
     *  @tparam Args    entry arguments
     *
     *  @param  fmt     format string
     *  @param  args    arguments for @p fmt
     *
     *  @sa Log
     */
    template <typename... Args>
        inline void Critical(char const* fmt, Args const&... args)
    {
        Log(LogLevel::critical, fmt, args...);
    }

    /** @brief  Processes critical log entry
     *
     *  @tparam Args    entry arguments
     *
     *  @param  msg     message
     *
     *  @sa Log
     */
    template <typename... Args>
        inline void Critical(char const* msg)
    {
        Log(LogLevel::critical, msg);
    }

    /** @brief  Sets min entry level to be logged
     *
     *  @param  level   min log entry level to be logged
     */
    void SetLevel(LogLevel::level_enum level) { m_logger.set_level(level); }

    /** @brief  Sets log entry pattern
     *
     *  @param  pattern log entry pattern
     */
    void SetPattern(std::string const& pattern = std::string("%+")) { m_logger.set_pattern(pattern, spdlog::pattern_time_type::utc); }

private:
    //! Actual logger implementation
    Impl m_logger;
};

using LoggerPtr = std::shared_ptr<Logger>;

}

#endif // MULE_LOGGER_HPP
