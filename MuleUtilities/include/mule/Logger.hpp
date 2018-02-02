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

#endif // MULE_LOGGER_HPP
