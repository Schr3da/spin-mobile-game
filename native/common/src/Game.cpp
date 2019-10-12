#include "Game.h"
#include "ofxAssimpModelLoader.h"

Game::Game() : settings(PositionFactory::instance().getSettings()) {}

void Game::setup(){
    //SETUP OPEN FRAMEWORK
    ofSetFrameRate( 60 );
    ofEnableAlphaBlending();
    ofEnableDepthTest();
    ofEnableSmoothing();
    ofEnableAntiAliasing();
    ofEnableTextureEdgeHack();
    ofBackgroundHex(settings.getBackgroundColor());
    //SETUP PLAYERCONTROLLER
    scene = NULL;
    scene = new Scene();
    controlls = PlayerController(*scene);
    this->load();
}

void Game::load(){

/*
    http://gcc.gnu.org/onlinedocs/cpp/Predefined-Macros.html
    http://sourceforge.net/p/predef/wiki/OperatingSystems/
*/
    #ifdef _WIN32
        scene->startNewGame(4, 4, 0);
        scene->placeColorPhase();
    #ifdef _WIN64
        scene->startNewGame(4, 4, 0);
        scene->placeColorPhase();
    #endif
    #elif __APPLE__
        #include "TargetConditionals.h"
        #if TARGET_IPHONE_SIMULATOR
            scene->showMenuMesh();
        #elif TARGET_OS_IPHONE
            scene->showMenuMesh();
        #elif TARGET_OS_MAC
            scene->startNewGame(4, 4, 0);
            scene->placeColorPhase();
        #else
            scene->startNewGame(4, 4, 0);
            scene->placeColorPhase();
    #endif
    #elif __linux
        scene->startNewGame(4, 4, 0);
        scene->placeColorPhase();
    #elif __unix
        scene->startNewGame(4, 4, 0);
        scene->placeColorPhase();
    #elif __posix
        scene->startNewGame(4, 4, 0);
        scene->placeColorPhase();
    #endif
}

void Game::update(){
    if(scene != NULL){
        scene->update();
    }
}

void Game::draw(){
    if(scene != NULL){
        scene->draw();
    }
}

void Game::keyPressed(int key){

}

void Game::keyReleased(int key){
    controlls.up(key);
}

void Game::mouseMoved(int x, int y ){
    controlls.moved(x, y);
}

void Game::mouseDragged(int x, int y, int button){
    controlls.moved(x, y);
}

void Game::mousePressed(int x, int y, int button){
    controlls.down(x, y);
}

Face* Game::mouseReleased(int x, int y, int button){
    Face* selectedface = controlls.up(x, y);
    if(selectedface != NULL){
        bool isFaceSelected = scene->toggleFace(*selectedface);
        if(isFaceSelected){
            cout << "set next color" << endl;
        } else {
            cout << "remove face color" << endl;
        }
        return selectedface;
    }
    selectedface = NULL;
    return selectedface;
}

void Game::windowResized(int w, int h){
}

void Game::gotMessage(ofMessage msg){

}

void Game::dragEvent(ofDragInfo dragInfo){

}

Scene* Game::getScene(){
  return scene != NULL ? scene : NULL;
}

Game::~Game(){
    if(scene != NULL){
        delete scene;
        scene = NULL;
    }
}
