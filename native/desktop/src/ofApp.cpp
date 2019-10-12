#include "ofApp.h"
#include "ofxAssimpModelLoader.h"

void ofApp::setup(){
    game.setup();
}

void ofApp::prepareDraw(){

}

void ofApp::update(){
    game.update();
}

void ofApp::draw(){
    game.draw();
}

void ofApp::keyPressed(int key){
    game.keyPressed(key);
}

void ofApp::keyReleased(int key){
    game.keyReleased(key);
}

void ofApp::mouseMoved(int x, int y ){
    game.mouseMoved(x,y);
}

void ofApp::mouseDragged(int x, int y, int button){
    game.mouseDragged(x,y,button);
}

void ofApp::mousePressed(int x, int y, int button){
    game.mousePressed(x,y,button);
}

void ofApp::mouseReleased(int x, int y, int button){
    game.mouseReleased(x,y,button);
}

void ofApp::windowResized(int w, int h){
    game.windowResized(w,h);
}

void ofApp::gotMessage(ofMessage msg){
    game.gotMessage(msg);
}

void ofApp::dragEvent(ofDragInfo dragInfo){
    game.dragEvent(dragInfo);
}
