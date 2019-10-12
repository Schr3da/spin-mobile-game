#ifndef __SpinCpp__Settings__
#define __SpinCpp__Settings__


#include <Foundation/Foundation.h>
#include "Global.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "json.h"
#include <fstream>
#include "Logger.h"
#include "Global.h"

class Settings{

public:
        Settings();
        ~Settings();

        static void createJSONStringWithIntValue(stringstream &stream, string key, int value, bool comma);
        static void createJSONStringWithBoolValue(stringstream &stream, string key, bool value, bool comma);
        static void createJSONStringWithStringValue(stringstream &stream, string key, string value, bool comma);
        static void createJSONStringWithFloatValue(stringstream &stream, string key, float value, bool comma);

        bool init();
        void setUpDefaultSettingVariables();
        void setPostLoadVariables();
        string readFileContentWithFilename( const char *filename);
        void loadSettings();
        int getFrameRate();
        int getFaceSize();
        int getInitRows();
        int getMaxRows();
        int getCameraZOffset();
        int getResolutionSize();
        int getLineWidth();

        int getBackgroundColor();
        int getWireColor();
        int getGrayColor();
        int getRedColor();
        int getGreenColor();
        int getPurpleColor();
        int getBlueColor();
        int getYellowColor();
        int getDefaultFaceColor();
        int getNotSelectableColor();
    
        vector<int> getFaceColors() const;

        float getDragSpeed();
        bool isDebugModeActive();
        bool isGridModeActive();
        bool shouldSnapToGrid();
    
        GSSize getScreenSize();
        GSSize getHalfScreenSize();
    
        ApplicationState getApplicationState();
        void setApplicationState(ApplicationState state);
    
        const char* getMenuModelPath();
    
        bool getSoundActive();
        bool getVibrationActive();
        bool getSnapToGrid();
        bool getNetworkAllowed();
        bool isTutorialActivated();
        bool isLvlPassed();
        bool isNewHighscore();
    
        int getCurNumberOfUsedColors();
        int getCurNumberOfRows();
        int getHightscore();
        int getCurScore();
        int getCurArchievement();
        int getTimeBonus();
        int getArchievementColor();
        int getRequiredArchievement();
        int getInitTime();
    
        void setCurNumberOfRows(int value);
        void setCurNumberOfUsedColors(int value);
        void setSound(bool value);
        void setVibration(bool value);
        void setSnapToGrid(bool value);
        void setNetwork(bool value);
        void setCurArchievement(int value);
        void setCurScore(int value);
        void setTimeBonus(int value);
        void setNewGameDefaultValues();
        void setTutorialActiveState(bool state);
        void writeChangesToFile();

private:
        int frameRate;
        int faceSize;
        int initRows;
        int maxRows;
        int cameraZOffset;
        int resolutionSize;
        int lineWidth;
    
        int backgroundColor;
        int wireColor;
        int grayColor;
        int redColor;
        int greenColor;
        int purpleColor;
        int blueColor;
        int yellowColor;
        int notSelectableColor;
        int archievementColor;
        int requiredArchievement;
    
        CGRect winSize;
    
        float dragSpeed;
        bool debugMode;
        bool gridMode;
        bool snapToGrid;
        bool soundActive;
        bool vibrationActive;
        bool networkAllowed;
        bool tutorialActive;
        bool lvlPassed;
    
        int curNumberOfUsedColors;
        int curNumberOfRows;
        int highscore;
        int curScore;
        int curArchievment;
        int timeBonus;
    
        ApplicationState applicationState;
        vector<int> faceColors;
    
        bool fileExistAtPath();
};

#endif
