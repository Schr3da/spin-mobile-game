#pragma once

#include "Scene.h"
#include "Settings.h"
#include "PlayerController.h"

class Game {

 public:
    Game();
    ~Game();
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button=0);
    void mousePressed(int x, int y, int button=0);
    Face* mouseReleased(int x, int y, int button=0);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    Scene* getScene();
    
 private:
    PlayerController controlls;
    Settings &settings;
    Scene *scene;
    
    void load();
};
