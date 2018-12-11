#include "log.hh"

#include "assert.hh"

#include <iostream>

namespace core {

namespace {

const ui8 default_error_mark = ERROR;
const Log::RangeSet default_range_set{{INFO, FATAL}};

}

// static
void Log::Reset() {
  Log::error_mark() = default_error_mark;
  Log::ranges().reset(new RangeSet(default_range_set));
}

// static
void Log::Reset(ui8 error_mark, RangeSet&& ranges) {
  ui8 prev = 0;
  for (const auto& range : ranges) {
    if ((prev > 0 && range.second <= prev) || range.second > range.first) {
      NOT_REACHED();
    }
    prev = range.first;
  }

  Log::error_mark() = error_mark;
  Log::ranges().reset(new RangeSet(std::move(ranges)));
}

Log::Log(Level level) : _level(level), _error_mark(error_mark()), _ranges(ranges()) {}

Log::~Log() {
  auto it = _ranges->lower_bound(std::make_pair(_level, 0));
  if ((it != _ranges->end() && _level >= it->second) || _level <= ASSERT) {
    _stream << std::endl;

    auto& output_stream = (_level <= _error_mark) ? std::cerr : std::cout;
    output_stream << _stream.str() << std::flush;
  }

  if (_level == FATAL) {
    std::exit(EXIT_FAILURE);
  }

  if (_level == ASSERT) {
    std::abort();
    // FIXME: throw exception by default.
  }
}

// static
ui8& Log::error_mark() {
  static ui8 error_mark = default_error_mark;
  return error_mark;
}

// static
SharedPtr<Log::RangeSet>& Log::ranges() {
  static SharedPtr<RangeSet> ranges(new RangeSet(default_range_set));
  return ranges;
}

}  // namespace core
