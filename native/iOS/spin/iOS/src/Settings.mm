#include <ofMain.h>
#include "Settings.h"
#include "Logger.h"

Settings::Settings(){
}

Settings::~Settings(){

}

bool Settings::init(){
    
    if(this->fileExistAtPath()){
        this->loadSettings();
    } else {
        this->setUpDefaultSettingVariables();
        this->writeChangesToFile();
    }
    this->setPostLoadVariables();
    return true;
}

void Settings::setUpDefaultSettingVariables(){
    
    applicationState = APPLICATION_INIT;
    
    frameRate = 60;
    faceSize = 1;
    maxRows = 4;
    initRows = 1;
    cameraZOffset = 9;
    resolutionSize = 2;
    backgroundColor = 0xffffff;
    wireColor = 0xefefef;
    lineWidth = 4;
    grayColor = 0x6C7989;
    notSelectableColor =  0x9ca4b0;
    redColor = 0xF64747;
    greenColor = 0x02C9A9;
    blueColor = 0x19B5FE;
    yellowColor = 0xF9BF3B;
    purpleColor = 0x7F00FF;
    dragSpeed = 0.9f;
    debugMode = false;
    gridMode = false;
    
    soundActive = false;
    vibrationActive = false;
    snapToGrid = true;
    networkAllowed = false;
    tutorialActive = true;

    highscore = 0;
    timeBonus = 0;
    this->setNewGameDefaultValues();
}

void Settings::setNewGameDefaultValues(){
    curNumberOfUsedColors = 1;
    curNumberOfRows = 1;
    curScore = 0;
    timeBonus = 0;
    lvlPassed = false;
    this->writeChangesToFile();
}


void Settings::setPostLoadVariables(){
    curArchievment = 0;
    requiredArchievement = 0;
    curScore = 0;
    
    faceColors.push_back(greenColor);
    faceColors.push_back(blueColor);
    faceColors.push_back(yellowColor);
    faceColors.push_back(redColor);
}

string Settings::readFileContentWithFilename( const char *filename){
    ifstream readFile(filename, ifstream::binary);
    string content;
    if(readFile && readFile.is_open()){
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
    Json::Reader json;
    Json::Value root;
    stringstream filename;
    filename << [[NSString stringWithFormat:@"%@/configuration.json",[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, true) objectAtIndex:0]]cStringUsingEncoding:NSUTF8StringEncoding];

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
        tutorialActive = root["isTutorialActive"].asBool();
        
        timeBonus = root["timeBonus"].asInt();
        highscore = root["highscore"].asInt();
        curScore = root["curScore"].asInt();
        curNumberOfUsedColors = root["curNumberOfUsedColors"].asInt();
        curNumberOfRows = root["curNumberOfRows"].asInt();
    }
}

bool Settings::fileExistAtPath(){
    NSString *filename = [NSString stringWithFormat:@"%@/configuration.json",[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, true) objectAtIndex:0]];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if(![fileManager fileExistsAtPath:filename]){
        [fileManager createFileAtPath:filename contents:nil attributes:nil];
        this->writeChangesToFile();
        return false;
    }
    return true;
}

