test_cpp_args = ['-DINTERACTIVE_TEST=' + (get_option('interactive_test') ? '1' : '0')]

test_implemented = true

if platform == 'darwin'
  e = executable(
    'gnt-macos-test',
    'gnt_macos_test.cc',
    link_with: gnt_lib,
    include_directories: ['.', '..'],
    dependencies: [dependencies, gtest_dep],
    cpp_args: test_cpp_args,
  )
else
  message('No tests for this platform yet')
  test_implemented = false
endif

if test_implemented
  # if interactive_test run test without timeout
  if get_option('interactive_test')
    test('gnt', e, timeout: 0)
  else
    test('gnt', e)
  endif
endif
