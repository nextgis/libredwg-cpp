#pragma once

#include <libredwg_cpp/ilogger.hpp>
#include <pybind11/pybind11.h>

/**
 * Wrapper for Python object, which can be used as ILogger.
 */
class PythonLoggerWrapper : public libredwg::ILogger {
public:
  /**
   * Constructs wrapper from Python object.
   * \param obj Python object with debug, info, warning and error methods.
   */
  PythonLoggerWrapper(pybind11::object obj);

  /**
   * Implements ILogger::debug by calling the method of the wrapped object with
   * the same name.
   */
  void debug(const std::string &message) override;

  /**
   * Implements ILogger::info by calling the method of the wrapped object with
   * the same name.
   */
  void info(const std::string &message) override;

  /**
   * Implements ILogger::warning by calling the method of the wrapped object
   * with the same name.
   */
  void warning(const std::string &message) override;

  /**
   * Implements ILogger::error by calling the method of the wrapped object with
   * the same name.
   */
  void error(const std::string &message) override;

private:
  void validate_logger_methods();

  void callPyObjectLoggingMethod(const char *method,
                                 const std::string &message);

private:
  pybind11::object pythonObject;
};
