#pragma once

#include <libredwg_cpp/ilogger.hpp>
#include <pybind11/pybind11.h>

/**
 * A trampoline class for ILogger interface
 */
class PyILogger : public libredwg::ILogger {
public:
  void debug(const std::string &message) override;

  void info(const std::string &message) override;

  void warning(const std::string &message) override;

  void error(const std::string &message) override;
};