void Settings::writeChangesToFile(){
    
    stringstream content;
    content << "{" << endl;
    Settings::createJSONStringWithIntValue(content, "framerate", frameRate, true);
    Settings::createJSONStringWithIntValue(content, "faceSize", faceSize, true);
    Settings::createJSONStringWithIntValue(content, "maxRows", maxRows, true);
    Settings::createJSONStringWithIntValue(content, "initRows", initRows, true);
    Settings::createJSONStringWithIntValue(content, "cameraZOffset", cameraZOffset, true);
    Settings::createJSONStringWithIntValue(content, "resolutionSize", resolutionSize, true);
    Settings::createJSONStringWithIntValue(content, "lineWidth", lineWidth, true);
    
    Settings::createJSONStringWithIntValue(content, "backgroundColor", backgroundColor, true);
    Settings::createJSONStringWithIntValue(content, "wireColor", wireColor, true);
    Settings::createJSONStringWithIntValue(content, "grayColor", grayColor, true);
    Settings::createJSONStringWithIntValue(content, "notSelectableColor", notSelectableColor, true);
    Settings::createJSONStringWithIntValue(content, "redColor", redColor, true);
    Settings::createJSONStringWithIntValue(content, "greenColor", greenColor, true);
    Settings::createJSONStringWithIntValue(content, "blueColor", blueColor, true);
    Settings::createJSONStringWithIntValue(content, "yellowColor", yellowColor, true);
    
    Settings::createJSONStringWithFloatValue(content, "dragSpeed", dragSpeed, true);
    Settings::createJSONStringWithBoolValue(content, "isDebugModeActive", debugMode, true);
    Settings::createJSONStringWithBoolValue(content, "isGridModeActive", gridMode, true);
    Settings::createJSONStringWithBoolValue(content, "shouldSnapToGrid", snapToGrid, true);
    Settings::createJSONStringWithBoolValue(content, "isSoundActive", soundActive, true);
    Settings::createJSONStringWithBoolValue(content, "isVibrationActive", vibrationActive, true);
    Settings::createJSONStringWithBoolValue(content, "isNetworkAllowed", networkAllowed, true);
    Settings::createJSONStringWithBoolValue(content, "isTutorialActive", tutorialActive, true);
    
    Settings::createJSONStringWithIntValue(content, "timeBonus", timeBonus, true);
    Settings::createJSONStringWithIntValue(content, "highscore", highscore, true);
    Settings::createJSONStringWithIntValue(content, "curscore", curScore, true);
    Settings::createJSONStringWithIntValue(content, "curNumberOfUsedColors", curNumberOfUsedColors, true);
    Settings::createJSONStringWithIntValue(content, "curNumberOfRows", curNumberOfRows, false);
    content << "}" << endl;

    NSString *file;
    NSString *filename = [NSString stringWithFormat:@"%@/configuration.json",[NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, true) objectAtIndex:0]];
    file = [NSString stringWithCString:content.str().c_str() encoding:NSUTF8StringEncoding];
    [file writeToFile:filename atomically:false encoding:NSUTF8StringEncoding error:nil];
    
}


void Settings::createJSONStringWithIntValue(stringstream &stream, string key, int value, bool comma){
    if(comma){ stream << "\"" << key << "\" : " << value << "," << endl; }
    else { stream << "\"" << key.c_str() << "\" : " << value << endl; }
}

void Settings::createJSONStringWithFloatValue(stringstream &stream, string key, float value, bool comma){
    if(comma){ stream << "\"" << key << "\" : " << value << "," << endl; }
    else { stream << "\"" << key.c_str() << "\" : " << value << endl; }
}

void Settings::createJSONStringWithBoolValue(stringstream &stream, string key, bool value, bool comma){
    if(comma){ stream << "\"" << key << "\" : " << value << "," << endl; }
    else { stream << "\"" << key.c_str() << "\" : " << value << endl; }
}

void Settings::createJSONStringWithStringValue(stringstream &stream, string key, string value, bool comma){
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
    dragSpeed = snapToGrid ? 0.0f : 0.9f;
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
    return snapToGrid;
}

bool Settings::getNetworkAllowed(){
    return networkAllowed;
}

bool Settings::isNewHighscore(){
    if( curScore >= highscore){
        highscore = curScore;
        return true;
    }
    return false;
}

const char* Settings::getMenuModelPath(){
    return "model/cube.dae" ;
}

int Settings::getHightscore(){
    return highscore;
}

int Settings::getCurScore(){
    return curScore;
}

void Settings::setCurScore(int value){
    curScore += value;
    this->isNewHighscore();
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

void Settings::setSound(bool value){
    soundActive = value;
}

void Settings::setVibration(bool value){
    vibrationActive = value;
}

void Settings::setSnapToGrid(bool value){
    snapToGrid = value;
}

void Settings::setNetwork(bool value){
    networkAllowed = value;
}

bool Settings::isTutorialActivated(){
    return tutorialActive;
}

void Settings::setTutorialActiveState(bool state){
    tutorialActive = state;
}

void Settings::setCurArchievement(int value){
    curArchievment = value;
    requiredArchievement = (int)(100 - 100/curNumberOfUsedColors) + curNumberOfRows*curNumberOfRows;
    archievementColor = (curArchievment >= requiredArchievement) ? greenColor : redColor;
    lvlPassed = (curArchievment >= requiredArchievement) ? true : false;
}

int Settings::getCurArchievement(){
    return curArchievment;
}

int Settings::getRequiredArchievement(){
    return requiredArchievement;
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

int Settings::getInitTime(){
    return 30;
}




