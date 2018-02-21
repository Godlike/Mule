/*
* Copyright (C) 2018 by Godlike
* This code is licensed under the MIT license (MIT)
* (http://opensource.org/licenses/MIT)
*/

#ifndef MULE_LOGGERS_HPP
#define MULE_LOGGERS_HPP

#include <mule/LoggerConfigBase.hpp>
#include <mule/templates/Singleton.hpp>

namespace mule
{

class Loggers
    : public LoggerConfigBase
    , public templates::Singleton<Loggers>
{
public:
    using Settings = LoggerConfigBase::Settings;

    std::vector<std::string> GetDefaultLoggerNames() const;

private:
    friend templates::Singleton<Loggers>;

    Loggers();
    ~Loggers() = default;

    virtual void InitializeLogger(uint32_t index, Settings const& settings) override;
};

}


#endif // MULE_LOGGERS_HPP
