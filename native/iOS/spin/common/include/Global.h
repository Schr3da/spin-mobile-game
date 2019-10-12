#ifndef SpinCpp_Structs_h
#define SpinCpp_Structs_h

#include <stdio.h>
#include "ofMain.h"

typedef struct FaceColors{
    int r;
    int g;
    int b;
}FaceColors;

namespace direction{
    enum Direction{
    // 97 a
    // 115 s
    // 100 d
    // 119 w
        RIGHT=97,
        LEFT=100,
        DOWN=119,
        UP=115
    };
}


namespace scoreStatus{
    enum ScoreStatus{
      CORRECT=1,
      INCORRECT=2,
      NOTSET=3,
      NOTSELECTABLE=4
    };
}


typedef enum FaceId {
    FRONT,
    LEFT,
    RIGHT,
    BOTTOM,
    BACK,
    TOP
} FaceId;

typedef enum ApplicationState{
    APPLICATION_INIT,
    MAIN_MENU,
    SETTINGS,
    RANKINGS,
    GAME_MEMORIZE,
    GAME_PLACE_COLORS,
    GAME_RESULT,
    GAME_COMPLETE,
    GAME_SOLUTION
} ApplicationState;

typedef struct GSSize{
    int width;
    int height;
} GSSize;

static GSSize GSSizeMake(int width, int height){
    GSSize size;
    size.width = width;
    size.height = height;
    return size;
}

static void printVectorWithIdentifier(const char* identifier, ofVec3f vec){
    cout << identifier << ": X: " << vec.x << " Y: " << vec.y << " Z: " << vec.z << endl;
}

static void printVector(ofVec3f &vec){
    cout << "X: " << vec.x << " Y: " << vec.y << " Z: " << vec.z << endl;
}

#endif
