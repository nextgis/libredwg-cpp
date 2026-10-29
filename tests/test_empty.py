import libredwg_cpp


def test_empty():
    document = libredwg_cpp.Document.open("./data/empty.dwg")
    document.write_dxf("./out_data/empty.dxf")
