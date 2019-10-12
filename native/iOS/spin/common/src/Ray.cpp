//
//  Ray.cpp
//  spincpp
//
//  Created by schr3da on 22/02/15.
//
//

#include "Ray.h"

Ray::Ray(){

}

Ray::Ray( const ofVec3f &aOrigin, const ofVec3f &aDirection ) : mOrigin( aOrigin ) {
    setDirection( aDirection );
}

Ray::~Ray(){

}

ofVec3f Ray::calcPosition(float t) {
    return mOrigin + mDirection * t;
}

bool Ray::calcTriangleIntersection( const ofVec3f &vert0, const ofVec3f &vert1, const ofVec3f &vert2, float *result ) const
{
    ofVec3f edge1, edge2, tvec, pvec, qvec;
    float det;
    float u, v;
    const float EPSILON = 0.000001f;

    edge1 = vert1 - vert0;
    edge2 = vert2 - vert0;

    pvec = getDirection().getCrossed( edge2 );
    det = edge1.dot( pvec );

#if 0 // we don't want to backface cull
    if ( det < EPSILON )
        return false;
    tvec = getOrigin() - vert0;

    u = tvec.dot( pvec );
    if ( ( u < 0.0f ) || ( u > det ) )
        return false;

    qvec = tvec.getCrossed(edge1);
    v = getDirection().dot( qvec );
    if ( v < 0.0f || u + v > det )
        return false;

    *result = edge2.dot( qvec ) / det;
    return true;
#else
    if( det > -EPSILON && det < EPSILON )
        return false;

    float inv_det = 1.0f / det;
    tvec = getOrigin() - vert0;
    u = tvec.dot( pvec ) * inv_det;
    if( u < 0.0f || u > 1.0f )
        return false;

    qvec = tvec.getCrossed(edge1);

    v = getDirection().dot( qvec ) * inv_det;
    if( v < 0.0f || u + v > 1.0f )
        return 0;

    *result = edge2.dot( qvec ) * inv_det;
    return true;
#endif
}

bool Ray::calcPlaneIntersection( const ofVec3f &planeOrigin, const ofVec3f &planeNormal, float *result ) const
{
    float denom = planeNormal.dot(getDirection());
    if(denom != 0.0f){
        *result = planeNormal.dot(planeOrigin - getOrigin()) / denom;
        return true;
    }
    return false;
}

bool Ray::intersectsMesh(const ofVec2f &screenCoordinates,const ofMesh &mesh,const ofCamera &cam,const ofMatrix4x4 &toWorldSpace){
    ofVec3f screenToWorld = cam.screenToWorld(ofVec3f(screenCoordinates.x,screenCoordinates.y,0.0));
    Ray ray(cam.getPosition(), screenToWorld - cam.getPosition());

    const vector<ofMeshFace>& faces = mesh.getUniqueFaces();
    bool intersection = false;
    float t = 0;
    for (unsigned int i = 0; i < faces.size() ; i++) {
        const ofMeshFace &face = faces[i];
        // intersections are done worldSpace
        ofVec3f one = face.getVertex(0) * toWorldSpace;
        ofVec3f two = face.getVertex(1) * toWorldSpace;
        ofVec3f three = face.getVertex(2) * toWorldSpace;
        intersection = ray.calcTriangleIntersection(one,two,three, &t);
        if (intersection) {
            break;
        }
    }
    return intersection;
}

char Ray::getSignX(){
    return mSignX;
}

char Ray::getSignY(){
    return mSignY;
}

char Ray::getSignZ(){
    return mSignZ;
}

const ofVec3f& Ray::getDirection() const{
    return mDirection;
}

const ofVec3f& Ray::getInverseDirection() const{
    return mInvDirection;
}

void Ray::setOrigin( const ofVec3f &aOrigin ){
    mOrigin = aOrigin;
}

const ofVec3f& Ray::getOrigin() const{
    return mOrigin;
}

void Ray::setDirection( const ofVec3f &aDirection ){
    mDirection = aDirection;
    mInvDirection = ofVec3f( 1.0f / mDirection.x, 1.0f / mDirection.y, 1.0f / mDirection.z );
    mSignX = ( mDirection.x < 0.0f ) ? 1 : 0;
    mSignY = ( mDirection.y < 0.0f ) ? 1 : 0;
    mSignZ = ( mDirection.z < 0.0f ) ? 1 : 0;
}
