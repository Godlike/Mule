/*
* Copyright (C) 2018 by Godlike
* This code is licensed under the MIT license (MIT)
* (http://opensource.org/licenses/MIT)
*/

#include <mule/asset/Content.hpp>

namespace mule
{
namespace asset
{

Content::Content(std::vector<uint8_t>&& buffer)
    : m_buffer(buffer)
{
}

}
}

