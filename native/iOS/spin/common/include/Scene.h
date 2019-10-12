#ifndef __SpinCpp__Scene__
#define __SpinCpp__Scene__

#include "SceneObject.h"
#include "Camera.h"
#include "NavigationGrid.h"
#include "Settings.h"
#include "PositionFactory.h"
#include "Cube.h"
#include "ofxAssimpModelLoader.h"
#include "Global.h"

class Scene: public SceneObject{

    public:
        Scene();
        ~Scene();
        virtual bool update();
        virtual void draw();
        void restartGame();
        void rotate(int direction);
        bool isRotationActive();
        void lockCameraPosition(CameraPosition*);
        void lockCameraPosition();
        void startNewGame(int rows, int colors, int helper);
        bool isGameStarted();
        void setUpCube(int rows, int colors, int helpFaces);
        Cube& getCube();
        Camera& getCamera();
        int getScore(int timeLeft);
        int getNumberOfCorrectFaces();
        int getNumberOfIncorrectFaces();
        int getNumberOfFaces();

        bool showMenuMesh();
        void memorizePhase();
        void placeColorPhase();
        void showResultPhaseWithTimeBonus(int timebonus);

        void loadNextLevel();
        bool toggleFace(Face& face);
        void showSolution();

    private:

        //Scene & operator=(const Scene& other); //RO3: forbids using of = operator, if needed make public and implement
        Scene(const Scene& other); //RO3: forbids using of copy constructor, if needed make public and implement

        ofxAssimpModelLoader menuModel;
        float rotationAngleForIntroMesh;
        bool gameDidStart;
        int backgroundColor;
        Camera camera;
        Cube cube;
        Settings &settings;
        GSSize halfWindowSize;
        NavigationGrid grid;
        virtual bool init();
        virtual void drawDebug();
        bool introAnimate;
        void prepareToPlay();
        int lvlColors;
        int lvlHelpers;
        int lvlRows;
};


#endif
