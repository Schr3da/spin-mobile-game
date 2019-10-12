#include "Camera.h"
#include <iostream>
#include <sstream>
#include "Global.h"
#include "PositionFactory.h"
#include "Logger.h"
#include "CameraPositionSorter.h"
#include <cmath>
#include <stdexcept>

Camera::Camera(): rotationActive(false){

    rotationSpeed=5;
    rotationCounter=0;
    camera = ofEasyCam();
    currentPosition=NULL;
    previousPosition=NULL;
    instanceCorrectInitialized = init();
    if(!instanceCorrectInitialized){
        cout << "Camera instace not correctly initialized"  <<endl;
        return;
    }
}

bool Camera::init(){
    settings = &PositionFactory::instance().getSettings();
    if(settings == NULL){
        return false;
    }
    camera.setDistance(settings->getCameraZOffset());
    camera.setFarClip(settings->getCameraZOffset() * 2);
    camera.setFov(75);
    camera.setNearClip(0.1);
    camera.disableMouseMiddleButton();
    this->reset();
    return true;
}

void Camera::reset(){
    camera.setDrag(settings->getDragSpeed());
    camera.setPosition(0, 0, settings->getCameraZOffset());
    currentPosition = PositionFactory::instance().getStartPosition();
    lookAtPosition();
}

bool Camera::lookAtPosition(){
    if (currentPosition==NULL){
	throw invalid_argument("Camera::lookAtPosition() was called with currentPosition=NULL" );
        return false;
    }
    camera.setPosition(currentPosition->getPosition());
    camera.lookAt(currentPosition->getTarget(),currentPosition->getUpVector());
    return true;
}

bool Camera::update(){
    if (rotationActive==false){
        return false;
    }
    if (rotationCounter>=rotationSpeed){
        lookAtPosition();
        rotationActive=false;
        previousPosition=NULL;
        return true;
    }
    float anglePosition = (rotationSpeed-rotationCounter) * positionRotationAngle;
    float angleAxis = (rotationSpeed-rotationCounter) * axisRotationAngle;

    ofVec3f position = currentPosition->getPosition().getRotated(anglePosition, positionRotationAxis);
    ofVec3f axis = currentPosition->getUpVector().getRotated(angleAxis, axisRotationAxis);
    camera.setPosition(position);
    camera.lookAt(ofVec3f(0,0,0), axis.normalize());

    rotationCounter++;
    return true;
}

void Camera::draw(){
    camera.draw();
}

void Camera::drawDebug(){
    stringstream message;
    message << camera.getPosition();
    Logger::log(message.str(), Logger::DEBUG_LOW);
}

ofEasyCam& Camera::getCamera(){
    return camera;
}

bool Camera::isRotationActive(){
    return rotationActive;
}

CameraPosition* Camera::getCurrentPosition() const{
    return this->currentPosition;
}

void Camera::updateCurrentPosition(CameraPosition * newPosition, bool savePreviousPosition){
    if (savePreviousPosition){
        previousPosition = currentPosition;
    } else {
        previousPosition = NULL;
    }
    currentPosition=newPosition;
}

void Camera::activateRotation(){
    setUpRotationVariables();
    rotationActive=true;
}

void Camera::setUpRotationVariables(){
    ofVec3f previousCameraPosition;
    ofVec3f previousCameraAxis;
    setPreviousAxisAndPosition(previousCameraPosition, previousCameraAxis);

    positionRotationAngle = currentPosition->getPosition().angle(previousCameraPosition) / rotationSpeed;
    positionRotationAxis = ofVec3f(currentPosition->getPosition());
    positionRotationAxis.cross(previousCameraPosition);

    axisRotationAngle = currentPosition->getUpVector().angle(previousCameraAxis) / rotationSpeed;
    axisRotationAxis = ofVec3f(currentPosition->getUpVector());
    axisRotationAxis.cross(previousCameraAxis);

    axisRotationAxis.normalize();
    positionRotationAxis.normalize();

    rotationCounter=1;

    if (positionRotationAngle*rotationSpeed<=5){
        rotationCounter=rotationSpeed;
    }
}


void Camera::setPreviousAxisAndPosition(ofVec3f& position, ofVec3f& axis){
    if (previousPosition==NULL){
        position = camera.getPosition();
        axis = camera.getYAxis();
    } else {
        position = previousPosition->getPosition();
        axis = previousPosition->getUpVector();
    }
}
