# LibreDWG-Cpp
C++ Wrapper around LibreDWG C library - free implementation of the DWG file format.
LibreDWG-Cpp allows to convert DWG file to DXF.
Also, LibreDWG-Cpp provides a Python API.
## Installation to Virtualenv
1. Install dependecies:
```
    build-essential
    cmake
```
2. Create virtualenv, activate it and install the package there:
```bash
$ python3 -m venv env
$ source env/bin/activate
$ pip install --editable ./[dev,tests]
```
3. Run the tests:
```bash
$ cd tests
$ mkdir -p ./out_data
$ python -m pytest
```
## Running Python Tests in Docker
To run Python tests in Docker container, based on Ubuntu, use:
```bash
$ docker build -t libredwg-cpp .
```
## Usage Example (Python)
```python
import libredwg_cpp

try:
    document = libredwg_cpp.Document.open("path-to-dwg-file.dwg")
    print("'path-to-dwg-file.dwg' was successfully opened. It's version:", document.version())

    document.write_dxf("path-to-target-dxf-file.dxf")
    print("Convertation to DXF completed successfully.")
except libredwg_cpp.Error as error:
    print("An error occurred:", error)
```

See the `./examples` directory for more examples.
## Developer Notes

This project uses pre-commit to enforce code quality standards.

First, make sure pre-commit is installed:
```bash
$ pip install pre-commit
```
Then, enable it in the project by running:
```bash
$ pre-commit install
```
