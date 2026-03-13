#ifndef DWG_LOGGING_H
#define DWG_LOGGING_H

#include <dwg.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*Logger)(int message_level, int logging_level, bool is_error,
                       const char *format, ...);

EXPORT void dwg_register_logger(Logger new_logger);

#ifdef __cplusplus
}
#endif

#endif
