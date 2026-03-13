#pragma once

#include <libredwg_cpp_export_shared.hpp>
#include <string>

namespace libredwg {
/**
 * This class represents the interface for logger object.
 */
class LIBREDWG_CPP_EXPORT ILogger {
public:
  virtual ~ILogger() = default;

  /**
   * Logs a debug message. Corresponds the Trace logging level and higher.
   * \param message message to log
   */
  virtual void debug(const std::string &message) = 0;

  /**
   * Logs an information message. Corresponds the Info logging level.
   * \param message message to log
   */
  virtual void info(const std::string &message) = 0;

  /**
   * Logs a warning message. Corresponds the Error logging level.
   * \param message message to log
   */
  virtual void warning(const std::string &message) = 0;

  /**
   * Logs an error message. Corresponds the Error logging level.
   * \param message message to log
   */
  virtual void error(const std::string &message) = 0;
};

} // namespace libredwg
