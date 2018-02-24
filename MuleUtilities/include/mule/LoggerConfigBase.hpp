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

/** @brief  Base class for configurable categorized logging system */
class LoggerConfigBase
{
public:
    /** @brief  Logger configuration */
    struct Settings
    {
        //! logger category name; if empty, default preset category name would be used
        std::string name = std::string();

        //! log entry pattern; read more at https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
        std::string pattern = std::string("%+");

        //! overall log entry min level
        mule::LogLevel::level_enum level = mule::LogLevel::warn;

        //! sinks that should process log entries
        std::vector<mule::Logger::SinkPtr> sinks;
    };

    /** @brief  Reinitializes all loggers
     *
     *  Find corresponding settings for each logger and applies them via InitializeLogger()
     *
     *  @sa SetDefaultSettings, SetLoggerSettings, InitializeLogger
     */
    void Reinitialize();

    /** @brief  Returns default settings for loggers */
    Settings const& GetDefaultSettings() const;

    /** @brief  Sets default settings for loggers
     *
     *  @param  settings    new settings
     */
    void SetDefaultSettings(Settings const& settings);

    /** @brief  Resets default settings for loggers
     *
     *  Sets the following configuration:
     *  - empty name (-> default preset category name)
     *  - %+ pattern
     *  - warn log level
     *  - ansicolor stdout sink
     *
     *  @sa GetDefaultSettings, SetDefaultSettings
     */
    void ResetDefaultSettings();

    /** @brief  Sets logger category specific settings
     *
     *  @note   if settings.name is empty, default preset category name will be used
     *          if settings.pattern is empty, default pattern (%+) will be used
     *
     *  @param  index       category index
     *  @param  settings    new settings
     *
     *  @sa SetDefaultSettings
     */
    void SetLoggerSettings(uint32_t index, Settings const& settings);

    /** @brief  Returns settings that would be used for given logger index
     *
     *  @param  index   category index
     *
     *  @return category specific settings if they are set or default settings otherwise
     *
     *  @sa GetDefaultSettings, SetLoggerSettings
     */
    Settings const& GetLoggerSettings(uint32_t index) const;

protected:
    /** @brief  Constructs base object
     *
     *  @param  loggerCount maximum number of logger categories
     */
    LoggerConfigBase(uint32_t loggerCount);

    LoggerConfigBase(LoggerConfigBase const& other) = delete;
    LoggerConfigBase& operator=(LoggerConfigBase const& other) = delete;

    virtual ~LoggerConfigBase() = default;

    /** @brief  Creates a logger using given settings
     *
     *  @param  index       category index
     *  @param  settings    settings to be applied
     */
    virtual void InitializeLogger(uint32_t index, Settings const& settings) = 0;

    //! Maximum number of logger categories; used for asserts
    uint32_t m_loggerCount;

    //! Default settings to be applied when creating loggers
    Settings m_defaultSettings;

    //! Category specific settings to be applied when creating specific loggers
    std::map<uint32_t, Settings> m_loggerSettings;

};

}

#endif // MULE_LOGGER_CONFIG_BASE_HPP
