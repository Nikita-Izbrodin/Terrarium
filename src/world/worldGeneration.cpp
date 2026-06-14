#include "FastNoiseLite.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <iostream>
#include <cmath>
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
                if (y < WORLD_HEIGHT/4)
                {
                    world[index] = 1;
                } else
                {
                    world[index] = 1;
                }
            }
            index++;
        }
    }

    for (int x = 0; x < WORLD_WIDTH; x++)
        {
           if (world[x + (WORLD_HEIGHT/4) * WORLD_WIDTH] == 3)
           {
                world[x + (WORLD_HEIGHT/4) * WORLD_WIDTH] = 0;
           }
        }

    for (int x = 0; x < WORLD_WIDTH; x++)
        {
            double xDegrees = x*3.141592653589793/180*10;
            int yLevel = std::round(std::sin(xDegrees)*10);
            if ((yLevel >= 0) && (world[x + (WORLD_HEIGHT/4) * WORLD_WIDTH] != 1))
            {
                world[x + (WORLD_HEIGHT/4 - yLevel) * WORLD_WIDTH] = 0;
                
                yLevel--;
                while (yLevel >= 0)
                {
                    world[x + (WORLD_HEIGHT/4 - yLevel) * WORLD_WIDTH] = 3;
                    yLevel--;
                }
            }
            
        }

    return world;
}