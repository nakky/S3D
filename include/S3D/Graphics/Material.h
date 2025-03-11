#ifndef S3D_MATERIAL_H
#define S3D_MATERIAL_H

#include "S3D/Graphics/Math/MathematicsTypes.h"

#include "S3D/Foundation/Resource.h"
#include "S3D/Graphics/Texture.h"


namespace S3D
{
    //implemented
    class Material;

    //required
    class Shader;
    class ShaderParameter;

    class Material : public Resource
    {
    public:
        Material()
            : Resource(),
              mShader(NULL),
              mIsOpaque(true)
        {
        }

        virtual ~Material() {}

        virtual void load(GraphicsContext *context);
        virtual void unload(GraphicsContext *context);

        virtual const short getResourceType() { return RESOURCETYPE_MATERIAL; }

        const char* getShaderName() { return mShaderName.c_str(); }
        void setShaderName(const char *name) { mShaderName = name; }

        Shader *getShader() const { return mShader; }
        void setShader(Shader *shader) { mShader = shader; }
       
        const ShaderParameter *getShaderParameter() const { return mShaderParameter; }

        const bool isOpaque() const { return mIsOpaque; }
        void setOpaque(const bool opaque){ mIsOpaque = opaque; }

        static Material defaultMaterial;
    protected:
        std::string mShaderName;
        Shader * mShader;
        ShaderParameter * mShaderParameter;

        bool mIsOpaque;
    };
}

#endif // S3D_MATERIAL_H
