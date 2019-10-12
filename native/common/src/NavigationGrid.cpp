#include "NavigationGrid.h"
#include <cmath>
#include <algorithm>
#include <ofMain.h>
#include <vector>
#include "PositionFactory.h"
#include "CameraPositionSorter.h"

NavigationGrid::NavigationGrid() : settings(PositionFactory::instance().getSettings()) {}

bool NavigationGrid::init(){
    return true;
}

bool NavigationGrid::update(){
    return true;
}

void NavigationGrid::draw(){

}

void NavigationGrid::drawDebug(){
    if( settings.isGridModeActive() == true){
	std::vector<ofVec3f> gridVectors = PositionFactory::instance().getPositionVectors();
        for(std::vector<ofVec3f>::const_iterator vector=gridVectors.begin(); vector!=gridVectors.end(); vector++){
            ofSetHexColor(0xf22613);
            ofSetLineWidth( settings.getLineWidth() );
            ofLine(0, 0, 0, vector->x, vector->y, vector->z);
            ofSetHexColor( settings.getBackgroundColor() );
        }
    }
}

CameraPosition* NavigationGrid::getGridPosition(const ofNode &object){
    std::vector<CameraPosition*> cameraPositions = PositionFactory::instance().getCameraPositions();
    std::vector<CameraPosition*>::const_iterator targetCameraPosition = std::min_element(cameraPositions.begin(),
											 cameraPositions.end(),
											 CameraPositionSorter(object));
    return *targetCameraPosition;
}


CameraPosition* NavigationGrid::getGridPosition(const LocationVariables& var){
    std::vector<CameraPosition*> cameraPositions = PositionFactory::instance().getCameraPositions();
    std::vector<CameraPosition*>::const_iterator targetCameraPosition = std::min_element(cameraPositions.begin(),
											 cameraPositions.end(),
											 CameraPositionSorter(var));

    return *targetCameraPosition;
}
