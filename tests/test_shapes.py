import libredwg_cpp
from utils import LIBREDWG_DATADIR


def test_arc():
    document = libredwg_cpp.Document.open(LIBREDWG_DATADIR + "/2000/Arc.dwg")
    assert document.version() == libredwg_cpp.Version.R_2000
    document.write_dxf("./out_data/arc.dxf")


def test_ellipse():
    document = libredwg_cpp.Document.open(LIBREDWG_DATADIR + "/2000/Ellipse.dwg")
    assert document.version() == libredwg_cpp.Version.R_2000
    document.write_dxf("./out_data/ellipse.dxf")


def test_construction_line():
    document = libredwg_cpp.Document.open(
        LIBREDWG_DATADIR + "/2000/ConstructionLine.dwg"
    )
    assert document.version() == libredwg_cpp.Version.R_2000
    document.write_dxf("./out_data/construction_line.dxf")


def test_point():
    document = libredwg_cpp.Document.open(LIBREDWG_DATADIR + "/2000/Point.dwg")
    assert document.version() == libredwg_cpp.Version.R_2000
    document.write_dxf("./out_data/point.dxf")


def test_line():
    document = libredwg_cpp.Document.open(LIBREDWG_DATADIR + "/2000/Line.dwg")
    assert document.version() == libredwg_cpp.Version.R_2000
    document.write_dxf("./out_data/line.dxf")


def test_multiline():
    document = libredwg_cpp.Document.open(LIBREDWG_DATADIR + "/2000/Multiline.dwg")
    assert document.version() == libredwg_cpp.Version.R_2000
    document.write_dxf("./out_data/multiline.dxf")


def test_polyline():
    document = libredwg_cpp.Document.open(LIBREDWG_DATADIR + "/2000/Polyline.dwg")
    assert document.version() == libredwg_cpp.Version.R_2000
    document.write_dxf("./out_data/polyline.dxf")


def test_polygon():
    document = libredwg_cpp.Document.open(LIBREDWG_DATADIR + "/2000/Polygon.dwg")
    assert document.version() == libredwg_cpp.Version.R_2000
    document.write_dxf("./out_data/polygon.dxf")
