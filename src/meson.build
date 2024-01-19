s3d_inc = include_directories('../include')

s3d_srcs = [
  'Common.cpp',
  'CPU.cpp',
  'Math/GeometricNode.cpp',
  'Math/MathematicSystem.cpp',
  'Math/Matrix.cpp',
  'Math/Quaternion.cpp',
  'Math/Vector.cpp',
  'Color.cpp',
  'Entity.cpp',
  'Camera.cpp',
  'RootEntity.cpp',
  'Cluster.cpp',
  'RenderList.cpp',
  'Function/EntityFunction.cpp',
]


s3d_lib = static_library('s3d',
                s3d_srcs,
                install: true,
                include_directories: s3d_inc,
                cpp_args: cpp_define_args
                )
