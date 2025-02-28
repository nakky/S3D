
#include "ExampleApp.h"

#include "Home/HomeContent.h"

using namespace S3D;

int main(int argc, char *argv[])
{

    ExampleApp *app = new ExampleApp(
        argc, argv, 
        new HomeContent(), 
        DisplayMode(false, Size2(800, 600)),
        GraphicsMode(true, 60.0f)
    );

    app->init();
    app->run();
    app->cleanup();

    SAFE_DELETE(app);

    exit(EXIT_SUCCESS);
}
