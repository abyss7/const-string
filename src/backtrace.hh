#pragma once

#include "types.hh"

namespace core {

List<String> GetStackTrace(ui8 depth = 64) noexcept;

}  // namespace core
