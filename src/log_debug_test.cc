#undef NDEBUG

#include "log.hh"

#include <gtest/gtest.h>

namespace core {

using ::testing::ExitedWithCode;

using ::testing::internal::CaptureStderr;
using ::testing::internal::CaptureStdout;
using ::testing::internal::GetCapturedStderr;
using ::testing::internal::GetCapturedStdout;

TEST(LogDebugTest, DefaultVerbosity) {
  Log::Reset();

  CaptureStderr();
  CaptureStdout();

  LOG(ERROR) << "error";
  LOG(WARNING) << "warning";
  LOG(INFO) << "info";
  LOG(VERBOSE) << "verbose";
  LOG(TRACE) << "trace";

  DLOG(ERROR) << "debug error";
  DLOG(WARNING) << "debug warning";
  DLOG(INFO) << "debug info";
  DLOG(VERBOSE) << "debug verbose";
  DLOG(TRACE) << "debug trace";

  String stderr = GetCapturedStderr();
  String stdout = GetCapturedStdout();

  EXPECT_EQ("error\ndebug error\n", stderr);
  EXPECT_EQ("warning\ninfo\ndebug warning\ndebug info\n", stdout);
}

TEST(LogDebugTest, CustomVerbosity) {
  Log::Reset(WARNING, {{WARNING, FATAL}, {TRACE, TRACE}});

  CaptureStderr();
  CaptureStdout();

  LOG(ERROR) << "error";
  LOG(WARNING) << "warning";
  LOG(INFO) << "info";
  LOG(VERBOSE) << "verbose";
  LOG(TRACE) << "trace";

  DLOG(ERROR) << "debug error";
  DLOG(WARNING) << "debug warning";
  DLOG(INFO) << "debug info";
  DLOG(VERBOSE) << "debug verbose";
  DLOG(TRACE) << "debug trace";

  String stderr = GetCapturedStderr();
  String stdout = GetCapturedStdout();

  EXPECT_EQ("error\nwarning\ndebug error\ndebug warning\n", stderr);
  EXPECT_EQ("trace\ndebug trace\n", stdout);
}

TEST(LogDebugTest, FatalAlwaysWorks) {
  Log::Reset(FATAL, {{TRACE, TRACE}});

  ASSERT_EXIT(LOG(FATAL) << "fatal", ExitedWithCode(1), "fatal");
  ASSERT_EXIT(DLOG(FATAL) << "debug fatal", ExitedWithCode(1), "debug fatal");
}

}  // namespace core
