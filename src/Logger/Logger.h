#ifndef LOGGER_H
#define LOGGER_H
#include <condition_variable>
#include <fstream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

enum class LogLevel {
  INFO,
  WARNING,
  LOG_ERROR
};


class Logger {
  struct Deleter {
    void operator()(const Logger *logger) const {
      delete logger;
    }
  };

  std::string folderName;
  std::ofstream logFile;
  std::queue<std::string> logQueue;
  std::mutex mutex;
  std::condition_variable condVar;
  std::thread loggingThread;
  std::atomic<bool> done;

  static std::unique_ptr<Logger, Deleter> instance;
  static std::once_flag initFlag;

  explicit Logger(std::string);

  void processEntries();

  static std::string generateTimestampedFilename() ;

protected:
  ~Logger();

public:
  static void create(const std::string &);

  static Logger &getInstance();

  Logger(const Logger &) = delete;

  Logger &operator=(const Logger &) = delete;

  Logger(Logger &&) = delete;

  Logger &operator=(Logger &&) = delete;

  void log(LogLevel, const std::string &);
};


#endif //LOGGER_H
