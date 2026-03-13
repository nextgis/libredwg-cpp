#include <dwg_logging.h>

#include <logging.h>

#include <stdarg.h>
#include <stdio.h>

static void default_logger(int message_level, int logging_level, bool is_error,
                           const char *format, ...) {
  if (message_level <= logging_level) {
    va_list args;
    va_start(args, format);

    if (is_error) {
      if (message_level == DWG_LOGLEVEL_ERROR) {
        fprintf(stderr, "Error: ");
      }
      vfprintf(stderr, format, args);
      fprintf(stderr, "\n");
    } else {
      if (message_level == DWG_LOGLEVEL_ERROR) {
        fprintf(stdout, "Warning: ");
      }
      vfprintf(stdout, format, args);
      fprintf(stdout, "\n");
    }

    va_end(args);
  }
}

Logger dwg_logger = default_logger;

EXPORT void dwg_register_logger(Logger new_logger) { dwg_logger = new_logger; }
