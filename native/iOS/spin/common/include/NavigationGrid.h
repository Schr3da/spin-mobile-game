#ifndef __SpinCpp__NavigationGrid__
#define __SpinCpp__NavigationGrid__

#include "SceneObject.h"
#include "Camera.h"
#include "Settings.h"

class NavigationGrid : SceneObject{

    public:
        NavigationGrid();
        virtual void draw();
        virtual bool update();
        CameraPosition* getGridPosition(const ofNode &object);
        CameraPosition* getGridPosition(const LocationVariables& var);
    private:
        Settings &settings;
        virtual bool init();
        virtual void drawDebug();

};


#endif /* defined(__SpinCpp__NavigationGrid__) */
