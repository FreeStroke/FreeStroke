#include "../includes/loggertest.h"

#include "../../../Common/includes/logger.h"

LoggerTest::LoggerTest(std::string name) : CppUnit::TestCase(name) {}

void LoggerTest::runTest()
{
    //monothreaded test
    std::string filename = std::string("log_test.txt", false);
    std::string message = std::string("Logger works in monothreaded context");
    std::string package = std::string("TEST");
    Logger *logger = new Logger(filename, false);
    logger->log(message, package, INFO);
    delete logger;

    //multithreaded test

}
