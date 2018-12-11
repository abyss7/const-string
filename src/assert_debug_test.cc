#undef NDEBUG

#include "assert.hh"

#include <gtest/gtest.h>

namespace core {

using ::testing::KilledBySignal;

TEST(AssertDebugTest, DebugCheckOrEvaluate) {
  int a = 1;
  DCHECK_O_EVAL(++a);  // should be evaluated
  ASSERT_EXIT(DCHECK_O_EVAL(false), KilledBySignal(SIGABRT), "Assertion failed: false");
  ASSERT_EQ(2, a);
}

TEST(AssertDebugTest, DebugCheck) {
  int a = 1;
  DCHECK(++a);
  ASSERT_EXIT(DCHECK(false), KilledBySignal(SIGABRT), "Assertion failed: false");
  ASSERT_EQ(2, a);
}

TEST(AssertDebugTest, Check) {
  int a = 1;
  CHECK(++a);
  ASSERT_EXIT(CHECK(false), KilledBySignal(SIGABRT), "Assertion failed: false");
  ASSERT_EQ(2, a);
}

TEST(AssertDebugTest, NotReached) {
  ASSERT_EXIT(NOT_REACHED(), KilledBySignal(SIGABRT), "Assertion failed:.*NOT_REACHED");
}

}  // namespace core
