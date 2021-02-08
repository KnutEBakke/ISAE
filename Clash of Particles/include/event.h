/**
 * @file event.h
 *
 * @brief Simple definition of a particle and usefull fonctions for the project
 *
 * @author Knut Bakke
 *
 * This is a simple definition of a event
 *
 * The API of the event is defined as follows:
 *
 * - a function to create an empty particle
 * - a function to print a particle
 * - a function to deallocate a particle
 * - a function to update the position of a particle, given a variation 
 * 	 of time
 * - a function to calculate the time until a vertical wall collision
 * - a function to calculate the time until a horizontal wall collision
 * - a function to update the velocity after a vertical wall collision
 * - a function to update the velocity after a horizontal wall collision
 * - a function to calculate the time until a collision between two particles
 * - a function to update the velocity after a collision between two collisions
 *
 * You should always call the deallocate function when you do not
 * need an event anymore.
 */

#ifndef EVENT_H
#define EVENT_H
#include "particles.h"
#include "libs.h"

/**
 * @brief An alias for the structure representing the events
 */
typedef struct event  event;

/**
 * @brief The structure representing the event
 */

struct event { 
	double time;
	particle * p_particle_a;
	particle * p_particle_b;
	int collision_nb_a;
	int collision_nb_b;
};

/**
 * @brief Test if the event is a refreshing_event
 *
 * @param p_event  a pointer to the event
 *
 * @post Returns a boolean value indicating if the event is a refreshing event or not
 */

bool refreshing_event(event*);

/**
 * @brief Test if the event is a refreshing_event
 *
 * @param p_event  a pointer to the event
 *
 * @post Returns a boolean value indicating if the event is a refreshing event or not
 */
 
bool vertical_event(event*);

/**
 * @brief Test if the event is a refreshing_event
 *
 * @param p_event  a pointer to the event
 *
 * @post Returns a boolean value indicating if the event is a refreshing event or not
 */
 
bool horizontal_event(event*);

/**
 * @brief Test if the event is a refreshing_event
 *
 * @param p_event  a pointer to the event
 *
 * @post Returns a boolean value indicating if the event is a refreshing event or not
 */
 
bool collision_event(event*);

/**
 * @brief Creates an event
 *
 * @param t the time of the event
 * 
 * @param a a pointer to the a particle
 * 
 * @param b a pointer to the b particle
 * 
 * @param nb_a the number of collisions of the particle a
 * 
 * @param nb_b the number of collisions of the particle b
 *
 * @post Return the new event
 */
 
event* create_event(double t, particle* a, particle* b, int nb_a, int nb_b);

/**
 * @brief Checks if the event is valid
 *
 * @param e a pointer to the event
 * 
 * @post Returns a boolean indicating if the event is valid
 */

bool is_valid(event* e);


#endif 
