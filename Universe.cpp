#include "Universe.h"
#include "Planetoid.h"

#include <iostream>

// Universe's Default Constructor
Universe::Universe(){

}

// Universe's Dynamic Constructor
Universe::Universe(int planetoidNum, Planetoid* planets, int xGridWidth, int yGridDepth, int zGridHeight){
    Universe::planetoidNum = planetoidNum;
    Universe::planets = planets;
    Universe::xGridWidth = xGridWidth;
    Universe::yGridDepth = yGridDepth;
    Universe::zGridHeight = zGridHeight;
}

// Simulates all of a given environments possible combinations for collisions
// If collision is found return to re-run simulation with new planetoid configuration
bool Universe::simulate() {

    bool valid = true;

    // For each Planet simulate their movement to determine their pathLength
    // PathLength: Number of moves to return to their original location

    // Calculates the time t required to return the state of the system to original state
    // By calculating the Lowest Common Multiple of all planetoids pathLengths'
    int lcm = calcLCM();

    // Simulates maximum possibilities of system
    for(int t = 0; t < lcm; t++) {

        cout << "Time: " << t << endl;

        /*
        For each planetoid in System compare its current Location with the other
        planetoids and all that share a position: create 1 new planetoid at that position
        */

        // Temporary array of planets which holds the new array of planets at t after collisions
        Planetoid* tPlanetoids = new Planetoid[planetoidNum];

        int newPNum = planetoidNum; // Tracks current number of planetoids as we collide
        int collNum = 0; // Tracks indexing with respect to adding new planets that result from collision

        //for each planet that has not already been involved in a collision
        for(int a = 0; a < planetoidNum && !planets[a].getCollided(); a++) {

            // Tracks number of collided Planetoids per run
            int collideNum = 0;

            //Human readable variables to build updated data off of
            int mass = planets[a].getMass();
            int vX = planets[a].getVX();
            int vY = planets[a].getVY();
            int vZ = planets[a].getVZ();

            // Print's each current planets data for debugging purposes
            cout << endl;
            cout << "Planet A Position: " << planets[a].getX() << " " << planets[a].getY() << " " << planets[a].getZ() << endl;
            cout << "Planet A Velocity: " << vX << " " << vY << " " << vZ << endl;
            cout << endl;

            // For each other planetoid in the system that we could collide with
            for(int b = 0; b < planetoidNum; b++) {
                //Skip comparing position with itself
                if(b != a) {
                    // Print's each compared planets data for debugging purposes
                    cout << endl;
                    cout << "Planet B Position: " << planets[b].getX() << " " << planets[b].getY() << " " << planets[b].getZ() << endl;
                    cout << "Planet B Velocity: " << planets[b].getVX() << " " << planets[b].getVY() << " " << planets[b].getVZ() << endl;
                    cout << endl;

                    //Checks to see if working planet is in the same position as the comparing planet
                    if(planets[a].getCurrLoc() == planets[b].getCurrLoc()) {
                        // Updates new result planets properties
                        mass += planets[b].getMass();
                        vX += planets[b].getVX();
                        vY += planets[b].getVY();
                        vZ += planets[b].getVZ();

                        // Makes sure to only count Planet A once even tho comparing multiple times
                        if(!planets[a].getCollided()) {
                            // Sets the working planets collided flag so that it is not considered again
                            planets[a].setCollided(true);
                            collideNum++;
                        } // end starter case for setting working planet

                        // Sets the involved planets collided flag so that they are not considered again
                        // Remember that this is happening in a solid time t and that it is re evaluated at each t
                        planets[b].setCollided(true);
                        
                        // Tracks number of planetoids involved in the collision
                        collideNum++;
                    } else {
                        // Print's if No collision occurred
                        cout << "No Collision" << endl;
                    }
                } else {
                    // Print's that it tried to compare itself to itself
                    cout << "Don't compare yourself" << endl;
                } // end self check detection
            } // end comparing other planetoids

            // Updates global collision count
            if(collideNum != 0) { // if != 0 then we had at least one collision
                // Calculate new planetoids velocity vector
                cout << "Planet A + B: " << vX << " " << vY << " " << vZ << endl;
                cout << collideNum << endl;
                int newVX = (vX / collideNum);
                int newVY = (vY / collideNum);
                int newVZ = (vZ / collideNum);
                cout << "Planet C: " << newVX << " " << newVY << " " << newVZ << endl;

                //Create new Planetoid that is a combination of all planets involved in the collision
                Planetoid* tPlanet = new Planetoid(mass, planets[a].getX(), planets[a].getY(), planets[a].getZ(), newVX, newVY, newVZ, planets[a].getCurrLoc());
                tPlanetoids[collNum] = *tPlanet; // Store new planet in new array of planets

                // Sets valid to false because we need to re run new simulation with new array of planets
                valid = false;
            } // end result from collision

            // Updates newPNum to be equal to current amount of planets, subtracts 1 because if 3 collided we only removed 2
            newPNum -= collideNum - 1;

            // Resets collided count for next time t
            collideNum = 0;

        } // end current t's analysis


        cout << "end of current t = " << t << "'s analysis" << endl;

         // If the universe needs a reset return that it needs reset
        if(!valid) {
            // Adds the remaining uncollided planets into the new array
            for(int v = 0; v < planetoidNum; v++) {
                if(planets[v].getCollided() == false) {
                    tPlanetoids[v] = planets[v];
                } // end collided flag check
            } // end remaining planet addition

            // array of new Planets
            Planetoid* newPlanets = new Planetoid[newPNum+1];

            // Adds the new planets that were the result of collisions
            for(int n = 0; n < newPNum; n++) {
                newPlanets[n] = tPlanetoids[n];
            } // end planet array population

            cout << newPNum << endl;

            // Update Universe with new environment
            Universe::planets = newPlanets;
            Universe::planetoidNum = newPNum;

            // if we found a collision return because we need to restart the simulation
            return valid;
        }
        else {
            // if we didn't find collisions advance all planets by velocity
            // and move forward to next t
            for(int m = 0; m < planetoidNum; m++) {
                calcNextLocation(&planets[m]);
            } // location update
        }   // end no collision result
    } // end simulation
    return valid;
} // end simulation

