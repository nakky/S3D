cmake = import('cmake')

inc = include_directories([
  './include',
  '../include',
  ])

srcs = [
  './src/example.cpp',
  './src/ExampleApp.cpp',
  './src/Home/HomeContent.cpp',
]

glfw_proj = cmake.subproject('glfw')
glfw_dep = glfw_proj.dependency('glfw')

deps = [
  s3d_dep,
  glfw_dep,
]

if ['windows'].contains(host_machine.system())
  c_compiler = meson.get_compiler('c')
  winmm_dep = c_compiler.find_library('winmm', required: true)
  deps += winmm_dep

elif ['darwin'].contains(host_machine.system())
  
  cocoa_dep = dependency('cocoa', required: true)
  deps += cocoa_dep
  iokit_dep = dependency('IOKit', required: true)
  deps += iokit_dep

elif ['linux'].contains(host_machine.system())

endif

#install assets
base_dir = meson.current_source_dir()
install_subdir(base_dir + '/assets', install_dir: base_dir + '/../build/examples')

executable(
  'example',
  srcs,
  install: false,
  include_directories: inc,
  dependencies: deps,
  cpp_args: cpp_define_args,
)

