#include "Cube.h"
#include "PositionFactory.h"
#include <algorithm>
#include <stdexcept>

Cube::Cube(){}

Cube::Cube(int rows, int colors, int helpFaces){
    this->rows = rows;
    this->colors = colors;
    this->helpFaces = helpFaces;
    instanceCorrectInitialized = this->init();
    if(!instanceCorrectInitialized){
        cout << "Cube instace not correctly initialized"  <<endl;
        return;
    }
    /*
      self.placedColors = {};
      self.freeCubeColors = {};
      self.currentColor = undefined;

      self.freeCubeColors[faceColors.red]=0;
      self.freeCubeColors[faceColors.blue]=0;
      self.freeCubeColors[faceColors.yellow]=0;
      self.freeCubeColors[faceColors.green]=0;

      self.placedColors[faceColors.red]=0;
      self.placedColors[faceColors.blue]=0;
      self.placedColors[faceColors.yellow]=0;
      self.placedColors[faceColors.green]=0;
    */
}

int Cube::getTotalFacesNumber(){
    int total = faces.size();
    for (int i=0; i < faces.size(); i++) {
        Face& face = faces[i];
        scoreStatus::ScoreStatus state = face.getScoreInfo();
        if (state==scoreStatus::NOTSELECTABLE){
            total--;
        }
    }
    return total;
}

int Cube::getNumberOfCorrectFaces(){
    int correct=0;
    for (int i=0; i < faces.size(); i++) {
        Face& face = faces[i];
        scoreStatus::ScoreStatus state = face.getScoreInfo();
        if(state==scoreStatus::CORRECT){
            correct++;
        }
    }
    return correct;
}

int Cube::getNumberOfIncorrectFaces(){
    int wrong=0;
    for (int i=0; i < faces.size(); i++) {
        Face& face = faces[i];
        scoreStatus::ScoreStatus state = face.getScoreInfo();
        if(state==scoreStatus::INCORRECT){
            wrong++;
        }
    }
    return wrong;
}


int Cube::getScore(int timeLeft){
    int total = getTotalFacesNumber();
    int correct = getNumberOfCorrectFaces();
    int wrong = getNumberOfIncorrectFaces();
    return calculateScore(total,correct,wrong, timeLeft);
}

int Cube::calculateScore(float total, float correct, float wrong, float timeLeft){
    return (correct-wrong)/total*100+timeLeft;
}

void Cube::generateColors(){
    vector<int> possibleColors = settings->getFaceColors();
    if (possibleColors.size()<colors){
        throw std::invalid_argument("Cube was created with invalid colors parameter. Number too high");
    }

    shuffleVector(possibleColors);
    while(possibleColors.size()>colors){
        possibleColors.pop_back();
    }

    for (int i=0; i < possibleColors.size(); i++) {
        freeColors[possibleColors[i]]=0;
        placedColors[possibleColors[i]]=0;
    }
    currentColor = possibleColors[0];

    for (int i = 0; i < getFaceCount(); i++) {
        int color = possibleColors[i%colors];
        this->colorContainer.push_back(color);
        freeColors[color]++;
    }
    shuffleVector(colorContainer);
}

int Cube::getFaceCount(){
    return rows*rows*6;
}

void Cube::shuffleVector(vector<int>& vec){
    std::random_shuffle(vec.begin(), vec.end());
}

Cube::~Cube(){
    settings = NULL;
}

bool Cube::init(){
    settings = &PositionFactory::instance().getSettings();
    if(settings == NULL){
        return false;
    }
    if(rows == 0){
        rows = settings->getInitRows();
    }
    this->isSolutionVisible = false;
    this->correctColorsVisible = false;
    faceSegments = settings->getResolutionSize();
    faceSize = settings->getFaceSize();
    return this->loadCube();
}

int Cube::popColor(){
    if (colorContainer.size()==0){
        throw length_error("Cube::popColor was called when colorContainer.size()==0");
    }

    int faceColor = colorContainer.back();
    colorContainer.pop_back();
    return faceColor;
}

bool Cube::loadCube(){
      stringstream msg;
      msg<<"Scene::loadCube() entered. Rows: "<<rows;
      Logger::log(msg.str(),Logger::DEBUG);

      generateColors();
      faces.clear();
      int amount = 0;
      float faceWith = settings->getFaceSize();
      float halfFaceWidth = settings->getFaceSize() * 0.5;
      for(int x=0; x<rows; x++){
          for(int y=0; y<rows; y++){
              this->addFace(x, y, -halfFaceWidth, popColor(), FRONT);
              this->addFace(x, y, faceWith * rows - halfFaceWidth, popColor(), BACK);
              this->addFace(-faceWith + halfFaceWidth, x, y, popColor(), LEFT);
              this->addFace( faceWith * rows - halfFaceWidth, x, y ,popColor(), RIGHT);
              this->addFace(x, faceWith * rows - halfFaceWidth, y , popColor(), BOTTOM);
              this->addFace(x, -halfFaceWidth, y, popColor(), TOP);
              amount += 6;
          }
     }
    int tmp=rows*rows*6;
    if (amount!=tmp){
        Logger::log("Scene::loadCube() - Wrong amount of faces created!",Logger::ERROR);
        return false;
    }
    setHelpFaces();
    return true;
}

