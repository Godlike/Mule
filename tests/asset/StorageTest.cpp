#define CATCH_CONFIG_MAIN

#include <mule/Loggers.hpp>
#include <mule/MuleUtilities.hpp>

#include <mule/asset/Content.hpp>
#include <mule/asset/Storage.hpp>

#include <spdlog/sinks/stdout_sinks.h>

#include <catch.hpp>

// Files should be located in WORKING_DIRECTORY of the test
static std::string const testFile1("derp.txt");
static std::string const testFile2("derpiness.txt");
static std::string const testFile3("herp.txt");

void Setup()
{
    mule::Loggers::Instance().SetDefaultSettings(
        mule::Loggers::Settings{
            std::string()
            , std::string("%+")
            , mule::LogLevel::trace
            , { std::make_shared<spdlog::sinks::stdout_sink_st>() }
        }
    );

    mule::MuleUtilities::Initialize();
}

TEST_CASE("Content check", "[basic]")
{
    Setup();

    mule::asset::Storage& storage = mule::asset::Storage::Instance();

    mule::asset::Handler handler1 = storage.Get(testFile1);
    mule::asset::Handler handler2 = storage.Get(testFile2);
    mule::asset::Handler handler3 = storage.Get(testFile3);

    REQUIRE(true == handler1.IsValid());
    REQUIRE(handler1.GetContent().GetBuffer().size() > 0);

    REQUIRE(true == handler2.IsValid());
    REQUIRE(handler2.GetContent().GetBuffer().size() > 0);

    REQUIRE(true == handler3.IsValid());
    REQUIRE(handler3.GetContent().GetBuffer().size() > 0);

    mule::asset::Storage::Destroy();
}

TEST_CASE("Creating sync handlers", "[sync]")
{
    Setup();

    mule::asset::Storage& storage = mule::asset::Storage::Instance();

    SECTION("handlers to the same file")
    {
        mule::asset::Handler handler1 = storage.Get(testFile1);
        mule::asset::Handler handler2 = storage.Get(testFile1);

        REQUIRE(handler1 == handler2);
    }

    SECTION("handlers to different files")
    {
        mule::asset::Handler handler1 = storage.Get(testFile1);
        mule::asset::Handler handler2 = storage.Get(testFile2);

        REQUIRE(handler1 != handler2);
    }

    mule::asset::Storage::Destroy();
}

TEST_CASE("Creating async handlers", "[async]")
{
    Setup();

    mule::asset::Storage& storage = mule::asset::Storage::Instance();

    storage.InitializeWorkers(1);

    SECTION("handlers to the same file")
    {
        std::shared_future<mule::asset::Handler> handler1 = storage.GetAsync(testFile1);
        std::shared_future<mule::asset::Handler> handler2 = storage.GetAsync(testFile1);

        REQUIRE(handler1.get() == handler2.get());
    }

    SECTION("handlers to different files")
    {
        std::shared_future<mule::asset::Handler> handler1 = storage.GetAsync(testFile1);
        std::shared_future<mule::asset::Handler> handler2 = storage.GetAsync(testFile3);

        REQUIRE(handler1.get() != handler2.get());
    }

    mule::asset::Storage::Destroy();
}

TEST_CASE("Mixed handlers", "[sync][async]")
{
    Setup();

    mule::asset::Storage& storage = mule::asset::Storage::Instance();

    storage.InitializeWorkers(1);

    SECTION("handlers to the same file")
    {
        std::shared_future<mule::asset::Handler> handler1 = storage.GetAsync(testFile1);
        mule::asset::Handler handler2 = storage.Get(testFile1);

        REQUIRE(handler1.get() == handler2);
    }

    SECTION("handlers to different files")
    {
        std::shared_future<mule::asset::Handler> handler1 = storage.GetAsync(testFile1);
        mule::asset::Handler handler2 = storage.Get(testFile2);

        REQUIRE(handler1.get() != handler2);
    }

    mule::asset::Storage::Destroy();
}
