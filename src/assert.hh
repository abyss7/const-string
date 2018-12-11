#pragma once

#include "backtrace.hh"
#include "log.hh"

#define CHECK(expr)                               \
  if (!(expr))                                    \
  [] {                                            \
    using namespace ::core;                       \
    using namespace ::std;                        \
                                                  \
    const auto& frames = GetStackTrace();         \
    Log log(ASSERT);                              \
    log << "Assertion failed: " << #expr << endl; \
    for (const auto& frame : frames) {            \
      log << "\t" << frame << endl;               \
    }                                             \
                                                  \
    return log;                                   \
  }()

#if defined(NDEBUG)
#define DCHECK_O_EVAL(expr) (void)(expr)
#define DCHECK(expr)
#define NOT_REACHED() __builtin_unreachable()
#else
#define DCHECK_O_EVAL(expr) CHECK(expr)
#define DCHECK(expr) CHECK(expr)
#define NOT_REACHED() DCHECK(false) << "NOT_REACHED"
#endif
