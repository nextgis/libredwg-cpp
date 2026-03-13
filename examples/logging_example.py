import libredwg_cpp
import logging


LIBREDWG_DATADIR = "../src/external/libredwg/test/test-data/2000/"


def setup_logging():
    logger = logging.getLogger(__name__)
    logging.basicConfig(filename="./output/logging_example.log", level=logging.DEBUG)

    # Register logger in LoggingDispatcher of libredwg to redirect logs.
    libredwg_cpp.LoggingDispatcher.instance().setLogger(logger, False)


def main():
    setup_logging()
    try:
        document = libredwg_cpp.Document.open(LIBREDWG_DATADIR + "Point.dwg")
        document.write_dxf("./out_data/point.dxf")
        print("Conversion to DXF completed successfully.")
    except libredwg_cpp.Error as error:
        print("An error occurred:", error)


if __name__ == "__main__":
    main()
