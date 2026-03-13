pybind11_add_module(libredwg_cpp
    pylib.cpp 
    py_ilogger_wrapper.cpp 
    pyilogger.cpp
)

target_link_libraries(libredwg_cpp PRIVATE libredwg-cpp)

target_include_directories(libredwg_cpp
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

find_program(PYBIND11_STUBGEN_EXEC pybind11-stubgen)

set(PYTHON_INTERFACE_FILES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../python")

if(PYBIND11_STUBGEN_EXEC)
    add_custom_command(
        TARGET libredwg_cpp
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E env
        PYTHONPATH=$<TARGET_FILE_DIR:libredwg_cpp>
        ${PYBIND11_STUBGEN_EXEC} libredwg_cpp --output-dir ${PYTHON_INTERFACE_FILES_DIR}/libredwg_cpp
        WORKING_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
        COMMENT "Generating .pyi stub with pybind11-stubgen into source directory"
    )
else()
  message(WARNING "pybind11-stubgen not found, using pre-generated stub from source directory.")
endif()

# =============================================================================
# Installation

if(BUILD_PYPROJECT)
    set_target_properties(libredwg_cpp PROPERTIES INSTALL_RPATH "$ORIGIN/../lib/")

    install(TARGETS libredwg_cpp DESTINATION libredwg_cpp)
    install(FILES "${PYTHON_INTERFACE_FILES_DIR}/libredwg_cpp/libredwg_cpp.pyi" DESTINATION ${CMAKE_INSTALL_PREFIX}/libredwg_cpp)
    install(FILES "${PYTHON_INTERFACE_FILES_DIR}/libredwg_cpp/__init__.pyi" DESTINATION ${CMAKE_INSTALL_PREFIX}/libredwg_cpp)
else()
    include(GNUInstallDirs)
    set(BINDINGS_INSTALL_PATH "${CMAKE_INSTALL_LIBDIR}/python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}/dist-packages")

    set_target_properties(libredwg_cpp PROPERTIES INSTALL_RPATH "$ORIGIN/../../")

    install(TARGETS libredwg_cpp EXPORT libredwg_cpp_export
        COMPONENT libredwg_cpp
        LIBRARY DESTINATION ${BINDINGS_INSTALL_PATH}
    )

    install(FILES "${PYTHON_INTERFACE_FILES_DIR}/libredwg_cpp/__init__.pyi"
        COMPONENT libredwg_cpp
        DESTINATION ${BINDINGS_INSTALL_PATH}
    )

    install(FILES "${PYTHON_INTERFACE_FILES_DIR}/libredwg_cpp/libredwg_cpp.pyi"
        COMPONENT libredwg_cpp
        DESTINATION ${BINDINGS_INSTALL_PATH}
    )
endif()
