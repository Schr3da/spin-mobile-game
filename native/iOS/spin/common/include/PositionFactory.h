#ifndef POSITION_FACTORY_HH
#define POSITION_FACTORY_HH

#include <ofMain.h>
#include <vector>
#include "CameraPosition.h"
#include "Settings.h"


class PositionFactory{

public:
    static PositionFactory& instance(){ //has to be implemented here
	return object;
    }
    ~PositionFactory();
    CameraPosition* getStartPosition();
    const std::vector<ofVec3f>& getPositionVectors();
    const std::vector<CameraPosition*>& getCameraPositions() const;
    Settings& getSettings();
    CameraPosition* addBoth(CameraPosition* c, CameraPosition* b,  int direction, bool bothways);

private:
    bool createPositions();
    std::vector<CameraPosition*> cameraPositions;
    CameraPosition* startPosition;

    PositionFactory(); //private constructor to make the class singleton
    PositionFactory & operator=(const PositionFactory& other); //RO3: forbids using of = operator, if needed make public and implement
    PositionFactory(const PositionFactory& other); //RO3: forbids using of copy constructor, if needed make public and implement
    std::vector<ofVec3f> positionVectors;
    Settings settings;
    static PositionFactory object; // The only object of the Singleton class
};

#endif // POSITION_FACTORY_HH
