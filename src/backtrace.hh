#pragma once

#include "types.hh"

namespace core {

// TODO: support invocation from signal handlers.
List<String> GetStackTrace(ui8 depth = 64) noexcept;

}  // namespace core
