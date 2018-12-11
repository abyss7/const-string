gtest_deps = [
  dependency('gmock'),
  dependency('gtest'),
]

executable('unit_tests',
  [
    '../src/assert_debug_test.cc',
    '../src/assert_release_test.cc',
    '../src/backtrace_test.cc',
    '../src/log_debug_test.cc',
    '../src/log_release_test.cc',
    'unit_tests.cc',
  ],

  dependencies : [ core_dep, gtest_deps ],
  include_directories : default_includes,
)
