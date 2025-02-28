#include "S3D/Graphics/IO/PngImageGenerator.h"
#include "S3D/Foundation/FileIO.h"

#include "stb_image.h"

namespace S3D
{
    Image *PngImageGenerator::createImage(const FilePath &path)
    {
        Input *input = NULL;
#if defined OS_ANDROID
        input = new AssetInput(path, true);
#else
        input = new FileInput(path.getSystemPath(), false);
#endif
        if(!input->open()){
            SAFE_DELETE(input);
            return NULL;
        }

        unsigned char *pImage = NULL;
        int width, height, comp;

        pImage = loadFromFile(input, &width, &height, &comp, 3);

        if(comp == 4){
            delete[] pImage;
            input->close();
            input->open();
            pImage = loadFromFile(input, &width, &height, &comp, 4);
        }
        
        input->close();
        SAFE_DELETE(input);

        Image *image = NULL;

        switch(comp){
            case 1:
                {
                    image = new Image(PIXEL_ALPHA8, Size2(width, height), pImage);
                }
                break;
            case 3:
                {
                    image = new Image(PIXEL_RGB24, Size2(width, height), pImage);
                }
                break;
            case 4:
                {
                    image = new Image(PIXEL_RGBA32, Size2(width, height), pImage);
                }
                break;
        }

        return image;
    }

    int readpng(void* user, char* data, int size)
    {
        return (int)((Input *)user)->read(data, size);
    }
    void skippng(void* user, int size)
    {
        ((Input *)user)->seek(size, IO::CURRENT);
    }
    int eofpng(void* user)
    {
        return ((Input *)user)->end();
    }
    
    unsigned char *PngImageGenerator::loadFromFile(Input *input, int *x, int *y, int *comp, int reqComp)
    {
        stbi_io_callbacks callbacks;
        callbacks.read = &readpng;
        callbacks.skip = &skippng;
        callbacks.eof = &eofpng;
        
        return stbi_load_png_from_callbacks(&callbacks, (void*)input, x, y, comp, reqComp);
    }

} // namespace S3D
