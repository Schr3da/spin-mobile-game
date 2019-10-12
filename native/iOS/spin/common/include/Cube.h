#ifndef spincpp_Cube_h
#define spincpp_Cube_h

#include <ofMain.h>
#include "SceneObject.h"
#include "Settings.h"
#include "Face.h"
#include <vector>

class Cube : public SceneObject{

public:
        Cube();
        Cube(int rows, int colors, int helpFaces);
        ~Cube();
        virtual void draw();
        virtual bool update();
        vector<Face>& getFaces();
        int getScore(int timeLeft);
        int calculateScore(float total, float correct, float wrong, float timeLeft);
        int getNumberOfIncorrectFaces();
        int getNumberOfCorrectFaces();
        int getTotalFacesNumber();

        void showCorrectColors();
        void showDefaultColors();
        bool toggleFace(Face& face);
        int getNextColor();
        int getCurrentColor();
    
        bool shouldRemoveColorFromFace(Face &face);
        bool shouldPlaceColorOnFace(Face &face);
        bool getIsSolutionVisibe();
        void setIsSolutionVisible(bool isVisible);
        void showUserColors();
        void switchBetweenUserAndCorrectColors();
    
private:

        int faceSize;
        int faceSegments;
        int rows;
        int colors;
        int helpFaces;
        bool isSolutionVisible;
        Settings *settings;
        vector<int> colorContainer;
        vector<Face> faces;

        virtual bool init();
        virtual void drawDebug();

        void addFace(float x, float y, float z, int color, FaceId identifier);
        void addFace(float x, float y, float z, int color);
        int getRandomFaceColor(int x,int y,int z);
        bool loadCube();
        bool correctColorsVisible;
        void generateColors();
        void shuffleVector(vector<int>& vec);
        int getFaceCount();
        int popColor();
        void setHelpFaces();

        map<int,int> freeColors;
        map<int,int> placedColors;
        int currentColor;
};

#endif
