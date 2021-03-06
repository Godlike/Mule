#define CATCH_CONFIG_MAIN

#include <mule/Loggers.hpp>
#include <mule/MuleUtilities.hpp>

#include <mule/asset/Content.hpp>
#include <mule/asset/SimpleStorage.hpp>

#include <catch.hpp>

// Files should be located in WORKING_DIRECTORY of the test
static std::string const testFile1("derp.txt");
static std::string const testFile2("herp.txt");

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

    mule::asset::SimpleStorage& storage = mule::asset::SimpleStorage::Instance();

    mule::asset::Handler handler1 = storage.Get(testFile1);
    mule::asset::Handler handler2 = storage.Get(testFile2);

    REQUIRE(true == handler1.IsValid());
    REQUIRE(handler1.GetContent().GetBuffer().size() > 0);

    REQUIRE(true == handler2.IsValid());
    REQUIRE(handler2.GetContent().GetBuffer().size() > 0);

    mule::asset::SimpleStorage::Destroy();
}

TEST_CASE("Creating handlers", "[sync]")
{
    Setup();

    mule::asset::SimpleStorage& storage = mule::asset::SimpleStorage::Instance();

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

    mule::asset::SimpleStorage::Destroy();
}
