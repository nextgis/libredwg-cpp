import libredwg_cpp
from utils import (
    LIBREDWG_DATADIR,
    LoggerForTest,
    ExceptionalLogger,
    check_message,
    MessageType,
)


def test_logger_registration():
    libredwg_cpp.LoggingDispatcher.instance().setLogger(LoggerForTest(), False)


def test_debug_logging():
    logger = LoggerForTest()

    libredwg_cpp.LoggingDispatcher.instance().setLogger(logger, False)
    document = libredwg_cpp.Document.open(LIBREDWG_DATADIR + "/2000/Point.dwg")
    document.write_dxf("./out_data/point.dxf")

    check_message(
        logger.get_messages()[0],
        MessageType.INFO,
        "This file's version code is: AC1015 (r2000)\n",
    )
    check_message(logger.get_messages()[1], MessageType.DEBUG, "ANSI_1252\n")


def test_logging_exception():
    logger = ExceptionalLogger()

    libredwg_cpp.LoggingDispatcher.instance().setLogger(logger, False)
    document = libredwg_cpp.Document.open(LIBREDWG_DATADIR + "example_2000.dwg")
    document.write_dxf("./out_data/point.dxf")
