#include "FastNoiseLite.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <iostream>
#include "../globals.hpp"

int* generateTerrain()
{
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetSeed(1337);
    noise.SetFrequency(0.010);
    std::vector<float> noiseData(WORLD_WIDTH * WORLD_HEIGHT);
    int index = 0;

    int* world = new int[WORLD_WIDTH*WORLD_HEIGHT];

    std::ofstream file;
    file.open("../../src/worldSaves/noiseTest.txt");

    for (int y = 0; y < WORLD_HEIGHT; y++)
    {
        for (int x = 0; x < WORLD_WIDTH; x++)
        {
            if ((noiseData[index] = noise.GetNoise((float)x, (float)y)) > -0.5)
            {
                if (y < WORLD_HEIGHT/4)
                {
                    world[index] = 1;
                } else
                {
                    world[index] = 3;
                }
                
            } else
            {
                world[index] = 0;
            }
            index++;
        }
        file << ("\n");
    }

    file.close();
    return world;
}