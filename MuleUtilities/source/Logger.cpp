/*
* Copyright (C) 2018 by Godlike
* This code is licensed under the MIT license (MIT)
* (http://opensource.org/licenses/MIT)
*/

#include <mule/Logger.hpp>

#include <spdlog/sinks/null_sink.h>

namespace mule
{

LoggerPtr g_logger = std::make_shared<Logger>(
    "mule"
    ,
    std::initializer_list<mule::Logger::SinkPtr>({
        std::make_shared<spdlog::sinks::null_sink_st>()
    }));

}
