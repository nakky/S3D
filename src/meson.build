s3d_inc = [
  '../include',
  '../subprojects/glfw/include',
]

s3d_srcs = [
  'Common.cpp',
  'Foundation/CPU.cpp',
  'Foundation/FileIO.cpp',
  'Foundation/FilePath.cpp',
  'Foundation/Lock.cpp',
  'Foundation/Thread.cpp',
  'Foundation/QueueThread.cpp',
  'Foundation/ThreadDriver.cpp',
  'Foundation/QueueThreadPool.cpp',
  'Foundation/Timer.cpp',
  'Foundation/ResourceDataBase.cpp',
  'Graphics/Math/Matrix.cpp',
  'Graphics/Math/Quaternion.cpp',
  'Graphics/Math/Vector.cpp',
  'Graphics/GeometricNode.cpp',
  'Graphics/Color.cpp',
  'Graphics/Material.cpp',
  'Graphics/Camera.cpp',
  'Graphics/GraphicsSystem.cpp',
  'Graphics/Shader.cpp',
  'Graphics/ShaderLibrary.cpp',
  'Graphics/ImageFactory.cpp',
  'Graphics/IO/PngImageGenerator.cpp',
  'Graphics/IO/stb_image.cpp',
  'Graphics/Texture.cpp',
  'Graphics/Image.cpp',
  'Sound/SoundBuffer.cpp',
  'Sound/SoundDriver.cpp',
  'Sound/SoundEffector.cpp',
  'Sound/SoundFileDescriptor.cpp',
  'Sound/SoundSystem.cpp',
  'Sound/SoundFactory.cpp',
  'Sound/WavFileCreator.cpp',
  'Application/App.cpp',
  'Application/ContentApp.cpp',
  'Application/GraphicsQueueThread.cpp',
  'Application/DrawScheme.cpp',
  'Application/DrawScheme/SimpleDrawScheme.cpp',
  'Application/DrawScheme/ThreadedDrawScheme.cpp',
  'Application/GraphicsFactory.cpp',
  'Game/Entity.cpp',
  'Game/RenderList.cpp',
  'Game/Content.cpp',
  'Game/Function/EntityFunction.cpp',
  'Game/Function/CameraFunction.cpp',
  'Game/Function/MeshRendererFunction.cpp',
  'Game/Function/RotatingFunction.cpp',
]

if ['windows'].contains(host_machine.system())

  #W32 Thread
  s3d_srcs += 'Foundation/Drivers/W32/W32ThreadDriver.cpp'

  #GLFW
  s3d_inc += '../include/S3D/Application/Drivers/GLFW'
  s3d_srcs += 'Application/Drivers/GLFW/glad.cpp'
  s3d_srcs += 'Application/Drivers/GLFW/GLFWAppDriver.cpp'
  s3d_srcs += 'Application/Drivers/GLFW/GLFWGraphicsContext.cpp'

  #OpenGL
  s3d_srcs += 'Graphics/Drivers/OpenGL3/OpenGL3Renderer.cpp'
  s3d_srcs += 'Graphics/Drivers/OpenGL3/OpenGL3RenderFrameDriver.cpp'
  s3d_srcs += 'Graphics/Drivers/OpenGL3/OpenGL3TextureDriver.cpp'
  s3d_srcs += 'Graphics/Drivers/OpenGL3/OpenGL3MeshDriver.cpp'
  s3d_srcs += 'Graphics/Drivers/OpenGL3/Shaders/GLSL3Shader.cpp'
  s3d_srcs += 'Graphics/Drivers/OpenGL3/Shaders/GLSL3DefaultShader.cpp'
  s3d_srcs += 'Graphics/Drivers/OpenGL3/Shaders/GLSL3UnlitShader.cpp'

  #MME
  s3d_srcs += 'Sound/Drivers/MME/MMEDriver.cpp'

elif ['darwin'].contains(host_machine.system())

  #PThread
  s3d_srcs += 'Foundation/Drivers/PThread/PThreadThreadDriver.cpp'
  
  #GLFW
  s3d_inc += '../include/S3D/Application/Drivers/GLFW'
  s3d_srcs += 'Application/Drivers/GLFW/glad.cpp'
  s3d_srcs += 'Application/Drivers/GLFW/GLFWAppDriver.cpp'
  s3d_srcs += 'Application/Drivers/GLFW/GLFWGraphicsContext.cpp'

  #OpenGL
  s3d_srcs += 'Graphics/Drivers/OpenGL3/OpenGL3Renderer.cpp'
  s3d_srcs += 'Graphics/Drivers/OpenGL3/OpenGL3RenderFrameDriver.cpp'
  s3d_srcs += 'Graphics/Drivers/OpenGL3/OpenGL3TextureDriver.cpp'
  s3d_srcs += 'Graphics/Drivers/OpenGL3/OpenGL3MeshDriver.cpp'
  s3d_srcs += 'Graphics/Drivers/OpenGL3/Shaders/GLSL3Shader.cpp'
  s3d_srcs += 'Graphics/Drivers/OpenGL3/Shaders/GLSL3DefaultShader.cpp'
  s3d_srcs += 'Graphics/Drivers/OpenGL3/Shaders/GLSL3UnlitShader.cpp'

  #CoreAudio
  s3d_srcs += 'Sound/Drivers/CoreAudio/CoreAudioDriver.mm'

elif ['linux'].contains(host_machine.system())
  
  s3d_inc += '/usr/include'
  
  #PThread
  s3d_srcs += 'Foundation/Drivers/PThread/PThreadThreadDriver.cpp'
  
  #GLFW
  s3d_inc += '../include/S3D/Application/Drivers/GLFW'
  s3d_srcs += 'Application/Drivers/GLFW/glad.cpp'
  s3d_srcs += 'Application/Drivers/GLFW/GLFWAppDriver.cpp'
  s3d_srcs += 'Application/Drivers/GLFW/GLFWGraphicsContext.cpp'

  #OpenGL
  s3d_srcs += 'Graphics/Drivers/OpenGL3/OpenGL3Renderer.cpp'
  s3d_srcs += 'Graphics/Drivers/OpenGL3/OpenGL3RenderFrameDriver.cpp'
  s3d_srcs += 'Graphics/Drivers/OpenGL3/OpenGL3TextureDriver.cpp'
  s3d_srcs += 'Graphics/Drivers/OpenGL3/OpenGL3MeshDriver.cpp'
  s3d_srcs += 'Graphics/Drivers/OpenGL3/Shaders/GLSL3Shader.cpp'
  s3d_srcs += 'Graphics/Drivers/OpenGL3/Shaders/GLSL3DefaultShader.cpp'
  s3d_srcs += 'Graphics/Drivers/OpenGL3/Shaders/GLSL3UnlitShader.cpp'

  #ALSA
  s3d_srcs += 'Sound/Drivers/ALSA/ALSADriver.cpp'

endif


s3d_lib = static_library('s3d',
                s3d_srcs,
                install: true,
                include_directories: include_directories(s3d_inc),
                cpp_args: cpp_define_args
                )
