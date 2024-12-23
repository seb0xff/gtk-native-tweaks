project('gnt', 'c', 'cpp', default_options: ['c_std=c14', 'cpp_std=c++14'])

sources = []
headers = []
dependencies = []
c_args = ['-fPIC']
platform = host_machine.system()

if platform == 'darwin'
  gtk_dep = dependency('gtk4-macos')
  macos_deps = dependency('appleframeworks', modules: ['Cocoa', 'Foundation'])

  dependencies += [gtk_dep, macos_deps]

  sources += [
    'gnt_macos.c',
  ]

  headers += [
    'gnt_macos.h',
  ]

  c_args += ['-xobjective-c']
else
  error('Unsupported platform')
endif

gnt_lib = shared_library(
  'gnt',
  sources,
  c_args: c_args,
  dependencies: [gtk_dep, macos_deps],
)

gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_main_dep')
subdir('test')

gir_includes = ['Gtk-4.0', 'GObject-2.0', 'Gdk-4.0']

gnome = import('gnome')
gnome.generate_gir(
  gnt_lib,
  namespace: 'Gnt',
  identifier_prefix: 'Gnt',
  symbol_prefix: 'gnt',
  nsversion: '0.1',
  sources: [sources, headers],
  dependencies: dependencies,
  includes: gir_includes,
  install: false,
  install_gir: false,
  install_typelib: false,
)
