#ifndef __SpinCpp__CameraPositionSorter__
#define __SpinCpp__CameraPositionSorter__

#include "ofMain.h"
#include "CameraPosition.h"

class CameraPositionSorter{
public:
    CameraPositionSorter(ofNode object);
    CameraPositionSorter(const LocationVariables& var);
    bool operator()(const CameraPosition* c1, const CameraPosition* c2) const;

private:
    ofVec3f referencePosition;
    ofVec3f referenceUpVector;
};

#endif