void Cube::setHelpFaces(){
    vector<int> helpIndex;
    for (int i=0; i < faces.size(); i++) {
        helpIndex.push_back(i);
    }
    shuffleVector(helpIndex);

    for (int i=0; i < helpFaces; i++) {
        int idx = helpIndex[i];
        Face& face = faces[idx];
        freeColors[face.getCorrectColor()]--;
        face.setUnselectable();
    }

}

void Cube::addFace(float x, float y, float z, int color){
    float initPos = (float)(-rows*faceSize)/2 + (float)faceSize/2;
    float xPosition= (x*faceSize) + initPos;
    float yPosition= (y*faceSize) + initPos;
    float zPosition= (z*faceSize) + initPos;
    ofVec3f pos = ofVec3f(xPosition, yPosition, zPosition);
    Face face(pos, faceSize, color);
    faces.push_back(face);
}

void Cube::addFace(float x, float y, float z, int color, FaceId identifier){
    float initPos = (float)(-rows*faceSize)/2 + (float)faceSize/2;
    float xPosition= (x*faceSize) + initPos;
    float yPosition= (y*faceSize) + initPos;
    float zPosition= (z*faceSize) + initPos;
    ofVec3f pos = ofVec3f(xPosition, yPosition, zPosition);
    Face face(pos, faceSize, color, identifier);
    faces.push_back(face);
}

int Cube::getRandomFaceColor(int x,int y,int z){
    bool x_region=(x==0 || x==rows-1);
    bool y_region=(y==0 || y==rows-1);
    bool z_region=(z==0 || z==rows-1);
    int color = settings->getBackgroundColor();
    if (!x_region && !y_region){
        color= settings->getGreenColor();
        if (z==0){
            color= settings->getRedColor();
        }
    }
    if (!x_region && !z_region){
        color=settings->getBlueColor();
        if(y==0){
            color=settings->getYellowColor();
        }
    }
    if (!z_region && !y_region){
        color=settings->getYellowColor();
        if(x==0){
            color=settings->getNotSelectableColor();
        }
    }
    return color;
}

bool Cube::update(){
    return true;
}

void Cube::draw(){
    if(instanceCorrectInitialized){
        for (vector<Face>::iterator iter = faces.begin(); iter!=faces.end(); iter++){
            iter->draw();
        }
    }
}

void Cube::drawDebug(){
    if(settings->isDebugModeActive()){
        int size = rows * faceSize;
        ofSetColor(255, 0, 0);
        ofNoFill();
        ofDrawBox(0, 0, 0, size, size, size);
        ofDrawSphere(0, 0, 0, 0.25);
    }
}

vector<Face>& Cube::getFaces(){
    return faces;
}

void Cube::showCorrectColors(){
    for (int i=0; i < faces.size(); i++) {
        Face& face = faces[i];
        face.showCorrectColor();
    }
    correctColorsVisible = true;
}

void Cube::showDefaultColors(){
    for (int i=0; i < faces.size(); i++) {
        Face& face = faces[i];
        face.showDefaultColor();
    }
}

void Cube::showUserColors(){
    for (int i=0; i < faces.size(); i++) {
        Face& face = faces[i];
        face.showUserColor();
    }
}

bool Cube::toggleFace(Face& face){
    int colorToBePlaced = currentColor;
    if (face.isSelectable()==false){
        return false;
    }
    if(this->shouldPlaceColorOnFace(face)){
        cout << "new color placed" << endl;
    } else if(this->shouldRemoveColorFromFace(face)){
        cout << "removed color from face" << endl;
    }
    return face.toggleSelection(colorToBePlaced);
}

bool Cube::shouldRemoveColorFromFace(Face &face){
    if (face.isColorPlacedByUser()){
        int color = face.getCurrentColor();
        freeColors[color]++;
        placedColors[color]--;
        if (currentColor==-1){
            this->getNextColor();
        }
        return true;
    }
    return false;
}
    
bool Cube::shouldPlaceColorOnFace(Face &face){
    if(!face.isColorPlacedByUser()){
        freeColors[currentColor]--;
        placedColors[currentColor]++;
        if (freeColors[currentColor]==0){
            this->getNextColor();
        }
        return true;
    }
    return false;
}

int Cube::getCurrentColor(){
    return currentColor;
}

int Cube::getNextColor(){
    vector<int> colors;

    for(map<int,int>::iterator iter = freeColors.begin(); iter!=freeColors.end();iter++){
        if (iter->second > 0){
            colors.push_back(iter->first);
        }
    }
    vector<int>::iterator i = find(colors.begin(),colors.end(),currentColor);
    if (i!=colors.end()){
        int index = distance(colors.begin(), i);
        index++;
        int color = colors[index%colors.size()];
        currentColor=color;
        return color;
    }
    if (colors.size()==0){ //all colors are placed
        currentColor=-1;
        return -1; // -1 = no more colors
    }
    currentColor = colors[0];
    return currentColor;
}

bool Cube::getIsSolutionVisibe(){
    return isSolutionVisible;
}

void Cube::setIsSolutionVisible(bool isVisible){
    isSolutionVisible = isVisible;
}

void Cube::switchBetweenUserAndCorrectColors(){
    if(correctColorsVisible){
        this->showUserColors();
        correctColorsVisible = false;
    } else {
        this->showCorrectColors();
        correctColorsVisible = true;
    }
}
