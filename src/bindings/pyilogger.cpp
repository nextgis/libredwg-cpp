#include <pyilogger.hpp>

void PyILogger::debug(const std::string &message) {
  PYBIND11_OVERRIDE_PURE(void, ILogger, debug, message);
}

void PyILogger::info(const std::string &message) {
  PYBIND11_OVERRIDE_PURE(void, ILogger, info, message);
}

void PyILogger::warning(const std::string &message) {
  PYBIND11_OVERRIDE_PURE(void, ILogger, warning, message);
}

void PyILogger::error(const std::string &message) {
  PYBIND11_OVERRIDE_PURE(void, ILogger, error, message);
}
