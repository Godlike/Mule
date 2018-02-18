/*
* Copyright (C) 2018 by Godlike
* This code is licensed under the MIT license (MIT)
* (http://opensource.org/licenses/MIT)
*/

#ifndef MULE_ASSET_SIMPLE_STORAGE_HPP
#define MULE_ASSET_SIMPLE_STORAGE_HPP

#include <mule/asset/Handler.hpp>
#include <mule/templates/Singleton.hpp>

#include <cstdint>
#include <string>
#include <unordered_map>

namespace mule
{
namespace asset
{

/** @brief  Controls non-thread safe asset access
 *
 *  Provides synchronous method to request assets
 *
 *  @todo   cleaning up idle Handler object
 */
class SimpleStorage : public templates::Singleton<SimpleStorage>
{
public:
    //! Alias to a key type used by underlying container
    typedef std::string KeyType;

    /** @brief  Gets an asset identified by @p key
     *
     *  If the asset is not available, prepares and returns it
     *
     *  @param  key asset identifier
     *
     *  @return Handler shared object
     *
     *  @sa ProcessHandlerCreation()
     */
    Handler Get(KeyType const& key);

private:
    friend class templates::Singleton<SimpleStorage>;

    //! Alias to underlying container
    typedef std::unordered_map<KeyType, Handler> HandlerMap;

    /** @brief  Creates and stores a Handler
     *
     *  Creates handler via CreateHandler() call and inserts it
     *  to @ref m_entries
     *
     *  @param  key asset identifier
     *
     *  @return created Handler
     *
     *  @sa CreateHandler()
     */
    Handler ProcessHandlerCreation(KeyType const& key);

    /** @brief  Creates a Handler for given @p key
     *
     *  Prepares asset contents from @p key and creates a Handler object.
     *
     *  @param  key asset identifier
     *
     *  @return created Handler
     */
    Handler CreateHandler(KeyType const& key);

    SimpleStorage() = default;

    SimpleStorage(SimpleStorage const& other) = delete;
    SimpleStorage& operator=(SimpleStorage const& other) = delete;

    SimpleStorage(SimpleStorage&& other) = delete;
    SimpleStorage& operator=(SimpleStorage&& other) = delete;

    ~SimpleStorage() = default;

    //! Container of asset handlers
    HandlerMap m_entries;
};

}
}

#endif // MULE_ASSET_SIMPLE_STORAGE_HPP
