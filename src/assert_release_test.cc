#define NDEBUG

#include "assert.hh"

#include <gtest/gtest.h>

namespace core {

using ::testing::KilledBySignal;

TEST(AssertReleaseTest, DebugCheckOrEvaluate) {
  int a = 1;
  DCHECK_O_EVAL(++a);    // should be evaluated
  DCHECK_O_EVAL(false);  // shouldn't do anything
  ASSERT_EQ(2, a);
}

TEST(AssertReleaseTest, DebugCheck) {
  int a = 1;
  DCHECK(++a);
  DCHECK(false);
  ASSERT_EQ(1, a);
}

TEST(AssertReleaseTest, Check) {
  int a = 1;
  CHECK(++a);
  ASSERT_EXIT(CHECK(false), KilledBySignal(SIGABRT), "Assertion failed: false");
  ASSERT_EQ(2, a);
}

TEST(DISABLED_AssertReleaseTest, NotReached) {
  // FIXME: doesn't die on gcc
  ASSERT_DEATH(NOT_REACHED(), ".*");
}

}  // namespace core
