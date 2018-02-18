/*
* Copyright (C) 2018 by Godlike
* This code is licensed under the MIT license (MIT)
* (http://opensource.org/licenses/MIT)
*/

#ifndef MULE_ASSET_HANDLER_HPP
#define MULE_ASSET_HANDLER_HPP

#include <mule/asset/Content.hpp>

#include <atomic>
#include <chrono>
#include <cstdint>
#include <string>

namespace mule
{
namespace asset
{

/** @brief  Provides access to shared asset content
 *
 *  Holds track of how long current object is the last reference to shared data
 */
class Handler
{
public:
    /** @brief  Constructs an empty handler
     *
     *  Created object does not have any data associated with it
     */
    Handler();

    /** @brief  Constructs a shared data object around @p pContent
     *
     *  Initializes all required shared data
     *
     *  @param  name        asset name
     *  @param  pContent    pointer to asset contents
     */
    Handler(std::string const& name, Content* pContent);

    /** @brief  Constructs a shared object from @p other
     *
     *  Inherits and subscribes to shared data of @p other
     *
     *  @param  other   object with shared data
     */
    Handler(Handler const& other);

    /** @brief  Switches to shared object from @p other
     *
     *  Unsubscribes from current shared data and then inherits
     *  and subscribes to shared data of @p other
     *
     *  @param  other   object with shared data
     *
     *  @return a reference to @c this object
     */
    Handler& operator=(Handler const& other);

    /** @brief  Moves shared object from @p other
     *
     *  Inherits and subscribes to shared data of @p other, after that
     *  @p other is unsubscribed and reset
     *
     *  @param[in,out]  other   object with shared data
     */
    Handler(Handler&& other);

    /** @brief  Moves shared object from @p other
     *
     *  Unsubscribes from current shared data, then inherits and
     *  subscribes to shared data of @p other, after that @p other
     *  is unsubscribed and reset
     *
     *  @param[in,out]  other   object with shared data
     *
     *  @return a reference to @c this object
     */
    Handler& operator=(Handler&& other);

    /** @brief  Destructor
     *
     *  Unsubscribes from current shared data
     */
    ~Handler();

    /** @brief  Compares two Handler objects
     *
     *  @param  other   object with shared data
     *
     *  @return @c true if @p other points to the same shared data,
     *          @c false otherwise
     */
    bool operator==(Handler const& other) const;

    /** @brief  Compares two Handler objects
     *
     *  @param  other   object with shared data
     *
     *  @return @c false if @p other points to the same shared data,
     *          @c true otherwise
     *
     *  @sa operator==()
     */
    bool operator!=(Handler const& other) const;

    /** @brief  Checks if shared data may be accessed */
    bool IsValid() const { return nullptr != m_pContent; }

    /** @brief  Returns asset name */
    std::string const& GetName() const { return *m_pName; }

    /** @brief  Returns asset contents */
    Content const& GetContent() const { return *m_pContent; }

    /** @brief  Returns the duration since this object is the last refernce
     *
     *  @return duration since this object is the last reference (in ms),
     *          @c 0ms is returned if this object is not the last reference
     */
    std::chrono::milliseconds GetLastReferenceDuration() const;

private:
    /** @brief  Unsubscribes from shared data
     *
     *  Decrements @ref m_pRefCounter and checks its value:
     *  - if it is @c 0, deletes shared data
     *  - if it is @c 1, stores current timestamp to @ref m_pLastReferenceTimestamp
     *
     *  Resets shared data pointers
     */
    void Unsubscribe();

    /** @brief  Subscribes to shared data
     *
     *  Increments @ref m_pRefCounter and checks its value.
     *  If it became 2, resets @ref m_pLastReferenceTimestamp.
     */
    void Subscribe();

    //! Pointer to asset name
    std::string* m_pName;

    //! Pointer to asset contents
    Content* m_pContent;

    //! Atomic reference counter
    std::atomic<uint32_t>* m_pRefCounter;

    //! Atomic timestamp since this reference is the only one
    std::atomic<uint64_t>* m_pLastReferenceTimestamp;
};

}
}

#endif // MULE_ASSET_HANDLER_HPP
