
#include "S3D/Graphics/Image.h"

namespace S3D
{
    void Image::init()
    {

    }

    void Image::cleanup()
    {
        if(mBuffer != NULL) SAFE_DELETE_ARRAY(mBuffer);
    }
    
} // namespace S3D

