#include "ofApp.h"
#include "./../include/Helper.h"
#import "GUI.h"
#import <AudioToolbox/AudioServices.h>

void ofApp::setup(){
    sceneRef = NULL;
    settingsRef = NULL;
    settingsRef = &PositionFactory::instance().getSettings();
    gui = nil;
    isMoved = false;
    game.setup();
    sceneRef = game.getScene();
    this->initMenu();
}

void ofApp::initMenu(){
    if(sceneRef ==  NULL){
        cout << "Sceneref is null in ofApp initMenu" << endl;
        return;
    }
    [Helper releaseViewObject:&gui];
    gui = [[GUI alloc]initWithWindow:ofxiOSGetUIWindow()];
    gui.sceneRef = sceneRef;
}

void ofApp::update(){
    game.update();
}

void ofApp::draw(){
    game.draw();
}

void ofApp::exit(){

}

void ofApp::touchDown(ofTouchEventArgs & touch){
    isMoved = false;
    game.mousePressed(touch.x, touch.y);
}

void ofApp::touchMoved(ofTouchEventArgs & touch){
    isMoved = true;
    game.mouseMoved(touch.x, touch.y);
}

void ofApp::touchUp(ofTouchEventArgs & touch){
    
    if(!isMoved && gui != nil && settingsRef != NULL && settingsRef->getApplicationState() == MAIN_MENU && !gui.isAnimating ){
        [gui hideCurrentView:[Helper newGameText]];
    }
    else if (!isMoved && gui != nil && sceneRef != NULL && sceneRef->getCube().getIsSolutionVisibe()){
        sceneRef->getCube().switchBetweenUserAndCorrectColors();
    } else {
        Face* selectedFace = game.mouseReleased(touch.x, touch.y);
        if(gui != nil && selectedFace != NULL && selectedFace->isSelectable()){
            [gui setCurrentColor];
            if(!selectedFace->isColorPlacedByUser()){
                if(settingsRef->getVibrationActive()){
                    AudioServicesPlaySystemSound(kSystemSoundID_Vibrate);
                }
            }
        }
    }
}

void ofApp::touchDoubleTap(ofTouchEventArgs & touch){

}

void ofApp::touchCancelled(ofTouchEventArgs & touch){
    
}

void ofApp::lostFocus(){

}

void ofApp::gotFocus(){

}

void ofApp::gotMemoryWarning(){

}

void ofApp::deviceOrientationChanged(int newOrientation){

}

ofApp::~ofApp(){
    if(gui != nil){
        [Helper releaseViewObject:&gui];
        gui = nil;
    }
    sceneRef = NULL;
    settingsRef = NULL;
}
