#ifndef __SpinCpp__Camera__
#define __SpinCpp__Camera__

#include <ofMain.h>
#include "CameraPosition.h"
#include "SceneObject.h"
#include "Settings.h"
#include "PositionFactory.h"

class Camera: public SceneObject{

    public:
        Camera();
        virtual bool init();
        virtual bool update();
        virtual void draw();
        ofEasyCam& getCamera();
        bool initCameraPositions();
        bool isRotationActive();
        bool lookAtPosition();
        void updateCurrentPosition(CameraPosition* newPosition, bool savePreviousPosition);
        CameraPosition* getCurrentPosition() const;
        void activateRotation();
        void reset();
    
    private:
        ofEasyCam camera;
        float x;
        CameraPosition *currentPosition;
        Settings *settings;
        bool rotationActive;
        virtual void drawDebug();

        CameraPosition *previousPosition;
        ofVec3f positionRotationAxis;
        ofVec3f axisRotationAxis;
        float positionRotationAngle;
        float axisRotationAngle;
        int rotationSpeed;
        int rotationCounter;
        void setUpRotationVariables();
        void setPreviousAxisAndPosition(ofVec3f& position, ofVec3f& axis);

};

#endif
