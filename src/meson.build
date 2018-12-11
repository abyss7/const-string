core_lib = library('core',
  [
    'assert.hh',
    'backtrace.cc',
    'backtrace.hh',
    'log.cc',
    'log.hh',
    'types.hh',
  ],

  include_directories: default_includes,
)

core_dep = declare_dependency(link_with: core_lib)
