/**
 * @file loader.h
 *
 * @brief Definition of a loader allowing to initiate paricle positions
 *
 * @author Knut Bakke
 *
 * This is a simple simulation of trapped particles with elastic collisions
 */

#ifndef LOADER_H
#define LOADER_H
#include "particles.h"


/**
 * @brief Loads particles from a text file into a list
 *
 * @param file a path to a file where the particles are written
 *
 * @post Returns a list of particles having the properties described in the text file
 */

particle ** loader(char* file);

#endif

