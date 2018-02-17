/*
* Copyright (C) 2018 by Godlike
* This code is licensed under the MIT license (MIT)
* (http://opensource.org/licenses/MIT)
*/

#include <mule/asset/Handler.hpp>

namespace mule
{
namespace asset
{

Handler::Handler()
    : m_pName(nullptr)
    , m_pContent(nullptr)
    , m_pRefCounter(nullptr)
    , m_pLastReferenceTimestamp(nullptr)
{
}

Handler::Handler(std::string const& name, Content* pContent)
    : m_pName(nullptr)
    , m_pContent(pContent)
    , m_pRefCounter(nullptr)
    , m_pLastReferenceTimestamp(nullptr)
{
    m_pName = new std::string(name);
    m_pRefCounter = new std::atomic<uint32_t>(1);
    m_pLastReferenceTimestamp = new std::atomic<uint64_t>(0);
}

Handler::Handler(Handler const& other)
    : m_pName(other.m_pName)
    , m_pContent(other.m_pContent)
    , m_pRefCounter(other.m_pRefCounter)
    , m_pLastReferenceTimestamp(other.m_pLastReferenceTimestamp)
{
    Subscribe();
}

Handler& Handler::operator=(Handler const& other)
{
    Unsubscribe();

    m_pName = other.m_pName;
    m_pContent = other.m_pContent;
    m_pRefCounter = other.m_pRefCounter;
    m_pLastReferenceTimestamp = other.m_pLastReferenceTimestamp;

    Subscribe();

    return *this;
}

Handler::Handler(Handler&& other)
    : m_pName(other.m_pName)
    , m_pContent(other.m_pContent)
    , m_pRefCounter(other.m_pRefCounter)
    , m_pLastReferenceTimestamp(other.m_pLastReferenceTimestamp)
{
    Subscribe();

    other.Unsubscribe();
    other.m_pName = nullptr;
    other.m_pContent = nullptr;
    other.m_pRefCounter = nullptr;
    other.m_pLastReferenceTimestamp = nullptr;
}

Handler& Handler::operator=(Handler&& other)
{
    Unsubscribe();

    m_pName = other.m_pName;
    m_pContent = other.m_pContent;
    m_pRefCounter = other.m_pRefCounter;
    m_pLastReferenceTimestamp = other.m_pLastReferenceTimestamp;

    Subscribe();

    other.Unsubscribe();

    return *this;
}

Handler::~Handler()
{
    Unsubscribe();
}

bool Handler::operator==(Handler const& other) const
{
    return m_pName == other.m_pName &&
        m_pContent == other.m_pContent &&
        m_pRefCounter == other.m_pRefCounter &&
        m_pLastReferenceTimestamp == other.m_pLastReferenceTimestamp;
}

bool Handler::operator!=(Handler const& other) const
{
    return !operator==(other);
}

std::chrono::milliseconds Handler::GetLastReferenceDuration() const
{
    std::chrono::milliseconds timestamp(m_pLastReferenceTimestamp->load(std::memory_order_acquire));

    if (timestamp.count() != 0)
    {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::chrono::milliseconds nowInMs(std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count());

        return nowInMs - timestamp;
    }

    return timestamp;
}

void Handler::Unsubscribe()
{
    if (m_pRefCounter)
    {
        switch (--(*m_pRefCounter))
        {
            case 0:
            {
                delete m_pName;
                delete m_pContent;
                delete m_pRefCounter;
                delete m_pLastReferenceTimestamp;

                break;
            }
            case 1:
            {
                m_pLastReferenceTimestamp->store(
                    std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::system_clock::now().time_since_epoch())
                        .count(),
                    std::memory_order_release);
                break;
            }
            default:
            {
                break;
            }
        }
    }

    m_pName = nullptr;
    m_pContent = nullptr;
    m_pRefCounter = nullptr;
    m_pLastReferenceTimestamp = nullptr;
}

void Handler::Subscribe()
{
    if (m_pRefCounter)
    {
        //! reset clock if this is becomes not the last reference
        if (2 == ++(*m_pRefCounter))
        {
            m_pLastReferenceTimestamp->store(0, std::memory_order_release);
        }
    }
}

}
}
