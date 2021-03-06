/*
* Copyright (C) 2018 by Godlike
* This code is licensed under the MIT license (MIT)
* (http://opensource.org/licenses/MIT)
*/

#include <mule/asset/SimpleStorage.hpp>

#include <mule/asset/Content.hpp>
#include <mule/asset/FileReader.hpp>

#include <mule/InternalLoggers.hpp>

namespace mule
{
namespace asset
{

Handler SimpleStorage::Get(const KeyType& key)
{
    HandlerMap::const_iterator it = m_entries.find(key);

    if (m_entries.cend() != it)
    {
        LOG_STORAGE->Debug("Requested asset \"{}\" -> exists", key.c_str());

        return it->second;
    }
    else
    {
        LOG_STORAGE->Debug("Requested asset \"{}\" -> process", key.c_str());

        return ProcessHandlerCreation(key);
    }
}

Handler SimpleStorage::ProcessHandlerCreation(const KeyType& key)
{
    LOG_STORAGE->Debug("Processing asset \"{}\" -> creating handler", key.c_str());

    Handler handler = CreateHandler(key);

    LOG_STORAGE->Debug("Processing asset \"{}\" -> publishing entry", key.c_str());

    m_entries.insert(std::make_pair(key, handler));

    return handler;
}

Handler SimpleStorage::CreateHandler(const KeyType& key)
{
    Content* content = nullptr;

    LOG_STORAGE->Debug("Reading file \"{}\"", key.c_str());

    FileReader file(key.c_str());

    if (file.IsGood())
    {
        content = new Content(file.MoveContent());
    }
    else
    {
        LOG_STORAGE->Warning("Failed to read file \"{}\"", key.c_str());
    }

    return Handler(key, content);
}

}
}
