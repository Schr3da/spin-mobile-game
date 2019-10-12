#include "CameraPosition.h"

CameraPosition::CameraPosition(ofVec3f p, ofVec3f u) {
    positionInfo = LocationVariables(p,u);
    target = ofVec3f(0,0,0);
    leftNeighbour=NULL;
    rightNeighbour=NULL;
    upNeighbour=NULL;
    downNeighbour=NULL;
    friendPosition=NULL;
}

CameraPosition::CameraPosition(LocationVariables var) : positionInfo(var), target(ofVec3f(0,0,0)) {
    leftNeighbour=NULL;
    rightNeighbour=NULL;
    upNeighbour=NULL;
    downNeighbour=NULL;
}
CameraPosition::CameraPosition(const CameraPosition& other){
    leftNeighbour=NULL;
    rightNeighbour=NULL;
    upNeighbour=NULL;
    downNeighbour=NULL;

    //leftNeighbour = other.getLeftNeighbour();
    //rightNeighbour  = other.getRightNeighbour();
    upNeighbour  = other.getUpNeighbour();
    downNeighbour  = other.getDownNeighbour();
    positionInfo = other.getPositionInfo();
    target = other.getTarget();

}

CameraPosition* CameraPosition::getLeftNeighbour() const{
	return this->leftNeighbour;
}
CameraPosition* CameraPosition::getRightNeighbour() const{
	return this->rightNeighbour;
}
CameraPosition* CameraPosition::getUpNeighbour() const{
	return this->upNeighbour;
}
CameraPosition* CameraPosition::getDownNeighbour() const{
	return this->downNeighbour;
}
const ofVec3f& CameraPosition::getPosition() const{
        return this->positionInfo.getPosition();
}
const ofVec3f& CameraPosition::getUpVector() const{
    return this->positionInfo.getUpVector();
}
const ofVec3f& CameraPosition::getTarget() const{
	return this->target;
}
void CameraPosition::setLeftNeighbour(CameraPosition* pos){
	this->leftNeighbour=pos;
}
void CameraPosition::setRightNeighbour(CameraPosition* pos){
	this->rightNeighbour=pos;
}
void CameraPosition::setUpNeighbour(CameraPosition* pos){
	this->upNeighbour=pos;
}
void CameraPosition::setDownNeighbour(CameraPosition* pos){
	this->downNeighbour=pos;
}
string CameraPosition::toString() const{
  ostringstream str;
  str<< "CameraPositin: "<<this->getPosition()<<endl;
  return str.str();
}

const LocationVariables& CameraPosition::getPositionInfo() const{
    return this->positionInfo;
}
