//
//  World.h
//
//  A module to represent the world for the game.
//

#ifndef WORLD_H
#define WORLD_H

#include <string>



const unsigned int ROW_COUNT    = 6;
const unsigned int COLUMN_COUNT = 9;

typedef unsigned int World[ROW_COUNT][COLUMN_COUNT];



void worldLoadAll (World world, std::string game_name);
void worldLoadNodes (World world, std::string filename);
void worldLoadDescriptions (World world, std::string filename);
void worldDebugPrint (const World world);
void worldFindStart (const World world,
                     unsigned int& row, unsigned int& column);
bool worldIsValid (const World world,
                   unsigned int row, unsigned int column);
void worldPrintDescription (const World world,
                            unsigned int row, unsigned int column);
bool worldCanGoNorth (const World world,
                      unsigned int row, unsigned int column);
bool worldCanGoSouth (const World world,
                      unsigned int row, unsigned int column);
bool worldCanGoEast  (const World world,
                      unsigned int row, unsigned int column);
bool worldCanGoWest  (const World world,
                      unsigned int row, unsigned int column);
bool worldIsDeath   (const World world,
                     unsigned int row, unsigned int column);
bool worldIsVictory (const World world,
                     unsigned int row, unsigned int column);



#endif
