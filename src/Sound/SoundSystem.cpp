

#include "S3D/Sound/SoundSystem.h"
#include "S3D/Sound/SoundFactory.h"

#if defined PLAYERAPI_OPENSLES
#include "S3D/Sound/OpenSLES/OpenSLESDriver.h"
#endif

namespace S3D{

#if defined PLAYERAPI_OPENSLES
    SLObjectItf SoundSystem::mEngine = NULL;
    SLEngineItf SoundSystem::mEngineInterface = NULL;
#endif

    /****************************************/
    /*!
        @brief	Initialize
        @note

        @author	Naoto Nakamura
        @date	Apr. 7, 2009
    */
    /****************************************/
    void SoundSystem::init()
    {
        SoundFactory::init();
        SoundFactory::createStandardCreatorSet();
#if defined PLAYERAPI_OPENSLES
        SLresult result;

        SLEngineOption EngineOption[] = {
                SL_ENGINEOPTION_THREADSAFE, SL_BOOLEAN_TRUE,
                SL_ENGINEOPTION_LOSSOFCONTROL, SL_BOOLEAN_TRUE
        };
        result = slCreateEngine(&mEngine, 2, EngineOption, 0, NULL, NULL);
        result = (*mEngine)->Realize(mEngine, SL_BOOLEAN_FALSE);
        result = (*mEngine)->GetInterface(mEngine, SL_IID_ENGINE, &mEngineInterface);
#endif
    }

    /****************************************/
    /*!
        @brief	Cleanup
        @note

        @author	Naoto Nakamura
        @date	Apr. 7, 2009
    */
    /****************************************/
    void SoundSystem::cleanup()
    {
#if defined PLAYERAPI_OPENSLES
        if (mEngine != NULL) {
            (*mEngine)->Destroy(mEngine);
            mEngine = NULL;
            mEngineInterface = NULL;
        }
#endif
        SoundFactory::cleanup();
    }


};	//namespace S3D

