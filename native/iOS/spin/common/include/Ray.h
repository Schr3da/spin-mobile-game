//
//  Ray.h
//  spincpp
//
//  Created by schr3da on 22/02/15.
//
//

#ifndef __spincpp__Ray__
#define __spincpp__Ray__

#include <stdio.h>
#include "ofMain.h"

class Ray {
public:
    Ray();
    ~Ray();
    Ray(const ofVec3f &aOrigin, const ofVec3f &aDirection);
    friend class ofMeshFace;
    
    static bool intersectsMesh(const ofVec2f &screenCoordinates,const ofMesh &mesh,const ofCamera &cam,const ofMatrix4x4 &toWorldSpace);
    
    ofVec3f calcPosition( float t );
    bool calcTriangleIntersection( const ofVec3f &vert0, const ofVec3f &vert1, const ofVec3f &vert2, float *result ) const;
    bool calcPlaneIntersection( const ofVec3f &origin, const ofVec3f &normal, float *result ) const;
    void setOrigin( const ofVec3f &aOrigin );
    void setDirection( const ofVec3f &aDirection );
    const ofVec3f& getOrigin() const;
    const ofVec3f& getDirection() const;
    const ofVec3f& getInverseDirection() const;
    char getSignX();
    char getSignY();
    char getSignZ();

protected:
    ofVec3f mOrigin;
    ofVec3f mDirection;
    ofVec3f mInvDirection;
    char mSignX;
    char mSignY;
    char mSignZ;
};



#endif /* defined(__spincpp__Ray__) */
