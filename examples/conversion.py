import libredwg_cpp


LIBREDWG_DATADIR = "../src/external/libredwg/test/test-data/2018/"


def main():
    try:
        document = libredwg_cpp.Document.open(LIBREDWG_DATADIR + "Point.dwg")
        document.write_dxf("./out_data/point.dxf")
        print("Conversion to DXF completed successfully.")
    except libredwg_cpp.Error as error:
        print("An error occurred:", error)


if __name__ == "__main__":
    main()
