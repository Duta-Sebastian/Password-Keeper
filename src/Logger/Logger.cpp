#include "Logger.h"

#include <iomanip>
#include <iostream>
#include <utility>
#include <filesystem>
std::unique_ptr<Logger, Logger::Deleter> Logger::instance = nullptr;
std::once_flag Logger::initFlag;

void Logger::create(const std::string &folderName) {
    std::call_once(initFlag, [&folderName]() {
        instance.reset(new Logger(folderName));
    });
}

Logger &Logger::getInstance() {
    if (!instance) {
        throw std::runtime_error(
            "Logger::create() must be called before getInstance()");
    }
    return *instance;
}

Logger::Logger(std::string folderName): folderName(std::move(folderName)), done(false) {
    const auto currentPath = std::filesystem::current_path() / std::filesystem::path(this->folderName);

    create_directory(currentPath);

    const auto filePath = currentPath.string() / std::filesystem::path(generateTimestampedFilename());

    logFile.open(filePath, std::ios::out | std::ios::app);
    loggingThread = std::thread(&Logger::processEntries, this);
}

Logger::~Logger() {
    if (loggingThread.joinable()) {
        {
            std::lock_guard lock(mutex);
            done = true;
        }
        condVar.notify_all();
        loggingThread.join();
    }
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(const LogLevel logLevel, const std::string &message) {
    std::string levelStr;
    switch (logLevel) {
        case LogLevel::INFO: levelStr = "[INFO]";
            break;
        case LogLevel::WARNING: levelStr = "[WARNING]";
            break;
        case LogLevel::LOG_ERROR: levelStr = "[ERROR]";
            break;
        default: levelStr = "[INFO]";
            break;
    }
    const std::string fullMessage = levelStr + " " + message;
    std::lock_guard lock(mutex);
    logQueue.push(fullMessage);
    condVar.notify_one();
}

void Logger::processEntries() {
    while (true) {
        std::unique_lock lock(mutex);
        condVar.wait(lock, [this] { return !logQueue.empty() || done; });
        while (!logQueue.empty()) {
            logFile << logQueue.front() << std::endl;
            logQueue.pop();
        }
        if (done) break;
    }
}

std::string Logger::generateTimestampedFilename() {
    const auto now = std::chrono::system_clock::now();
    const auto time = std::chrono::system_clock::to_time_t(now);
    std::ostringstream oss;
    oss << "log_"
            << std::put_time(std::localtime(&time), "%Y%m%d_%H%M%S")
            << ".log";
    return oss.str();
}
