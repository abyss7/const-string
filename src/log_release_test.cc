#define NDEBUG

#include "log.hh"

#include <gtest/gtest.h>

namespace core {

using ::testing::ExitedWithCode;

using ::testing::internal::CaptureStderr;
using ::testing::internal::CaptureStdout;
using ::testing::internal::GetCapturedStderr;
using ::testing::internal::GetCapturedStdout;

TEST(LogReleaseTest, DefaultVerbosity) {
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

  EXPECT_EQ("error\n", stderr);
  EXPECT_EQ("warning\ninfo\n", stdout);
}

TEST(LogReleaseTest, CustomVerbosity) {
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

  EXPECT_EQ("error\nwarning\n", stderr);
  EXPECT_EQ("trace\n", stdout);
}

TEST(LogReleaseTest, FatalAlwaysWorks) {
  Log::Reset(FATAL, {{TRACE, TRACE}});

  ASSERT_EXIT(LOG(FATAL) << "fatal", ExitedWithCode(1), "fatal");
  DLOG(FATAL) << "fatal";
}

}  // namespace core
