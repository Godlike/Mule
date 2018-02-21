/*
* Copyright (C) 2018 by Godlike
* This code is licensed under the MIT license (MIT)
* (http://opensource.org/licenses/MIT)
*/

#include <mule/MuleUtilities.hpp>

#include <mule/Loggers.hpp>

namespace mule
{

void MuleUtilities::Initialize()
{
    Loggers::Instance().Reinitialize();
}

}
