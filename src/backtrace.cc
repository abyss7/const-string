#include "backtrace.hh"

#include <cxxabi.h>
#include <execinfo.h>

namespace {

using namespace core;

template <class T>
struct FreeDeleter {
  void operator()(T* ptr) { free(ptr); }
};

String Demangle(const char* frame) {
  const String string = frame;

  const auto begin_name = string.find_last_of('(') + 1;
  if (begin_name == String::npos) {
    return string;
  }

  const auto end_name = string.find('+', begin_name);
  if (end_name == String::npos) {
    return string;
  }

  int status;
  UniquePtr<char, FreeDeleter<char>> demangled_frame(
      abi::__cxa_demangle(string.substr(begin_name, end_name - begin_name).c_str(), nullptr, nullptr, &status));
  if (status == 0) {
    return String(demangled_frame.get());
  } else {
    return frame;
  }
}

}  // namespace

namespace core {

List<String> GetStackTrace(ui8 depth) noexcept {
  using void_ptr = void*;
  UniquePtr<void_ptr[]> buffer(new void_ptr[depth + 2]);
  List<String> frames;

  auto size = backtrace(buffer.get(), depth + 2);
  UniquePtr<char*, FreeDeleter<char*>> symbols(backtrace_symbols(buffer.get(), size));

  // Skip two last frames always look like:
  //     backtrace
  //     core::GetStackTrace(…)

  for (int i = 2; i < size; ++i) {
    frames.push_back(Demangle(symbols.get()[i]));
    // TODO: implement prettifiers here.
  }

  return frames;
}

}  // namespace core
