/*
* Copyright (C) 2018 by Godlike
* This code is licensed under the MIT license (MIT)
* (http://opensource.org/licenses/MIT)
*/

#include <mule/asset/Storage.hpp>

#include <mule/asset/Content.hpp>
#include <mule/asset/FileReader.hpp>

#include <mule/InternalLoggers.hpp>

#include <chrono>

namespace mule
{
namespace asset
{

void Storage::InitializeWorkers(uint16_t count)
{
    if (m_workers.size() != count)
    {
        StopWorkers();
    }

    LOG_STORAGE->Info("Initializing {} workers", count);

    m_workers.reserve(count);

    for (unsigned int i = 0; i < count; ++i)
    {
        m_workers.push_back(std::thread(&Storage::WorkerThread, this));
    }
}

Handler Storage::Get(const KeyType& key)
{
    std::pair<ConcurrentHandlerMap::iterator, bool> entry = m_entries.contains(key);

    if (entry.second && std::future_status::ready == entry.first->second.wait_for(std::chrono::nanoseconds(0)))
    {
        LOG_STORAGE->Debug("Requested sync task \"{}\" -> exists", key.c_str());

        return entry.first->second.get();
    }
    else
    {
        LOG_STORAGE->Debug("Requested sync task \"{}\" -> process", key.c_str());

        return ProcessHandlerCreation(key);
    }
}

std::shared_future<Handler> Storage::GetAsync(const KeyType& key, uint32_t priority)
{
    std::pair<ConcurrentHandlerMap::iterator, bool> entry = m_entries.contains(key);

    if (entry.second)
    {
        LOG_STORAGE->Debug("Requested async task \"{}\"[{}] -> exists", key.c_str(), priority);

        return entry.first->second;
    }
    else
    {
        LOG_STORAGE->Debug("Requested async task \"{}\"[{}] -> process", key.c_str(), priority);

        return ProcessAsyncHandlerCreation(key, priority);
    }
}

void Storage::StopWorkers()
{
    if (!m_workers.empty())
    {
        LOG_STORAGE->Info("Stopping all worker threads");

        {
            std::lock_guard<MutexType> lock(m_ordersMutex);
            m_workersStopFlag = true;
        }

        m_ordersCV.notify_all();

        LOG_STORAGE->Info("Joining threads");

        for (std::vector<std::thread>::iterator it = m_workers.begin(); it != m_workers.end(); ++it)
        {
            it->join();
        }

        m_workers.clear();

        m_workersStopFlag = false;
    }
}

Handler Storage::ProcessHandlerCreation(const KeyType& key)
{
    std::pair<RequestsSet::iterator, bool> requestFlag;
    std::promise<Handler> promise;

    {
        std::lock_guard<SharedMutexType> lock(m_requestsMutex);
        requestFlag = m_requests.insert(key);

        if (requestFlag.second)
        {
            LOG_STORAGE->Debug("Processing sync task \"{}\" -> creating entry", key.c_str());

            m_entries.insert(std::make_pair(key, promise.get_future().share()));
        }
    }

    if (requestFlag.second)
    {
        LOG_STORAGE->Debug("Processing sync task \"{}\" -> creating handler", key.c_str());

        Handler handler = CreateHandler(key);

        LOG_STORAGE->Debug("Processing sync task \"{}\" -> publishing handler to entry", key.c_str());

        promise.set_value(handler);

        return handler;
    }
    else
    {
        //! If given key was already requested, we need to either snatch the order
        //! to fulfill it ourselves or wait for the worker thread to process it
        Task task;

        {
            std::lock_guard<MutexType> lock(m_ordersMutex);
            task = m_orders.Snatch(key);
        }

        //! If the key is not empty - we snatched the order from the queue
        if (!task.key.empty())
        {
            std::shared_future<Handler> result = m_entries.at(key);

            LOG_STORAGE->Debug("Processing sync task \"{}\" -> snatched async task \"{}\"[{}] -> creating handler", key.c_str(), task.key.c_str(), task.priority);

            //! Since we snatched it, we should also set the promise value
            Handler handler = CreateHandler(task.key);

            LOG_STORAGE->Debug("Processing sync task \"{}\" -> publishing handler to entry", key.c_str());

            task.promise.set_value(handler);

            return handler;
        }
        else
        {
            LOG_STORAGE->Debug("Processing sync task \"{}\" -> waiting for async task finish", task.key.c_str());

            //! We couldn't snatch it, so we should wait on the future
            return m_entries.at(key).get();
        }
    }
}

std::shared_future<Handler> Storage::ProcessAsyncHandlerCreation(const KeyType& key, uint32_t priority)
{
    std::pair<RequestsSet::iterator, bool> requestFlag;
    std::shared_future<Handler> result;
    std::promise<Handler> promise;

    {
        std::lock_guard<SharedMutexType> lock(m_requestsMutex);
        requestFlag = m_requests.insert(key);

        if (requestFlag.second)
        {
            LOG_STORAGE->Debug("Processing async task \"{}\"[{}] -> creating entry", key.c_str(), priority);

            result = promise.get_future().share();
            m_entries.insert(std::make_pair(key, result));
        }
    }

    if (requestFlag.second)
    {
        Task task;
        task.key = key;
        task.priority = priority;
        task.promise = std::move(promise);

        LOG_STORAGE->Debug("Processing async task \"{}\"[{}] -> pushing order", task.key.c_str(), priority);

        {
            std::lock_guard<MutexType> lock(m_ordersMutex);
            m_orders.push(std::move(task));
        }

        m_ordersCV.notify_one();
    }
    else
    {
        LOG_STORAGE->Debug("Processing async task \"{}\"[{}] -> already requested; updating priority and reusing entry", key.c_str(), priority);

        {
            std::lock_guard<MutexType> lock(m_ordersMutex);
            m_orders.UpdatePriority(key, priority);
        }

        result = m_entries.at(key);
    }

    return result;
}

Handler Storage::CreateHandler(const KeyType& key)
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

Storage::Task::Task()
    : key(KeyType())
    , priority(0)
{
}

Storage::Task::Task(Task&& other)
    : key(other.key)
    , priority(other.priority)
    , promise(std::move(other.promise))
{
    other.key = KeyType();
    other.priority = 0;
}

Storage::Task& Storage::Task::operator=(Task&& other)
{
    key = other.key;
    priority = other.priority;
    promise = std::move(other.promise);

    other.key = KeyType();
    other.priority = 0;

    return *this;
}

Storage::Task Storage::TaskQueue::Snatch(const KeyType& key)
{
    for (container_type::iterator t = c.begin(); t != c.end(); ++t)
    {
        if (0 == key.compare(t->key))
        {
            Task result = std::move(*t);

            c.erase(t);

            std::make_heap(c.begin(), c.end(), comp);

            return result;
        }
    }

    return Task();
}

Storage::Task Storage::TaskQueue::PopTop()
{
    Task result = std::move(c.front());

    std::pop_heap(c.begin(), c.end(), comp);
    c.pop_back();

    return result;
}

void Storage::TaskQueue::UpdatePriority(const KeyType& key, uint32_t priority)
{
    for (container_type::iterator t = c.begin(); t != c.end(); ++t)
    {
        if (0 == key.compare(t->key))
        {
            if (priority > t->priority)
            {
                t->priority = priority;

                std::make_heap(c.begin(), c.end(), comp);
            }

            break;
        }
    }
}

void Storage::WorkerThread()
{
    LOG_STORAGE->Info("Storage::WorkerThread spawned");

    std::unique_lock<MutexType> lock(m_ordersMutex, std::defer_lock);

    while (!m_workersStopFlag)
    {
        lock.lock();
        m_ordersCV.wait(lock, [&]() { return !m_orders.empty() || m_workersStopFlag; });

        if (m_workersStopFlag)
        {
            LOG_STORAGE->Info("Storage::WorkerThread stop signal received");
            lock.unlock();
            break;
        }

        Task task = m_orders.PopTop();
        lock.unlock();

        LOG_STORAGE->Debug("Async task \"{}\"[{}] -> processing", task.key.c_str(), task.priority);

        Handler handler = CreateHandler(task.key);

        LOG_STORAGE->Debug("Async task \"{}\"[{}] -> publishing handler to entry", task.key.c_str(), task.priority);

        task.promise.set_value(handler);
    }
}

Storage::Storage()
    : m_workersStopFlag(false)
{
}

Storage::~Storage()
{
    StopWorkers();
}

}
}
