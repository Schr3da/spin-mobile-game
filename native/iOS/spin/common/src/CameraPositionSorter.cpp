#include "CameraPositionSorter.h"

CameraPositionSorter::CameraPositionSorter(ofNode object){
    this->referencePosition = object.getPosition();
    this->referenceUpVector =  object.getYAxis();
}

CameraPositionSorter::CameraPositionSorter(const LocationVariables& var){
    this->referencePosition = var.getPosition();
    this->referenceUpVector =  var.getUpVector();
}


bool CameraPositionSorter::operator()(const CameraPosition* c1, const CameraPosition* c2) const {
    // if position vector is equal, we want to choose the position with the smaller distance to current Up-vector
    if (c1->getPosition().angle(referencePosition) == c2->getPosition().angle(referencePosition) ){
	return c1->getUpVector().angle(referenceUpVector) < c2->getUpVector().angle(referenceUpVector);
    }
    // else we want to choose the CameraPosition with smaller distance to current position
    return c1->getPosition().angle(referencePosition) < c2->getPosition().angle(referencePosition);
}
