/*
* Copyright (C) 2018 by Godlike
* This code is licensed under the MIT license (MIT)
* (http://opensource.org/licenses/MIT)
*/

#ifndef MULE_LOGGER_CONFIG_BASE_HPP
#define MULE_LOGGER_CONFIG_BASE_HPP

#include <mule/Logger.hpp>

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace mule
{

class LoggerConfigBase
{
public:
    struct Settings
    {
        std::string name = std::string();
        std::string pattern = std::string("%+");
        mule::LogLevel::level_enum level = mule::LogLevel::warn;
        std::vector<mule::Logger::SinkPtr> sinks;
    };

    void Reinitialize();

    Settings const& GetDefaultSettings() const;
    void SetDefaultSettings(Settings const& settings);
    void ResetDefaultSettings();

    void SetLoggerSettings(uint32_t index, Settings const& settings);
    Settings const& GetLoggerSettings(uint32_t index) const;

protected:
    LoggerConfigBase(uint32_t loggerCount);

    LoggerConfigBase(LoggerConfigBase const& other) = delete;
    LoggerConfigBase& operator=(LoggerConfigBase const& other) = delete;

    virtual ~LoggerConfigBase() = default;

    virtual void InitializeLogger(uint32_t index, Settings const& settings) = 0;

    uint32_t m_loggerCount;
    Settings m_defaultSettings;
    std::map<uint32_t, Settings> m_loggerSettings;

};

}

#endif // MULE_LOGGER_CONFIG_BASE_HPP
