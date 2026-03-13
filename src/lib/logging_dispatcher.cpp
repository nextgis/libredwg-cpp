#include <dwg_logging.h>
#include <libredwg_cpp/logging_dispatcher.hpp>

#include <cstdarg>

using namespace libredwg;

namespace {

void libredwgCppLogger(int message_level, int logging_level, bool is_error,
                       const char *format, ...) noexcept {
  va_list args;

  va_start(args, format);
  int length = std::vsnprintf(nullptr, 0, format, args);
  va_end(args);

  try {
    if (length > 0) {
      std::vector<char> buffer(length + 1);

      va_start(args, format);
      std::vsnprintf(buffer.data(), buffer.size(), format, args);
      va_end(args);

      LoggingDispatcher::instance().dispatchMessage(
          std::string(buffer.data()), static_cast<LoggingLevel>(message_level),
          is_error);
    } else {
      fprintf(stderr, "Invalid logging message length: %d\n", length);
    }
  } catch (const std::exception &error) {
    fprintf(stderr, "Exception suppressed: %s\n", error.what());
  }
}

} // namespace

LoggingDispatcher &LoggingDispatcher::instance() {
  static LoggingDispatcher loggingDispatcher;
  return loggingDispatcher;
}

void LoggingDispatcher::dispatchMessage(const std::string &message,
                                        LoggingLevel messageLevel,
                                        bool isError) noexcept {
  try {
    if (!checkingLoggingLevel || messageLevel <= loggingLevel) {
      switch (messageLevel) {
      case LoggingLevel::Error: {
        if (isError) {
          logger->error(message);
        } else {
          logger->warning(message);
        }
        break;
      }
      case LoggingLevel::Info: {
        logger->info(message);
        break;
      }
      default: {
        logger->debug(message);
      }
      }
    }
  } catch (const std::exception &error) {
    fprintf(stderr, "Exception in logger suppressed: %s\n", error.what());
  } catch (...) {
    fprintf(stderr, "Unknown exception in logger suppressed\n");
  }
}

void LoggingDispatcher::setLoggingLevel(LoggingLevel level) noexcept {
  loggingLevel = level;
}

void LoggingDispatcher::setLogger(std::shared_ptr<ILogger> newLogger,
                                  bool useLoggingLevel) noexcept {
  if (newLogger) {
    logger = newLogger;
    checkingLoggingLevel = useLoggingLevel;
    dwg_register_logger(libredwgCppLogger);
  }
}
