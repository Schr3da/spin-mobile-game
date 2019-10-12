#ifndef __SpinCpp__Face__
#define __SpinCpp__Face__

#include "ofMain.h"
#include "SceneObject.h"
#include "Settings.h"
#include "PositionFactory.h"
#include "Global.h"

class Face : public SceneObject {

    public:
        Face(ofVec3f vec, int size, int color, FaceId identifier);
        Face(ofVec3f vec, int s, int c);
        ~Face();
        virtual void draw();
        virtual bool update();
        void setPosition(ofVec3f &value);
        ofVec3f& getPosition();
        void setSize(int value);
        int getSize();
        void setCurrentColor(int color);
        void setCorrectColor(int color);

        bool toggleSelection(int color);
        void unSelect();
        void select(int color);

        vector<ofVec3f>& getVertices();
        ofMesh& getMesh();
        ofPlanePrimitive& getBoxPrimitive();
        bool isColorPlacedByUser();
        bool userSetCorrectColor();
        void setUnselectable();
        void showCorrectColor();
        void showDefaultColor();
        bool isSelectable();
        scoreStatus::ScoreStatus getScoreInfo();
        int getCorrectColor();
        int getCurrentColor();
        void showUserColor();

    private:
        int size;
        int curColor;
        int corColor;
        int userColor;
        int angle;
        bool selectable;
        ofVec3f rotAxis;
        FaceId identifier;
        bool init(int size, int color, FaceId identifier);
        void setAngleAndRotationAxis();
        virtual bool init();
        bool colorPlacedByUser;
        ofVec3f pos;
        ofPlanePrimitive geometry;
        Settings *settings;
        ofMesh outline;
        virtual void drawDebug();
};

#endif
