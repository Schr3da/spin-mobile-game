#include <ofMain.h>
#include "Settings.h"
#include "Logger.h"

Settings::Settings(){
}

Settings::~Settings(){
    
}

bool Settings::init(){
    
    this->setUpDefaultSettingVariables();
    this->loadSettings();
    this->setPostLoadVariables();
    
    return true;
}

void Settings::setUpDefaultSettingVariables(){
    
    applicationState = APPLICATION_INIT;
    
    frameRate = 60;
    faceSize = 1;
    maxRows = 4;
    initRows = 4;
    cameraZOffset = 9;
    resolutionSize = 2;
    backgroundColor = 0xffffff;
    wireColor = 0xefefef;
    lineWidth = 2;
    grayColor = 0x6C7989;
    notSelectableColor =  0x9ca4b0;
    redColor = 0xF64747;
    greenColor = 0x02C9A9;
    blueColor = 0x19B5FE;
    yellowColor = 0xF9BF3B;
    purpleColor = 0x7F00FF;
    dragSpeed = 0.0f;
    debugMode = false;
    gridMode = true;
    
    soundActive = false;
    vibrationActive = false;
    snapToGrid = true;
    networkAllowed = true;
    tutorialActive = false;
    
    highscore = 0;
    curArchievment = 0;
    requiredArchievement = 40;
    curScore = 0;
    archievementColor = 0;
    
    this->setNewGameDefaultValues();
}

void Settings::setNewGameDefaultValues(){
    curNumberOfUsedColors = 1;
    curNumberOfRows = 1;
    curScore = 0;
    lvlPassed = false;
}


void Settings::setPostLoadVariables(){
    faceColors.push_back(greenColor);
    faceColors.push_back(blueColor);
    faceColors.push_back(yellowColor);
    faceColors.push_back(redColor);
}

string Settings::readFileContentWithFilename( const char *filename){
    ifstream readFile(filename, ifstream::binary);
    string content;
    if(readFile != NULL && readFile.is_open()){
        string line;
        while(getline(readFile, line)){
            content += line;
        };
        readFile.close();
        if(debugMode){
            cout << content << "\n";
        }
    }
    return content;
}

void Settings::loadSettings(){
    ofFile file;
    Json::Reader json;
    Json::Value root;
    stringstream filename;
    filename << file.path().c_str() <<endl;
    if(json.parse(Settings::readFileContentWithFilename(filename.str().c_str()), root, false)){
        
        frameRate = root["framerate"].asInt();
        faceSize = root["faceSize"].asInt();
        maxRows = root["maxRows"].asInt();
        initRows = root["initRows"].asInt();
        cameraZOffset = root["cameraZOffset"].asInt();
        resolutionSize = root["resolutionSize"].asInt();
        lineWidth = root["lineWidth"].asInt();
        
        backgroundColor = root["backgroundColor"].asInt();
        wireColor = root["wireColor"].asInt();
        grayColor = root["grayColor"].asInt();
        notSelectableColor = root["notSelectableColor"].asInt();
        redColor = root["redColor"].asInt();
        greenColor = root["greenColor"].asInt();
        blueColor = root["blueColor"].asInt();
        yellowColor = root["yellowColor"].asInt();
        
        dragSpeed = root["dragSpeed"].asFloat();
        debugMode = root["isDebugModeActive"].asBool();
        gridMode = root["isGridModeActive"].asBool();
        snapToGrid = root["shouldSnapToGrid"].asBool();
        soundActive = root["isSoundActive"].asBool();
        vibrationActive = root["isVibrationActive"].asBool();
        networkAllowed = root["isNetworkAllowed"].asBool();
        tutorialActive = root["isTutorialDeactivated"].asBool();
        
        highscore = root["highscore"].asInt();
        curScore = root["curScore"].asInt();
        curNumberOfUsedColors = root["curNumberOfUsedColors"].asInt();
        curNumberOfRows = root["curNumberOfRows"].asInt();
    }
}

void Settings::writeChangesToFile(){
    
    ofstream changes;
    changes << "{" << endl;
    Settings::createJSONStringWithIntValue(changes, "framerate", frameRate, true);
    Settings::createJSONStringWithIntValue(changes, "faceSize", faceSize, true);
    Settings::createJSONStringWithIntValue(changes, "maxRows", maxRows, true);
    Settings::createJSONStringWithIntValue(changes, "initRows", initRows, true);
    Settings::createJSONStringWithIntValue(changes, "cameraZOffset", cameraZOffset, true);
    Settings::createJSONStringWithIntValue(changes, "resolutionSize", resolutionSize, true);
    Settings::createJSONStringWithIntValue(changes, "lineWidth", lineWidth, true);
    
    Settings::createJSONStringWithIntValue(changes, "backgroundColor", backgroundColor, true);
    Settings::createJSONStringWithIntValue(changes, "wireColor", wireColor, true);
    Settings::createJSONStringWithIntValue(changes, "grayColor", grayColor, true);
    Settings::createJSONStringWithIntValue(changes, "notSelectableColor", notSelectableColor, true);
    Settings::createJSONStringWithIntValue(changes, "redColor", redColor, true);
    Settings::createJSONStringWithIntValue(changes, "greenColor", greenColor, true);
    Settings::createJSONStringWithIntValue(changes, "blueColor", blueColor, true);
    Settings::createJSONStringWithIntValue(changes, "yellowColor", yellowColor, true);
    
    Settings::createJSONStringWithFloatValue(changes, "dragSpeed", dragSpeed, true);
    Settings::createJSONStringWithBoolValue(changes, "isDebugModeActive", debugMode, true);
    Settings::createJSONStringWithBoolValue(changes, "isGridModeActive", gridMode, true);
    Settings::createJSONStringWithBoolValue(changes, "shouldSnapToGrid", snapToGrid, true);
    Settings::createJSONStringWithBoolValue(changes, "isSoundActive", soundActive, true);
    Settings::createJSONStringWithBoolValue(changes, "isVibrationActive", vibrationActive, true);
    Settings::createJSONStringWithBoolValue(changes, "isNetworkAllowed", networkAllowed, true);
    Settings::createJSONStringWithBoolValue(changes, "isTutorialDeactivated", tutorialActive, true);
    
    Settings::createJSONStringWithIntValue(changes, "highscore", highscore, true);
    Settings::createJSONStringWithIntValue(changes, "curscore", curScore, true);
    Settings::createJSONStringWithIntValue(changes, "curNumberOfUsedColors", curNumberOfUsedColors, true);
    Settings::createJSONStringWithIntValue(changes, "curNumberOfRows", curNumberOfRows, false);
    changes << "}" << endl;
    
}

