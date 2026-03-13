#pragma once

#include <functional>
#include <memory>

#include <libredwg_cpp/ilogger.hpp>
#include <libredwg_cpp/logging_level.hpp>
#include <libredwg_cpp_export_shared.hpp>

namespace libredwg {

/**
 * Global logging dispatcher for LibreDWG library. This class is Singleton.
 */
class LIBREDWG_CPP_EXPORT LoggingDispatcher final {
public:
  LoggingDispatcher(const LoggingDispatcher &) = delete;
  LoggingDispatcher(LoggingDispatcher &&) = delete;

  void operator=(const LoggingDispatcher &) = delete;
  void operator=(LoggingDispatcher &&) = delete;

  /**
   * Returns single instance of this class.
   */
  static LoggingDispatcher &instance();

  /**
   * Sends message to logger by calling its method, corresponding to
   * messageLevel.
   * \param message Message to log.
   * \param messageLevel Message importance level.
   * \param isError A flag that determines whether the message is an error or a
   * warning.
   */
  void dispatchMessage(const std::string &message, LoggingLevel messageLevel,
                       bool isError) noexcept;

  /**
   * Sets logging level of dispatcher. All messages with the lower level will be
   * ignored.
   * \param level Level of logging messages.
   * \details This level is used only if usingLoggingLevel is set to true.
   * \sa LoggingDispatcher::setLogger
   */
  void setLoggingLevel(LoggingLevel level) noexcept;

  /**
   * Sets the logger.
   * \param logger Logger to be set. Should not be nullptr.
   * \param useLoggingLevel If true, dispatcher will filter messages by the
   * level set via setLoggingLevel, otherwise all messages will be passed to the
   * logger.
   */
  void setLogger(std::shared_ptr<ILogger> logger,
                 bool usingLoggingLevel = true) noexcept;

private:
  LoggingDispatcher() = default;
  ~LoggingDispatcher() = default;

private:
  LoggingLevel loggingLevel = LoggingLevel::Error;
  std::shared_ptr<ILogger> logger;
  bool checkingLoggingLevel = true;
};

} // namespace libredwg
