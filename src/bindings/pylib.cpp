#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <libredwg_cpp/document.hpp>
#include <libredwg_cpp/error.hpp>
#include <libredwg_cpp/logging_dispatcher.hpp>

#include <py_ilogger_wrapper.hpp>
#include <pyilogger.hpp>

PYBIND11_MODULE(libredwg_cpp, m) {
  m.doc() = "Python bindings for libredwg-cpp";

  auto libredwgErrorHandle =
      pybind11::register_exception<libredwg::Error>(m, "Error");
  pybind11::register_exception<libredwg::IOError>(m, "IOError",
                                                  libredwgErrorHandle);
  pybind11::register_exception<libredwg::ParseError>(m, "ParseError",
                                                     libredwgErrorHandle);
  pybind11::register_exception<libredwg::UnsupportedError>(
      m, "UnsupportedError", libredwgErrorHandle);
  pybind11::register_exception<libredwg::ValidationError>(m, "ValidationError",
                                                          libredwgErrorHandle);
  pybind11::register_exception<libredwg::InternalError>(m, "InternalError",
                                                        libredwgErrorHandle);

  pybind11::enum_<libredwg::Version>(m, "Version")
      .value("Invalid", libredwg::Version::INVALID)
      .value("R_1_1", libredwg::Version::R_1_1)
      .value("R_1_2", libredwg::Version::R_1_2)
      .value("R_1_3", libredwg::Version::R_1_3)
      .value("R_1_4", libredwg::Version::R_1_4)
      .value("R_2_0", libredwg::Version::R_2_0)
      .value("R_2_10", libredwg::Version::R_2_10)
      .value("R_2_21", libredwg::Version::R_2_21)
      .value("R_2_22", libredwg::Version::R_2_22)
      .value("R_2_4", libredwg::Version::R_2_4)
      .value("R_2_5", libredwg::Version::R_2_5)
      .value("R_2_6", libredwg::Version::R_2_6)
      .value("R_9", libredwg::Version::R_9)
      .value("R_10", libredwg::Version::R_10)
      .value("R_11", libredwg::Version::R_11)
      .value("R_12", libredwg::Version::R_12)
      .value("R_13", libredwg::Version::R_13)
      .value("R_14", libredwg::Version::R_14)
      .value("R_2000", libredwg::Version::R_2000)
      .value("R_2002", libredwg::Version::R_2002)
      .value("R_2004", libredwg::Version::R_2004)
      .value("R_2007", libredwg::Version::R_2007)
      .value("R_2010", libredwg::Version::R_2010)
      .value("R_2013", libredwg::Version::R_2013)
      .value("R_2018", libredwg::Version::R_2018)
      .value("R_AFTER", libredwg::Version::R_AFTER);

  pybind11::class_<libredwg::Document>(m, "Document")
      .def_static("open", &libredwg::Document::open,
                  pybind11::arg("path_to_dwg"))
      .def("write_dxf", &libredwg::Document::writeDxf,
           pybind11::arg("path_to_dxf"))
      .def("version", &libredwg::Document::version);

  pybind11::class_<libredwg::ILogger, PyILogger,
                   std::shared_ptr<libredwg::ILogger>>(m, "ILogger")
      .def(pybind11::init<>())
      .def("debug", &libredwg::ILogger::debug, pybind11::arg("message"))
      .def("info", &libredwg::ILogger::info, pybind11::arg("message"))
      .def("warning", &libredwg::ILogger::warning, pybind11::arg("message"))
      .def("error", &libredwg::ILogger::error, pybind11::arg("message"));

  pybind11::enum_<libredwg::LoggingLevel>(m, "LoggingLevel")
      .value("NONE", libredwg::LoggingLevel::None)
      .value("ERROR", libredwg::LoggingLevel::Error)
      .value("INFO", libredwg::LoggingLevel::Info)
      .value("TRACE", libredwg::LoggingLevel::Trace)
      .value("HANDLE", libredwg::LoggingLevel::Handle)
      .value("INSANE", libredwg::LoggingLevel::Insane)
      .value("ALL", libredwg::LoggingLevel::All);

  pybind11::class_<
      libredwg::LoggingDispatcher,
      std::unique_ptr<libredwg::LoggingDispatcher, pybind11::nodelete>>(
      m, "LoggingDispatcher")
      .def_static("instance", &libredwg::LoggingDispatcher::instance,
                  pybind11::return_value_policy::reference)
      .def("setLoggingLevel", &libredwg::LoggingDispatcher::setLoggingLevel,
           pybind11::arg("level"))
      .def(
          "setLogger",
          [](libredwg::LoggingDispatcher *dispatcher, pybind11::object logger,
             bool usingLoggingLevel) {
            dispatcher->setLogger(std::make_shared<PythonLoggerWrapper>(logger),
                                  usingLoggingLevel);
          },
          pybind11::arg("logger"), pybind11::arg("usingLoggingLevel") = true);
}
