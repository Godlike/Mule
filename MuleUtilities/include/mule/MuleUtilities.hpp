/*
* Copyright (C) 2018 by Godlike
* This code is licensed under the MIT license (MIT)
* (http://opensource.org/licenses/MIT)
*/

#ifndef MULE_MULE_UTILITIES_HPP
#define MULE_MULE_UTILITIES_HPP

#include <mule/Logger.hpp>

#include <cstdint>
#include <map>
#include <string>
#include <vector>

namespace mule
{

/** @brief  Mule library entry point */
class MuleUtilities
{
public:
    /** @brief  Initializes internal subsystems */
    static void Initialize();

};

}

#endif // MULE_MULE_UTILITIES_HPP
