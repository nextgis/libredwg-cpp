target_sources(redwg PRIVATE ${CMAKE_CURRENT_LIST_DIR}/dwg_logging.c)

target_include_directories(redwg
    PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_compile_definitions(redwg PRIVATE LOGGING_H)
if (MSVC)
    target_compile_options(redwg PRIVATE /FI "${CMAKE_CURRENT_LIST_DIR}/custom_logging.h")
else()
    target_compile_options(redwg PRIVATE -include "${CMAKE_CURRENT_LIST_DIR}/custom_logging.h")
endif()
