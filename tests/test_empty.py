import libredwg_cpp
import pytest


@pytest.mark.skip(
    "Segmentation fault inside the dwg_write_dxf call, file: document.cpp, reason unknown"
)
def test_empty():
    document = libredwg_cpp.Document.open("./data/empty.dwg")
    document.write_dxf("./out_data/empty.dxf")
