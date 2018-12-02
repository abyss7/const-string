#include "backtrace.hh"

#include <gmock/gmock.h>

namespace core {

namespace {

// FIXME: make test gtest-independent
const List<String> expected_stack = {
    "void testing::internal::HandleExceptionsInMethodIfSupported<testing::Test, void>(testing::Test*, void "
    "(testing::Test::*)(), char const*)",
    "testing::Test::Run()",
    "testing::TestInfo::Run()",
    "testing::TestCase::Run()",
    "testing::internal::UnitTestImpl::RunAllTests()",
    "bool testing::internal::HandleExceptionsInMethodIfSupported<testing::internal::UnitTestImpl, "
    "bool>(testing::internal::UnitTestImpl*, bool (testing::internal::UnitTestImpl::*)(), char const*)",
    "testing::UnitTest::Run()",
    "build/tests/unit_tests()",
};

}  // namespace

using ::testing::StartsWith;

TEST(BacktraceTest, GetStackTrace) {
  for (size_t depth = 0; depth <= expected_stack.size() + 1; ++depth) {
    auto stack = GetStackTrace(depth);
    ASSERT_EQ(depth, stack.size());
    for (auto expected = expected_stack.cbegin(), actual = stack.cbegin(); actual != stack.end();
         ++expected, ++actual) {
      EXPECT_THAT(*actual, StartsWith(*expected));
    }
  }
}

}  // namespace core
