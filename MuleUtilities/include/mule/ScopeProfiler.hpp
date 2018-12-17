/*
* Copyright (C) 2018 by Godlike
* This code is licensed under the MIT license (MIT)
* (http://opensource.org/licenses/MIT)
*/

#ifndef MULE_SCOPE_PROFILER_HPP
#define MULE_SCOPE_PROFILER_HPP

#include <mule/Logger.hpp>

#include <chrono>
#include <iostream>
#include <string_view>

namespace mule
{

template<class Clock = std::chrono::high_resolution_clock>
    class ScopeProfiler
{
public:
    ScopeProfiler(LoggerPtr logger
        , std::string_view name
    )
        : m_logger(logger)
        , m_name(name)
    {
        m_start = Clock::now();
    }

    ~ScopeProfiler()
    {
        m_logger->Debug("[Profiler] #{} {}us"
            , m_name.data()
            , std::chrono::duration_cast<std::chrono::microseconds>(
                    Clock::now() - m_start
                ).count()
        );
    }

private:
    LoggerPtr m_logger;
    std::string_view m_name;
    typename Clock::time_point m_start;
};

}

#endif // MULE_SCOPE_PROFILER_HPP
