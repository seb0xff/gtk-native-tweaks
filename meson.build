project('gnt', 'c', 'cpp', default_options: ['c_std=c11', 'cpp_std=c++14'])

sources = []
headers = ['gnt.h']
dependencies = []
c_args = ['-fPIC']
platform = host_machine.system()
namespace_suffix = ''

if platform == 'darwin'
  suffix = 'Macos'
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
  install: true,
)

install_headers(
  headers,
  subdir: 'gnt',
)

gir_includes = ['Gtk-4.0', 'GObject-2.0', 'Gdk-4.0']

gnome = import('gnome')
gnome.generate_gir(
  gnt_lib,
  namespace: 'Gnt' + namespace_suffix,
  identifier_prefix: 'Gnt' + namespace_suffix,
  symbol_prefix: 'gnt' + '_' + namespace_suffix.to_lower(),
  nsversion: '0.1',
  sources: [sources, headers],
  dependencies: dependencies,
  includes: gir_includes,
  install: true,
)

pkgconfig = import('pkgconfig')
pkgconfig.generate(
  gnt_lib,
  name: 'gnt-0.1',
  description: 'Gtk Native Tweaks',
  version: '0.1'
)

gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_main_dep')
subdir('test')
