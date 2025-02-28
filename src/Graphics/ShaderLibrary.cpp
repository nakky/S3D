
#include "S3D/Graphics/ShaderLibrary.h"

namespace S3D
{
    //static
    std::map<std::string, Shader*> ShaderLibrary::mShaderMap;
    Shader* ShaderLibrary::mDefaultShader = NULL;

    void ShaderLibrary::retisterShader(const char* name, Shader *shader)
    {
        if(mDefaultShader == NULL) { mDefaultShader = shader; }
        mShaderMap.insert(std::make_pair(name,shader));
    }

    void ShaderLibrary::unretisterShader(const char* name)
    {
        mShaderMap.erase(name);
    }

    Shader *ShaderLibrary::getShader(const char *name)
    {
        auto ite = mShaderMap.find(name);
        if(ite == mShaderMap.end()) return NULL;
        else return (*ite).second;
    }

} // namespace S3D
