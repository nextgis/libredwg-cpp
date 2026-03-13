#include <py_ilogger_wrapper.hpp>

#include <pybind11/cast.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>

#include <array>
#include <cstdio>

PythonLoggerWrapper::PythonLoggerWrapper(pybind11::object obj)
    : pythonObject(obj) {
  validate_logger_methods();
}

void PythonLoggerWrapper::debug(const std::string &message) {
  callPyObjectLoggingMethod("debug", message);
}

void PythonLoggerWrapper::info(const std::string &message) {
  callPyObjectLoggingMethod("info", message);
}

void PythonLoggerWrapper::warning(const std::string &message) {
  callPyObjectLoggingMethod("warning", message);
}

void PythonLoggerWrapper::error(const std::string &message) {
  callPyObjectLoggingMethod("error", message);
}

void PythonLoggerWrapper::validate_logger_methods() {
  std::array<std::string, 4> required_methods = {"debug", "info", "warning",
                                                 "error"};

  for (const auto &method : required_methods) {
    if (!pybind11::hasattr(pythonObject, method.c_str())) {
      throw std::runtime_error("Object must have a '" + method + "' method");
    }

    auto method_obj = pythonObject.attr(method.c_str());
    if (!pybind11::isinstance<pybind11::function>(method_obj)) {
      throw std::runtime_error("'" + method + "' must be a callable method");
    }
  }
}

void PythonLoggerWrapper::callPyObjectLoggingMethod(
    const char *method, const std::string &message) {
  pybind11::gil_scoped_acquire gil;

  pybind11::handle pythonString =
      PyUnicode_DecodeUTF8(message.data(), message.size(), "replace");

  if (!pythonString) {
    PyErr_Clear();
    return;
  }

  pythonObject.attr(method)(
      pybind11::reinterpret_steal<pybind11::str>(pythonString));
}
