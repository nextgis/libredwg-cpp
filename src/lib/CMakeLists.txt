add_subdirectory(dwg_logging_override)

set(SOURCES
    ./document.cpp
    ./logging_dispatcher.cpp
)

add_library(libredwg-cpp ${SOURCES})
target_link_libraries(libredwg-cpp PUBLIC redwg)

include(GenerateExportHeader)
set(export_file_name "libredwg_cpp_export_shared.hpp")
generate_export_header(libredwg-cpp EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/include/${export_file_name}")

set(LIBREDWG_CPP_PUBLIC_HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_include_directories(libredwg-cpp
    PUBLIC
        $<BUILD_INTERFACE:${LIBREDWG_CPP_PUBLIC_HEADERS_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../external/libredwg/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/../external/libredwg/src>
)

# =============================================================================
# Installation

set_target_properties(libredwg-cpp PROPERTIES INSTALL_RPATH "$ORIGIN")

include(GNUInstallDirs)

install(TARGETS libredwg-cpp EXPORT mylib_export
    RUNTIME COMPONENT libredwg-cpp
    LIBRARY COMPONENT libredwg-cpp NAMELINK_COMPONENT libredwg-cpp-dev
    ARCHIVE COMPONENT libredwg-cpp-dev
    PUBLIC_HEADER COMPONENT libredwg-cpp-dev
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)
