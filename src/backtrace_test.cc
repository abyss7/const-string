#include "backtrace.hh"

#include <gtest/gtest.h>

namespace core {

namespace {

// FIXME: make test gtest-independent
const List<String> expected_stack = {
    "out/tests/unit_tests()",
    "void testing::internal::HandleExceptionsInMethodIfSupported<testing::Test, void>(testing::Test*, void "
    "(testing::Test::*)(), char const*)",
    "testing::Test::Run()",
    "testing::TestInfo::Run()",
    "testing::TestCase::Run()",
    "testing::internal::UnitTestImpl::RunAllTests()",
    "bool testing::internal::HandleExceptionsInMethodIfSupported<testing::internal::UnitTestImpl, "
    "bool>(testing::internal::UnitTestImpl*, bool (testing::internal::UnitTestImpl::*)(), char const*)",
    "testing::UnitTest::Run()",
    "out/tests/unit_tests()",
};

}  // namespace

TEST(BacktraceTest, GetStackTrace) {
  // FIXME: check somehow the frames contents.
  //        May use gmock's `StartsWith()`
  for (size_t depth = 0; depth <= expected_stack.size(); ++depth) {
    auto stack = GetStackTrace(depth);
    ASSERT_EQ(depth, stack.size());
  }
}

}  // namespace core
