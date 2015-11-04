#include "Universe.h"
#include "Planetoid.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>

using namespace std;

// Global Universe
Universe* universe;

int main() {
    //Creating sequential access to the input file
    ifstream inFile("001.in");

    //Creating stringStream for parsing purposes
    stringstream ss;

    //Buckets for current parsed data
    string line; //Holds each line of data
    string temp; //Holds current token

    if(inFile.is_open()) {
        //Sets up Universe (logical filling the black hole in another universe)
        getline(inFile, line);
        ss << line;

        int* uData = new int[4];
        
        //Pushes all universe data into array to store it
        for(int u = 0; u < 4; u++) {
            getline(ss, temp, ' ');
            uData[u] = atoi(temp.c_str()); // Converts to int
        }

        //Clears stream for next use
        ss.clear();

        //Human readable universe data
        int pNum, xGridWidth, yGridDepth, zGridHeight;

        //Create readable variables for universe creation
        pNum = uData[0];
        xGridWidth = uData[1];
        yGridDepth = uData[2];
        zGridHeight = uData[3];

        //Array to hold all of our planetoid objects
        Planetoid* planetoids = new Planetoid[pNum];

        //count variable used to populate the planetoids index
        int planetIndex = 0;

        //Builds planetoids for each line of data
        while(planetIndex < pNum) {
            //Get each line of Planetoid Data
            getline(inFile, line);
            ss << line; //Push that data into the stringstream

            cout << line << endl;

            //Create an array to hold the parsed data
            int* pData = new int[7];
            
            // Pushes all planetoid data into array to store it
            for(int i = 0; i < 7; i++) {
                getline(ss, temp, ' ');
                pData[i] = atoi(temp.c_str()); // Converts to int
            }

            //Human readable planetoid data
            int mass, pX, pY, pZ, vX, vY, vZ;

            // Mass of planetoid
            mass = pData[0];

            //units = #ofGridSpaces
            pX = pData[1]; // planetoid's x position in the universe grid space
            pY = pData[2]; // planetoid's y position in the universe grid space
            pZ = pData[3]; // planetoid's z position in the universe grid space

            //units = #ofGridSpaces
            vX = pData[4]; // planetoid's velocity in the x direction;
            vY = pData[5]; // planetoid's velocity in the y direction;
            vZ = pData[6]; // planetoid's velocity in the x direction;

            // Calculates planetoids logical grid position in the 3D grid system
            // The logical grid index position is a logical indexing of the data structure without having one
            // The number of indices is equal to: 0 <= indices < (xGridWidth * yGridDepth * zGridHeight) - 1
            // Assume a 3 x 3 x 3 cube of space: the max index would be 3 * 3 * 3 = 27 but starting from 0 means 26

            // Lets first see 2D before moving into 3D
            // the grid position is going to increase starting in x as x increases and increase into further y rows
            // So first assume a 3 x 3 structure meaning (xGridWidth = 3, yGridDepth = 3):
            // x = 1; y = 2 translates to: 0 + x + (y * xGridWidth) = index 7

            // Now to take it 3D we want to increase to the next plane up after we've exhausted this 3 x 3 plane.
            // so instead of increasing by the xGridWidth, we increase by our 3 x 3 planes total amount of grid spaces
            // so lets look at if we wished to move up one to the location 3 x 3 x 2
            // first the index of 3 x 3 = 0 + 2 + (2 * 3) = 8 remember that the 2 is the index number taking into account we start at 0
            // next we want to move up one plane to 3 x 3 x 2: to increase by each z level we add the total number of grid spaces in the plane
            // therefore: 8 + (2 * 3 * 3) = 26 where the 2 is the number of planes we wished to increase by

            // So the final equation will look like this
            int startLoc = pX + (pY * xGridWidth) + (pZ * xGridWidth * yGridDepth); //Note: this is encapsulated in universe we just don't have one yet

            // Now we can logically keep track of each planets logical location
            // Without having to physically track it and store it in memory

            //Create planetoid on the heap
            Planetoid* planetoid = new Planetoid(mass, pX, pY, pZ, vX, vY, vZ, startLoc);

            //Places planetoid in the array of planetoids
            planetoids[planetIndex] = *planetoid;

            //Sets up variables for next iteration
            ss.clear();
            planetIndex++;
        }

        //Build Universe (logical big bang)
        universe = new Universe(pNum, planetoids, xGridWidth, yGridDepth, zGridHeight);

        //run simulation
        bool valid = false;
        while(!valid) {
            // If valid is equal to true then there will be no more collisions
            // If valid is false then the state has changed and we must rerun the simulation
            // The state change occurs when a time t with collisions has resolved (all collisions in that t resolve first)
            cout << "Initializing new Universe" << endl;
            valid = universe->simulate();
        }


        //Get the final array of planets and output each remaining planets data
        Planetoid* tPlanets = universe->getPlanets();

        //Open an outFile stream and write the output
        ofstream outFile("output.txt");

        outFile << universe->getPlanetoidNum() << endl;

        for(int f = 0; f < universe->getPlanetoidNum(); f++) {
            outFile << tPlanets[f].getMass() << " " << tPlanets[f].getX() << " " << tPlanets[f].getY() << " " << tPlanets[f].getZ() << " " << tPlanets[f].getVX() << " " << tPlanets[f].getVY() << " " << tPlanets[f].getVZ() << endl;
        }

        // Close outFile
        outFile.close();
    }

    // Close inFile
    inFile.close();

    return 0;
}
