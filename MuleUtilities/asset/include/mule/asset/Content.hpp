/*
* Copyright (C) 2018 by Godlike
* This code is licensed under the MIT license (MIT)
* (http://opensource.org/licenses/MIT)
*/

#ifndef MULE_ASSET_CONTENT_HPP
#define MULE_ASSET_CONTENT_HPP

#include <cstdint>
#include <vector>

namespace mule
{
namespace asset
{

/** @brief  Represents asset content access
 *
 *  Holds binary buffer filled with asset content
 */
class Content
{
public:
    /** @brief  Constructs an object
     *
     *  @param  buffer  buffer with asset contents
     */
    Content(std::vector<uint8_t>&& buffer);

    Content(const Content& other) = delete;
    Content& operator=(const Content& other) = delete;

    Content(Content&& other) = delete;
    Content& operator=(Content&& other) = delete;

    ~Content() = default;

    /** @brief  Returns stored buffer */
    std::vector<uint8_t> const& GetBuffer() const { return m_buffer; }

    /** @brief  Returns the size of stored buffer */
    uintmax_t GetSize() const { return m_buffer.size(); }

private:
    //! Buffer with asset contents
    std::vector<uint8_t> m_buffer;
};

}
}

#endif // MULE_ASSET_CONTENT_HPP
