/*
* Copyright (C) 2018 by Godlike
* This code is licensed under the MIT license (MIT)
* (http://opensource.org/licenses/MIT)
*/

#include <mule/LoggerConfigBase.hpp>

#include <spdlog/sinks/null_sink.h>
#include <spdlog/sinks/ansicolor_sink.h>

namespace mule
{

void LoggerConfigBase::Reinitialize()
{
    for (uint32_t i = 0; i < m_loggerCount; ++i)
    {
        Settings settings = GetLoggerSettings(i);

        if (settings.pattern.empty())
        {
            settings.pattern = std::string("%+");
        }

        if (settings.sinks.empty())
        {
            settings.sinks.push_back(std::make_shared<spdlog::sinks::null_sink_st>());
        }

        InitializeLogger(i, settings);
    }
}

LoggerConfigBase::Settings const& LoggerConfigBase::GetDefaultSettings() const
{
     return m_defaultSettings;
}

void LoggerConfigBase::SetDefaultSettings(Settings const& settings)
{
    m_defaultSettings = settings;
}

void LoggerConfigBase::ResetDefaultSettings()
{
    m_defaultSettings.name = std::string();
    m_defaultSettings.pattern = std::string("%+");
    m_defaultSettings.level = mule::LogLevel::warn;
    m_defaultSettings.sinks = { std::make_shared<spdlog::sinks::ansicolor_stdout_sink_st>() };
}

void LoggerConfigBase::SetLoggerSettings(uint32_t index, Settings const& settings)
{
    assert(index < m_loggerCount);

    m_loggerSettings[index] = settings;
}

LoggerConfigBase::Settings const& LoggerConfigBase::GetLoggerSettings(uint32_t index) const
{
    return (
        (m_loggerSettings.cend() != m_loggerSettings.find(index))
            ? m_loggerSettings.at(index)
            : m_defaultSettings
    );
}

LoggerConfigBase::LoggerConfigBase(uint32_t loggerCount)
    : m_loggerCount(loggerCount)
{
    ResetDefaultSettings();
}

}
