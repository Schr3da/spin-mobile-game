#ifndef CAMERAPOSITION_H
#define CAMERAPOSITION_H

#include <ofMain.h>
#include <string>
#include <sstream>
#include "LocationVariables.h"

class CameraPosition
{
    public:
        CameraPosition(ofVec3f p, ofVec3f u);
        CameraPosition(LocationVariables var);
        CameraPosition(const CameraPosition& other);
        CameraPosition* getLeftNeighbour() const;
        CameraPosition* getRightNeighbour() const;
        CameraPosition* getUpNeighbour() const;
        CameraPosition* getDownNeighbour() const;
        const ofVec3f& getPosition() const;
        const ofVec3f& getUpVector() const;
        const ofVec3f& getTarget() const;
        const LocationVariables& getPositionInfo() const;
        string toString() const;
        CameraPosition* friendPosition;

        void setLeftNeighbour(CameraPosition* pos);
        void setRightNeighbour(CameraPosition* pos);
        void setUpNeighbour(CameraPosition* pos);
        void setDownNeighbour(CameraPosition* pos);

    private:
        CameraPosition* leftNeighbour;
        CameraPosition* rightNeighbour;
        CameraPosition* upNeighbour;
        CameraPosition* downNeighbour;
	LocationVariables positionInfo;
	ofVec3f target;
};


inline bool operator==(const CameraPosition& a, const CameraPosition& b){
  return a.getPositionInfo()==b.getPositionInfo();
}
inline bool operator!=(const CameraPosition& lhs, const CameraPosition& rhs){return !(lhs == rhs);}

#endif // CAMERAPOSITION_H
