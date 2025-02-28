

#include "S3D/Graphics/Material.h"

#include "S3D/Graphics/Shader.h"

#include "S3D/Graphics/ShaderLibrary.h"


namespace S3D
{
    //static
    Material Material::defaultMaterial = Material();

    void Material::load(GraphicsContext *context)
    {
        mShader = ShaderLibrary::getShader(mShaderName.c_str());
        if(mShader == NULL) {
            mShader = ShaderLibrary::getDefaultShader();
        }
        mShaderParameter = mShader->createParameter();
    }

    void Material::unload(GraphicsContext *context)
    {
        SAFE_DELETE(mShaderParameter);
    }

}; //namespace S3D