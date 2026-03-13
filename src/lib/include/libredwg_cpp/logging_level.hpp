#pragma once

namespace libredwg {

/**
 * Levels of logging messages.
 */
enum class LoggingLevel : int {
  None = 0,
  Error = 1,
  Info = 2,
  Trace = 3,
  Handle = 4,
  Insane = 5,
  All = 9
};

} // namespace libredwg
