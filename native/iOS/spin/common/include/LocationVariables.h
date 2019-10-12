#ifndef LOCATIONVARIABLES_H
#define LOCATIONVARIABLES_H
#include <ofMain.h>


class LocationVariables{
    public:
        LocationVariables();
        LocationVariables(const ofVec3f& p, const ofVec3f& up);
        LocationVariables(const LocationVariables& other);
        const ofVec3f& getPosition() const;
        const ofVec3f& getUpVector() const;

    private:
        ofVec3f position;
        ofVec3f upVector;
};


inline bool operator==(const LocationVariables& a, const LocationVariables& b){
    return a.getPosition()==b.getPosition() && a.getUpVector()==b.getUpVector();
}

inline bool operator!=(const LocationVariables& lhs, const LocationVariables& rhs){
    return !(lhs == rhs);
}

#endif /* LOCATIONVARIABLES_H */
