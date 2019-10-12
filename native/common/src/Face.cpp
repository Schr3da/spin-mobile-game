#include "Face.h"
#include <iostream>
#include "Logger.h"

Face::Face(ofVec3f vec, int size, int color, FaceId identifier) : pos(vec){
    this->identifier = identifier;
    instanceCorrectInitialized = this->init(size, color, identifier);
    if(!instanceCorrectInitialized){
        cout << "Face instace not correctly initialized"  <<endl;
        return;
    }
}

Face::Face(ofVec3f vec, int size, int color) : pos(vec){
    cout << "ATTENTION Cube(ofVec3f vec, int size, int color) - Constructor sets identifier to FRONT as default value" << endl;
    this->identifier = FRONT;
    instanceCorrectInitialized = this->init(size, color, identifier);
    if(!instanceCorrectInitialized){
        cout << "Face instace not correctly initialized"  <<endl;
        return;
    }
}

Face::~Face(){
    settings = NULL;
}

void Face::setUnselectable(){
    selectable=false;
    curColor=settings->getGrayColor();
    corColor=curColor;
}

bool Face::init(int size, int color, FaceId identifier){
    settings = &PositionFactory::instance().getSettings();
    if(settings == NULL){
        return false;
    }
    this->identifier = identifier;
    this->size = size;
    this->corColor = color;
    this->userColor = 0x000000;
    this->curColor= settings->getDefaultFaceColor();
    this->selectable=true;
    return this->init();
}

bool Face::init(){
    if(settings == NULL){
        settings = &PositionFactory::instance().getSettings();
    }
    int size = settings->getFaceSize();
    int segments = settings->getResolutionSize();
    float halfCubeSize = size * 0.5;
    colorPlacedByUser = false;
    geometry = ofPlanePrimitive();
    geometry.set(size, size, segments, segments);
    geometry.setPosition(pos.x, pos.y, pos.z);
    geometry.setMode(OF_PRIMITIVE_TRIANGLES);

    //small z value to bring outline to front
    outline.enableColors();
    outline.setMode(OF_PRIMITIVE_LINES);
    outline.addVertex( ofVec3f(-halfCubeSize, halfCubeSize, -halfCubeSize*0.001) );
    outline.addVertex( ofVec3f(halfCubeSize, halfCubeSize, -halfCubeSize*0.001) );
    outline.addVertex( ofVec3f(halfCubeSize, halfCubeSize, -halfCubeSize*0.001) );
    outline.addVertex( ofVec3f(halfCubeSize, -halfCubeSize, -halfCubeSize*0.001) );
    outline.addVertex( ofVec3f(halfCubeSize, -halfCubeSize, -halfCubeSize*0.001) );
    outline.addVertex( ofVec3f(-halfCubeSize, -halfCubeSize, -halfCubeSize*0.001) );
    outline.addVertex( ofVec3f(-halfCubeSize, -halfCubeSize, -halfCubeSize*0.001) );
    outline.addVertex( ofVec3f(-halfCubeSize, halfCubeSize, -halfCubeSize*0.001) );

    this->setAngleAndRotationAxis();
    geometry.rotate(angle, rotAxis);
    return true;
}

void Face::unSelect(){
    if(selectable){
        colorPlacedByUser=false;
        curColor=settings->getDefaultFaceColor();
    }
}
void Face::select(int color){
    if(selectable){
        colorPlacedByUser=true;
        curColor=color;
        userColor = color;
    }
}

bool Face::toggleSelection(int color){
    if (colorPlacedByUser){
        unSelect();
    } else {
        select(color);
    }
    return colorPlacedByUser;
}

void Face::setAngleAndRotationAxis(){
    rotAxis = ofVec3f();
    angle = 0;
    if(identifier == FRONT){
        rotAxis = ofVec3f(0,0,1);
        angle = 0;
    } else if(identifier == BACK){
        rotAxis = ofVec3f(0,1,0);
        angle = 180;
    } else if(identifier == LEFT){
        rotAxis = ofVec3f(0,1,0);
        angle = 90;
    }  else if(identifier == RIGHT){
        rotAxis = ofVec3f(0,1,0);
        angle = -90;
    } else if(identifier == BOTTOM){
        rotAxis = ofVec3f(1,0,0);
        angle = 90;
    } else if(identifier == TOP){
        rotAxis = ofVec3f(1,0,0);
        angle = -90;
    }
}

bool Face::update(){
    return true;
}

void Face::draw(){
    ofFill();
    ofSetHexColor(curColor);
    geometry.draw();
    ofSetHexColor(0xECF0F1);
    ofSetLineWidth(settings->getLineWidth());
    ofPushMatrix();
        ofTranslate(pos.x, pos.y, pos.z);
        ofRotate(angle, rotAxis.x, rotAxis.y, rotAxis.z);
        outline.drawWireframe();
    ofPopMatrix();
    ofSetHexColor(curColor);
}

void Face::drawDebug(){
    if(settings->isDebugModeActive()){
        ofSetColor(0, 255, 0);
        //geometry.drawAxes(1);
        ofNoFill();
    }
}

void Face::setPosition(ofVec3f &value){
    pos = value;
    geometry.setPosition(pos.x, pos.y, pos.z);
}

ofVec3f& Face::getPosition(){
    return pos;
}

void Face::setSize(int value){
    size = value;
}

int Face::getSize(){
    return size;
}

void Face::setCurrentColor(int color){
    if(!settings->isDebugModeActive()){
        if (selectable){
            this->curColor = color;
        }else{
            Logger::log("Face::setCurrentColor was called for a face that is unselectable");
        }
    }else {
        Logger::log("Face::setCurrentColor cannot be called when not in debug mode", Logger::ERROR);
    }
}

void Face::setCorrectColor(int color){
    this->corColor = color;
}

bool Face::userSetCorrectColor(){
    return curColor == corColor ? true : false;
}

scoreStatus::ScoreStatus  Face::getScoreInfo(){
    if (isSelectable()==false){
        return scoreStatus::NOTSELECTABLE;
    }
    if (colorPlacedByUser==false){
        return scoreStatus::NOTSET;
    }
    return userSetCorrectColor() ? scoreStatus::CORRECT : scoreStatus::INCORRECT;
}

vector<ofVec3f>& Face::getVertices(){
    return geometry.getMesh().getVertices();
}

ofMesh& Face::getMesh(){
    return geometry.getMesh();
}

ofPlanePrimitive& Face::getBoxPrimitive(){
    return geometry;
}

bool Face::isColorPlacedByUser(){
    return colorPlacedByUser;
}

void Face::showCorrectColor(){
    this->colorPlacedByUser=false;
    this->curColor=corColor;
}

void Face::showDefaultColor(){
    this->colorPlacedByUser=false;
    if (selectable){
        curColor=settings->getDefaultFaceColor();
    }
}

void Face::showUserColor(){
    if(selectable){
        if(userColor != 0x000000){
            curColor = userColor;
        } else {
            curColor = settings->getDefaultFaceColor();
        }
    }
}

bool Face::isSelectable(){
    return selectable;
}
int Face::getCorrectColor(){
    return corColor;
}
int Face::getCurrentColor(){
    return curColor;
}
