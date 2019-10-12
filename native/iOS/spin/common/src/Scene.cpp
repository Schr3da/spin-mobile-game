#include "Scene.h"
#include "math.h"
#include <algorithm>

Scene::Scene() :settings(PositionFactory::instance().getSettings()){
    instanceCorrectInitialized = this->init();
    if(!instanceCorrectInitialized){
        cout << "scene not correctly initialized";
        return;
    }
    cube.showCorrectColors();
}
void Scene::restartGame(){
    settings.setNewGameDefaultValues();
}

Scene::~Scene(){

}

bool Scene::isRotationActive(){
    return camera.isRotationActive();
}

bool Scene::init(){
    gameDidStart = false;
    rotationAngleForIntroMesh = 0;
    return this->showMenuMesh();
}

int Scene::getScore(int timeLeft){
    return cube.getScore(timeLeft);
}
int Scene::getNumberOfCorrectFaces(){
    return cube.getNumberOfCorrectFaces();
}
int Scene::getNumberOfIncorrectFaces(){
    return cube.getNumberOfIncorrectFaces();
}
int Scene::getNumberOfFaces(){
    return cube.getTotalFacesNumber();
}

bool Scene::showMenuMesh(){
    this->prepareToPlay();
    settings.setApplicationState(MAIN_MENU);
    introAnimate = false;
    introAnimate = menuModel.loadModel( settings.getMenuModelPath() ,true);
    menuModel.setScale(0.18, 0.18, 0.18);
    menuModel.setPosition(0, 0, 0);
    return introAnimate;
}

void Scene::prepareToPlay(){
    gameDidStart = false;
    camera.getCamera().disableMouseInput();
    halfWindowSize = settings.getHalfScreenSize();
    backgroundColor = settings.getBackgroundColor();
    camera.reset();
}

void Scene::startNewGame(int rows, int colors, int helper){
    prepareToPlay();
    this->setUpCube(rows, colors, helper);
    camera.getCamera().enableMouseInput();
    gameDidStart = true;
    introAnimate=false;
    this->memorizePhase();
}

void Scene::memorizePhase(){
    settings.setApplicationState(GAME_MEMORIZE);
    this->rotate(direction::LEFT);
    this->rotate(direction::UP);
}

void Scene::placeColorPhase(){
    settings.setApplicationState(GAME_PLACE_COLORS);
    cube.showDefaultColors();
}

void Scene::showResultPhaseWithTimeBonus(int timebonus){
    settings.setApplicationState(GAME_RESULT);
    int archievement = (float)this->getNumberOfCorrectFaces() / (float)this->getNumberOfFaces() * 100;
    settings.setCurArchievement( archievement );
    settings.setTimeBonus(timebonus);
    if(!settings.isLvlPassed()){
        settings.setNewGameDefaultValues();
        if(settings.getCurNumberOfRows() > 1){
            settings.setTutorialActiveState(false);
        }
    }
    settings.setCurScore(this->getNumberOfCorrectFaces() + timebonus - this->getCube().getNumberOfIncorrectFaces());
    settings.writeChangesToFile();
}

bool Scene::update(){
    ApplicationState state = settings.getApplicationState();
    if(state == MAIN_MENU || state == RANKINGS || state == SETTINGS){
        if (introAnimate){
            rotationAngleForIntroMesh -= 0.5f;
        }
        return introAnimate;
    }
    else if(state == GAME_MEMORIZE || state == GAME_PLACE_COLORS || GAME_RESULT){
        return camera.update();
    }
    return false;
}

void Scene::draw(){
    if(instanceCorrectInitialized){
        ofPushMatrix();
        ofSetBackgroundColorHex(backgroundColor);
        ofTranslate(halfWindowSize.width, halfWindowSize.height, 0);
        if(introAnimate){
            ofEnableAntiAliasing();
            ofSetHexColor(settings.getBackgroundColor());
            ofRotate(rotationAngleForIntroMesh, 0, 1, 0);
            ofRotate(rotationAngleForIntroMesh, 1, 0, 0);
            menuModel.drawFaces();
            ofDisableAntiAliasing();
        } else {
            camera.getCamera().begin();
            cube.draw();
            camera.getCamera().end();
        }
        ofPopMatrix();
    }
}

void Scene::drawDebug(){
    if(settings.isDebugModeActive()){
        ofSetHexColor(settings.getGrayColor());
        ofSetLineWidth(4);
    }
}

void Scene::lockCameraPosition(CameraPosition* lockedPosition){
    camera.updateCurrentPosition(lockedPosition, true);
    camera.activateRotation();
}

bool Scene::toggleFace(Face& face){
    return cube.toggleFace(face);
}

void Scene::lockCameraPosition(){
    if(settings.shouldSnapToGrid()){
        CameraPosition* lockedPosition = grid.getGridPosition(camera.getCamera());
        camera.updateCurrentPosition(lockedPosition, false);
        camera.activateRotation();
        camera.lookAtPosition();
    }
}

void Scene::rotate(int direction){
    if (direction==direction::LEFT){
        this->lockCameraPosition(this->camera.getCurrentPosition()->getLeftNeighbour());
    }
    if (direction==direction::RIGHT){
        this->lockCameraPosition(this->camera.getCurrentPosition()->getRightNeighbour());
    }
    if (direction==direction::UP){
        this->lockCameraPosition(this->camera.getCurrentPosition()->getUpNeighbour());
    }
    if (direction==direction::DOWN){
        this->lockCameraPosition(this->camera.getCurrentPosition()->getDownNeighbour());
    }
}

bool Scene::isGameStarted(){
    return gameDidStart;
}

void Scene::setUpCube(int rows, int colors, int helpFaces){
    cube = Cube(rows, colors, helpFaces);
    cube.showCorrectColors();
}

void Scene::loadNextLevel(){
    
    lvlRows = settings.getCurNumberOfRows();
    lvlColors = settings.getCurNumberOfUsedColors();
    
    if(lvlColors == 4 && lvlRows >= settings.getMaxRows()){
        std::cout << "max level reached Add specific level identifier" << endl;
        settings.setApplicationState(GAME_COMPLETE);
    }
    else if (lvlColors==4){
        lvlRows++;
        lvlColors=2;

        int faces = lvlRows*lvlRows*6;
        int possibilities = faces*lvlColors;
        int maxHelpers = faces-lvlColors;
        int helpers = ceil(possibilities*0.05);
        lvlHelpers= std::min(helpers, maxHelpers);
    } else {
        lvlColors++;
        int faces = lvlRows*lvlRows*6;
        int possibilities = faces*lvlColors;
        int maxHelpers = faces-lvlColors;
        int helpers = ceil(possibilities*0.05);
        lvlHelpers= std::min(helpers, maxHelpers);
    }
    
    if(lvlColors <= 1){
        lvlColors = 2;
    }
    
    settings.setCurNumberOfRows(lvlRows);
    settings.setCurNumberOfUsedColors(lvlColors);
    this->startNewGame(lvlRows,lvlColors,lvlHelpers);
}

Cube& Scene::getCube(){
    return cube;
}

Camera& Scene::getCamera(){
    return camera;
}

void Scene::showSolution(){
    cube.setIsSolutionVisible(true);
    cube.showCorrectColors();
}