void Settings::createJSONStringWithIntValue(ofstream &stream, string key, int value, bool comma){
    if(comma){ stream << "\"" << key << "\" : " << value << "," << endl; }
    else { stream << "\"" << key.c_str() << "\" : " << value << endl; }
}

void Settings::createJSONStringWithFloatValue(ofstream &stream, string key, float value, bool comma){
    if(comma){ stream << "\"" << key << "\" : " << value << "," << endl; }
    else { stream << "\"" << key.c_str() << "\" : " << value << endl; }
}

void Settings::createJSONStringWithBoolValue(ofstream &stream, string key, bool value, bool comma){
    if(comma){ stream << "\"" << key << "\" : " << value << "," << endl; }
    else { stream << "\"" << key.c_str() << "\" : " << value << endl; }
}

void Settings::createJSONStringWithStringValue(ofstream &stream, string key, string value, bool comma){
    if(comma){ stream << "\"" << key << "\" : " << value << "," << endl; }
    else { stream << "\"" << key.c_str() << "\" : " << value.c_str() << endl; }
}

int Settings::getFrameRate(){
    return frameRate;
}

int Settings::getFaceSize(){
    return faceSize;
}

int Settings::getInitRows(){
    return initRows;
}

int Settings::getMaxRows(){
    return maxRows;
}

int Settings::getCameraZOffset(){
    return cameraZOffset;
}

int Settings::getResolutionSize(){
    return resolutionSize;
}

int Settings::getLineWidth(){
    return lineWidth;
}

int Settings::getBackgroundColor(){
    return backgroundColor;
}

int Settings::getWireColor(){
    return wireColor;
}

int Settings::getGrayColor(){
    return grayColor;
}

int Settings::getDefaultFaceColor(){
    return backgroundColor;
}


int Settings::getRedColor(){
    return redColor;
}

int Settings::getGreenColor(){
    return greenColor;
}

int Settings::getPurpleColor(){
    return purpleColor;
}

int Settings::getBlueColor(){
    return blueColor;
}

int Settings::getYellowColor(){
    return yellowColor;
}

int Settings::getNotSelectableColor(){
    return notSelectableColor;
}

vector<int> Settings::getFaceColors() const{
    return faceColors;
}

float Settings::getDragSpeed(){
    return dragSpeed;
}

bool Settings::isDebugModeActive(){
    return debugMode;
}

bool Settings::isGridModeActive(){
    return gridMode;
}

bool Settings::shouldSnapToGrid(){
    return snapToGrid;
}

GSSize Settings::getScreenSize(){
    return GSSizeMake(ofGetWindowWidth(), ofGetWindowHeight());
}

GSSize Settings::getHalfScreenSize(){
    return GSSizeMake(ofGetWindowWidth() *0.5, ofGetWindowHeight() *0.5);
}

ApplicationState Settings::getApplicationState(){
    return applicationState;
}

void Settings::setApplicationState(ApplicationState state){
    this->applicationState = state;
}

bool Settings::getSoundActive(){
    return soundActive;
}

bool Settings::getVibrationActive(){
    return vibrationActive;
}

bool Settings::getSnapToGrid(){
    dragSpeed = snapToGrid ? 0.0f : dragSpeed;
    return snapToGrid;
}

bool Settings::getNetworkAllowed(){
    return networkAllowed;
}

const char* Settings::getMenuModelPath(){
    return "./model/cube.dae";
}

int Settings::getHightscore(){
    return highscore;
}

int Settings::getCurScore(){
    return curScore;
}

int Settings::getCurNumberOfUsedColors(){
    return curNumberOfUsedColors;
}

int Settings::getCurNumberOfRows(){
    return curNumberOfRows <= maxRows ? curNumberOfRows : maxRows;
}

void Settings::setCurNumberOfUsedColors(int value){
    curNumberOfUsedColors = value;
}

void Settings::setCurNumberOfRows(int value){
    curNumberOfRows = value;
}

bool Settings::isTutorialActivated(){
    return tutorialActive;
}

void Settings::setCurScore(int value){
    curScore = value;
}

void Settings::setCurArchievement(int value){
    curArchievment = value;
    archievementColor = (curArchievment >= requiredArchievement) ? greenColor : redColor;
}

int Settings::getCurArchievement(){
    return curArchievment;
}

int Settings::getTimeBonus(){
    return timeBonus;
}

void Settings::setTimeBonus(int value){
    timeBonus = value;
}

int Settings::getArchievementColor(){
    return archievementColor;
}

bool Settings::isLvlPassed(){
    return lvlPassed;
}

void Settings::setTutorialActiveState(bool state){
    tutorialActive = state;
}



