#ifndef spincpp_PlayerController_h
#define spincpp_PlayerController_h

#include "Settings.h"
#include "Scene.h"


class PlayerController{

    public:
        PlayerController();
        PlayerController(Scene& sceneRef);
        ~PlayerController();
        void down(int key);
        void up(int key);
        void down(int x, int y);
        void moved(int x, int y);
        Face* up(int x, int y);
        void drawDebug();
    
    private:
        Settings *settings;
        Scene *sceneRef;
        bool userDidDrag;
        bool init();
        bool didSelectFace();
        void update(int key);
        Face* update(int x, int y);
        Face* didSelectFace(int x, int y);
        ofVec3f origin;
        ofVec3f end;
};

#endif
