gtest_deps = [
  dependency('gmock'),
  dependency('gtest'),
]

executable('unit_tests',
  [
    '../src/backtrace_test.cc',
    'unit_tests.cc',
  ],

  dependencies : [ core_dep, gtest_deps ],
  include_directories : default_includes,
)
