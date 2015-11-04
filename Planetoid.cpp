#include "Planetoid.h"
#include <vector>

// Planetoid Default Constructor
Planetoid::Planetoid(){

}

// Planetoid Dynamic Constructor
Planetoid::Planetoid(int mass, int x, int y, int z, int vX, int vY, int vZ, int startLoc){
    Planetoid::mass = mass;
    Planetoid::x = x;
    Planetoid::y = y;
    Planetoid::z = z;
    Planetoid::vX = vX;
    Planetoid::vY = vY;
    Planetoid::vZ = vZ;
    Planetoid::startLoc = startLoc;
    Planetoid::currLoc = startLoc;
}

//Updates planetoids current position after each successful move
void Planetoid::setPosition(int x, int y, int z) {
    Planetoid::x = x;
    Planetoid::y = y;
    Planetoid::z = z;
}

//Used to set new grid location determined by the universe
void Planetoid::setCurrLoc(int loc) {
    Planetoid::currLoc = loc;
}

void Planetoid::setPathLength(int length) {
    Planetoid::pathLength = length;
}

void Planetoid::setCollided(bool flag) {
    collided = flag;
}

int Planetoid::getMass() {
    return mass;
}

int Planetoid::getStartLoc() {
    return startLoc;
}

int Planetoid::getCurrLoc() {
    return currLoc;
}

int Planetoid::getPathLength() {
    return pathLength;
}

bool Planetoid::getCollided() {
    return collided;
}

int Planetoid::getX() {
    return x;
}

int Planetoid::getY() {
    return y;
}

int Planetoid::getZ() {
    return z;
}

int Planetoid::getVX() {
    return vX;
}

int Planetoid::getVY() {
    return vY;
}

int Planetoid::getVZ() {
    return vZ;
}

// Planetoid Destructor
Planetoid::~Planetoid() {

}
