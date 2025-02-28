#ifndef S3D_APPLICATION_GRAPHICSQUEUETHREAD_H
#define S3D_APPLICATION_GRAPHICSQUEUETHREAD_H

#include "S3D/Common.h"

#include "S3D/Foundation/QueueThread.h"

namespace S3D
{
    class GraphicsContext;

    class GraphicsWorkRequest : public WorkRequest
    {
        friend class GraphicsQueueThread;
        public:
        GraphicsWorkRequest(int priority = PRIORITY_NORMAL, bool isAutoDeleteObject = true)
        :WorkRequest(priority, isAutoDeleteObject),
        mContext(NULL)
        {}

        protected:
        void addGraphicsContext(GraphicsContext *context){ mContext = context; }

        protected:
        GraphicsContext *mContext;

    };

    class GraphicsQueueThread : public QueueThread
    {
    public:
        GraphicsQueueThread(
            GraphicsContext *context,
            bool makeSubContextInInit = false,
            RequestContainer *container = NULL,
            bool isComtainerAutoDelete = TRUE,
            const unsigned long idleTime = 0xFFFFFFFF,
            Condition *sharedCondition = NULL,
            const int priority = PRIORITY_NORMAL,
            const int bindIndex = -1
            )
        :QueueThread(container, isComtainerAutoDelete, idleTime, sharedCondition, priority, bindIndex),
        mParentContext(context),
        mMakeSubContextInInit(makeSubContextInInit),
        mSetup(false)
        {
        }

        virtual ~GraphicsQueueThread(){}

        virtual void init();
        virtual void cleanup();

        virtual void run();

        virtual bool addRequest(WorkRequest *req, const bool resume = TRUE);

        bool isSetup() { return mSetup.load(); }

    protected:
        GraphicsContext *mParentContext;
        GraphicsContext *mContext;
        bool mMakeSubContextInInit;
        std::atomic<bool> mSetup;

    };

}; //namespace S3D

#endif //S3D_APPLICATION_GRAPHICSQUEUETHREAD_H
