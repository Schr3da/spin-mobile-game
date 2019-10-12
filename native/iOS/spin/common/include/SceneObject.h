#ifndef __SpinCpp__SceneObject__
#define __SpinCpp__SceneObject__

#include "ofMain.h"

class SceneObject{

    protected:
        bool instanceCorrectInitialized = false;
    
    private:
        virtual bool init()=0;
        virtual void drawDebug()=0;
    
    public:
        virtual void draw()=0;
        virtual bool update()=0;
};

#endif
