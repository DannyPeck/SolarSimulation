#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "Planetoid.h"

class Universe {
    private:
        int planetoidNum;
        Planetoid* planets;
        int xGridWidth;
        int yGridDepth;
        int zGridHeight;
        bool invalid;
    public:
        Universe();
        Universe(int pNum, Planetoid* planets, int xGridWidth, int yGridDepth, int zGridHeight);
        bool simulate();
        int calcLCM();
        int calcCurrLocation(int x, int y, int z);
        void calcNextLocation(Planetoid* planet);
        int getPlanetoidNum();
        Planetoid* getPlanets();
        ~Universe();
};

#endif // UNIVERSE_H
