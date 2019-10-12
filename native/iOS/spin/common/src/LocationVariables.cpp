#include "LocationVariables.h"


LocationVariables::LocationVariables(){}
LocationVariables::LocationVariables(const ofVec3f& p, const ofVec3f& up):position(p), upVector(up){};
LocationVariables::LocationVariables(const LocationVariables& other){
    position = other.getPosition();
    upVector = other.getUpVector();
}

const ofVec3f& LocationVariables::getPosition() const{
    return this->position;
}
const ofVec3f& LocationVariables::getUpVector() const{
    return this->upVector;
}