// Calculates the Lowest Calm Multiple of the all the pathLengths
int Universe::calcLCM() {
    //Number of times we need to advance whole universe to
    //return to where all planets are their starting position
    int lcm = 0;

    for(int p = 0; p < planetoidNum; p++) {
        int pathLength = 0;
        bool keepGoing = true;

        //Moves planet location by velocity until it reaches original location
        while(keepGoing) {
            // Calculates new position and currLoc and updates them
            calcNextLocation(&planets[p]);
            pathLength++;

            // Once it reaches original point than it will end with correct pathLength
            if(planets[p].getStartLoc() == planets[p].getCurrLoc()) {
                keepGoing = false;
            }
        }

        // Set the pathLength
        planets[p].setPathLength(pathLength);

        // Generates the lowest common multiple between each planetoids path lengths
        // If it is first pass then set initial lcm
        if(p == 0) {
            lcm = pathLength;
        }
        else {
            if(lcm % pathLength != 0) {
                lcm *= pathLength; // if not a multiple then create new lcm
            }
        }

        cout << "Planet " << p << "'s Path Length: " << planets[p].getPathLength() << endl;
        cout << "Lowest Common Multiple: " << lcm << endl;
    }

    return lcm;
}

int Universe::calcCurrLocation(int x, int y, int z) {
    int location = x + (y * xGridWidth) + (z * xGridWidth * yGridDepth);
    return location;
}

void Universe::calcNextLocation(Planetoid* planet) {
    // Calculates raw result of position + velocity
    int newX = (planet->getX() + planet->getVX());
    int newY = (planet->getY() + planet->getVY());
    int newZ = (planet->getZ() + planet->getVZ());

    // Updates values to account for wrapping
    if(newX < 0) {
        newX = xGridWidth + newX;
    }
    else {
        newX = newX % xGridWidth;
    }

    if(newY < 0) {
        newY = yGridDepth + newY;
    }
    else {
        newY = newY % yGridDepth;
    }

    if(newZ < 0) {
        newZ = zGridHeight + newZ;
    }
    else {
        newZ = newZ % zGridHeight;
    }

    // Calculates new logical gridLocation based off new position
    int currLoc = calcCurrLocation(newX, newY, newZ);

    // Updates planets properties
    planet->setPosition(newX, newY, newZ);
    planet->setCurrLoc(currLoc);
}

int Universe::getPlanetoidNum() {
    return planetoidNum;
}

Planetoid* Universe::getPlanets() {
    return planets;
}

// Universe Destructor
Universe::~Universe() {
    delete[] planets;
}
