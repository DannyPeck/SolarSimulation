#ifndef PLANETOID_H
#define PLANETOID_H

#include <vector>

using namespace std;

class Planetoid {
    private:
        int mass;
        int x, y, z; // Position Coordinate
        int vX, vY, vZ; // Velocity Vector
        int startLoc; // Planets original logical location
        int currLoc; // Planets current logical location
        int pathLength; // number of turns to return to startLoc
        bool collided; // flag for tracking which planets have been in a collision

    public:
        Planetoid();
        Planetoid(int mass, int x, int y, int z, int vX, int vY, int vZ, int startLoc);
        void setPosition(int x, int y, int z);
        void setCurrLoc(int loc);
        void setPathLength(int length);
        void setCollided(bool flag);
        int getMass();
        int getStartLoc();
        int getCurrLoc();
        int getPathLength();
        bool getCollided();
        int getX();
        int getY();
        int getZ();
        int getVX();
        int getVY();
        int getVZ();
        ~Planetoid();
};

#endif // PLANETOID_H
