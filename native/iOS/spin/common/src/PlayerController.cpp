#include "PlayerController.h"
#include "PositionFactory.h"
#include "ofMain.h"
#include "Camera.h"
#include "Cube.h"
#include "Ray.h"

PlayerController::PlayerController() {
    sceneRef = NULL;
    settings = NULL;
}

PlayerController::PlayerController(Scene& sceneRef){
    this->sceneRef = &sceneRef;
    this->init();
}

PlayerController::~PlayerController(){
    sceneRef = NULL;
    settings = NULL;

}

bool PlayerController::init(){
    userDidDrag = false;
    settings = &PositionFactory::instance().getSettings();
    return true;
}

void PlayerController::drawDebug(){

}

void PlayerController::down(int key){

}

void PlayerController::up(int key){
    update(key);
}

void PlayerController::down(int x, int y){
    userDidDrag = false;
}

void PlayerController::moved(int x, int y){
    userDidDrag = true;
}

Face* PlayerController::up(int x, int y){
    return this->update(x, y);
}

Face* PlayerController::update(int x, int y){
    if(sceneRef == NULL){
        return NULL;
    }
    if(sceneRef->isGameStarted()){
        if(!userDidDrag){
            return this->didSelectFace(x, y);
        } else {
            sceneRef->lockCameraPosition();
        }
    }
    userDidDrag = false;
    return NULL;
}

void PlayerController::update(int key){
    if(sceneRef != NULL && sceneRef->isGameStarted() && !sceneRef->isRotationActive()){
        if (key==direction::LEFT){
            sceneRef->rotate(direction::LEFT);
            return;
        }
        if (key==direction::RIGHT){
            sceneRef->rotate(direction::RIGHT);
            return;
        }
        if (key==direction::UP){
            sceneRef->rotate(direction::UP);
            return;
        }
        if (key==direction::DOWN){
            sceneRef->rotate(direction::DOWN);
            return;
        }
        sceneRef->setUpCube(2,4,1);
    }
}

Face* PlayerController::didSelectFace(int x, int y){

    if(sceneRef == NULL || settings == NULL){
        return NULL;
    }
    
    ApplicationState state = settings->getApplicationState();
    if(state != GAME_PLACE_COLORS){
        return NULL;
    }

    ofEasyCam cam = sceneRef->getCamera().getCamera();
    vector<Face> &cubeFaces = sceneRef->getCube().getFaces();
    vector<Face*> selectedFaces;

    bool isDebugModeActive = settings->isDebugModeActive();
    origin = cam.screenToWorld(ofVec3f(x, y, -1.f));
    end = cam.screenToWorld(ofVec3f(x, y, 1.0f));

    for (unsigned int i=0; i<cubeFaces.size(); i++) {
        Face *face = &cubeFaces.at(i);
        const ofMesh mesh = face->getMesh();
        if(isDebugModeActive){
            face->setCurrentColor(settings->getBackgroundColor());
            face->unSelect();
        }
        if (Ray::intersectsMesh(ofVec2f(x,y), mesh, cam, face->getBoxPrimitive().getGlobalTransformMatrix())){
            if(settings->isDebugModeActive()){
                face->setCurrentColor(0x00ffff);
            }
            selectedFaces.push_back( face );
        }
    }
    int index = 0;
    float smallestZValue = 0;
    for(unsigned int i=0; i<selectedFaces.size(); i++){
        if(i == 0){
            smallestZValue = cam.worldToCamera( selectedFaces.at(i)->getBoxPrimitive().getGlobalPosition()).z;
        }
        else if(cam.worldToCamera( selectedFaces.at(i)->getBoxPrimitive().getGlobalPosition()).z < smallestZValue ){
            smallestZValue = cam.worldToCamera( selectedFaces.at(i)->getBoxPrimitive().getGlobalPosition()).z;
            index = i;
        }
    }
    if(smallestZValue != 0){
        Face *object = selectedFaces.at(index);
        if(object == NULL){
            cout << "selectedFaces is null" << endl;
            return NULL;
        }
        if(object->isSelectable()){
            return object;
        }
    }
    return NULL;
}
