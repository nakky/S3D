
#include "S3D/Common.h"
#include "S3D/Graphics/GraphicsSystem.h"
#include "S3D/Sound/SoundSystem.h"

namespace S3D
{

    void init()
    {
        GraphicsSystem::init();
        SoundSystem::init();
    }

    void cleanup()
    {
        SoundSystem::cleanup();
        GraphicsSystem::cleanup();
    }

}; // namespace S3D
