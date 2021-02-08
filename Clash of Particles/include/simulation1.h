/**
 * @file simulation1.h
 *
 * @brief Definition of a simulation showing particles trapped in a 2D box
 *
 * @author Knut Bakke
 *
 * This is a simple simulation of trapped particles with elastic collisions
 *
 * The API of the particles is defined as follows:
 *
 * - a function to create random particles
 * - a function to draw particles
 * - a function to deallocate a list of particle pointers
 * - a function to update the position of a list of particle pointers, given a variation 
 * 	 of time
 * - a function to add vertical collisions of a particle to a heap
 * - a function to add horizontal collisions of a particle to a heap
 * - a function to add all collisions of a particle to a heap
 * - a function to run the simulation
 *
 */

#ifndef SIMULATION_H
#define SIMULATION_H

#include "binary-heap.h"	


/**
 * @brief Generates a list of particles with random values
 *
 * @param particle_nb the number of particles to generate
 *
 * @post Returns a pointer to the list of particle pointers
 */

particle** create_particles(int particle_nb);


/**
 * @brief Draws the particles in SDL
 *
 * @param particle_nb  the number of particles to draw
 *
 * @param p_list a pointer to a list of particle pointers
 * 
 * @param SIZE the size of the window where the particles are drawn
 * 
 * @post The particles are drawn in SDL
 */
 
void draw_particles(int particle_nb, particle** p_list, int SIZE);


/**
 * @brief Deallocates a list of particle pointers
 *
 * @param p_list a list of particle pointers
 *
 * @param particle_nb the number of particles to deallocate
 * 
 * @post The particles in the list are deallocated
 */


void deallocate_list(particle** p_list, int particle_nb);


/**
 * @brief Updates the position of particles in a list
 *
 * @param p_list a list of particle pointers
 * 
 * @param particle_nb the nombre of particles in the list
 * 
 * @param dt the time difference between the particle positions
 * 
 * @param mode indicates which simulation mode is running
 *
 * @post the positions are updated from t to t + dt
 */
 
void list_pos_up(particle ** p_list, int particle_nb, double dt, int mode);


/**
 * @brief Adds a vertical wall collisions event to a heap
 *
 * @param p_particle  a pointer to the particle
 * 
 * @param t_event the time of last event
 * 
 * @param Q a pointer to the heap where the collision event is added
 * 
 * @param t_max the maximum time of which the collision may occur
 *
 * @post The wall collision event where t < t_max is added
 */

void add_v_collision(particle* p_particle, double t_event, heap_event* Q, double t_max);

/**
 * @brief Adds a horizontal wall collisions event to a heap
 *
 * @param p_particle  a pointer to the particle
 * 
 * @param t_event the time of last event
 * 
 * @param Q a pointer to the heap where the collision event is added
 * 
 * @param t_max the maximum time of which the collision may occur
 * 
 * @param mode indicates which simulation mode is running
 *
 * @post The wall collision event where t < t_max is added
 */
 
void add_h_collision(particle* p_particle, double t_event, heap_event* Q, double t_max, int mode);

/**
 * @brief Adds all collisions of a particle to a heap
 *
 * @param p_particle  a pointer to the particle
 * 
 * @param t_event the time of last event
 * 
 * @param p_list a list of particle pointers
 * 
 * @param Q a pointer to the heap where the collision event is added
 * 
 * @param t_max the maximum time of which the collision may occur
 * 
 * @param start the position in p_list from where you start looking for particle collisions
 * 
 * @param finish the last position in p_list you look for particle collisions
 * 
 * @param mode indicates which simulation mode is running
 *
 * @post The wall collision event where t < t_max is added
 */
 
void add_collisions(particle* p_particle, double t_event, particle** p_list, heap_event* Q, double t_max, int start, int finish, int mode);

/**
 * @brief Simulates particles captured in a 2D box with elastic particle collision enabled
 * 
 * @param t_max the maximum time of which the collisions may occur
 * 
 * @param refresh_rate the refresh rate of the SDL window
 * 
 * @param particle_nb the number of particles in the simulation
 * 
 * @param SIZE the size of the box
 * 
 * @param p_list a list of particle pointers
 * 
 * @param mode indicates which simulation mode is running
 *
 * @post Simulates and draws the 2D box with particle collisions
 */

void simulation(double t_max,double refresh_rate, int particle_nb, int SIZE, particle ** p_list, int mode);

#endif

