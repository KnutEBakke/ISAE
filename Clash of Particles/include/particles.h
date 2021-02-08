/**
 * @file particles.h
 *
 * @brief Simple definition of a particle and usefull fonctions for the project
 *
 * @author Knut Bakke
 *
 * This is a simple definition of a particle
 *
 * The API of the particles is defined as follows:
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
 * need a particle anymore.
 */

#ifndef PARTICLES_H
#define PARTICLES_H
#include "disc.h"
/**
 * @brief An alias for the structure representing the particles
 */
typedef struct particle  particle;

/**
 * @brief The structure representing particle
 */

struct particle { 
	double* position;
	double* velocity;
	double mass;
	double radius;
	int collision_nb;
	enum color color;
};

// Auxiliary functions //
double scalaire(double*  , double*);
double* diff(double*, double*);
// END //

/**
 * @brief Creates an empty particle
 *
 * @post After the call, the returned pointer points to a NULL particle.
 */

particle * nil_particle(void);


/**
 * @brief Deallocates the particle
 *
 * @param p_particle  a pointer to the particle to be deallocated
 *
 * @post The particle is now deallocated
 */

void deallocate_particle(particle* p_particle);

/**
 * @brief Prints the particle

 * @param p_particle  a pointer to the particle to be printed
 *
 * @post The different characteristics of the particle is printed
 */

void print_particle(particle* p_particle);

/**
 * @brief Updates the particle position
 *
 * @param p_particle  a pointer to the particle to be updated
 * 
 * @param dt the time difference between the old and the new position
 * 
 * @param mode a int that modifies the fonction mode for simulation
 *
 * @post The particle position is updated from t to t+dt
 */
void pos_up(particle* p_particle, double dt, int mode);

/**
 * @brief Calculate the time until the particle collides with a vertical wall
 *
 * @param p_particle  a pointer to the particle
 *
 * @post Returns time until collison
 */

double t_v_wall_collision(particle* p_particle);

/**
 * @brief Calculate the time until the particle collides with a horizontal wall
 *
 * @param p_particle  a pointer to the particle
 *
 * @post Returns time until collison
 */
 
double t_h_wall_collision(particle* p_particle, int mode);

/**
 * @brief Updates the velocity of a particle after colliding with a vertical wall
 *
 * @param p_particle  a pointer to the particle
 * 
 * @param mode a int that modifies the fonction mode for simulation
 *
 * @post The velocity is updated
 */

void v_v_wall_collision_up(particle* p_particle);

/**
 * @brief Updates the velocity of a particle after colliding with a horizontal wall
 *
 * @param p_particle  a pointer to the particle
 *
 * @post The velocity is updated
 */

void v_h_wall_collision_up(particle* p_particle);

/**
 * @brief Calculate the time until the particles collide
 *
 * @param p_particle1  a pointer to the particle number 1
 * 
 * @param p_particle2  a pointer to the particle number 2
 *
 * @post Returns time until collison
 */

double t_particle_collision(particle* p_particle1,particle* p_particle2);

/**
 * @brief Updates the velocity of the particles after colliding
 *
 * @param p_particle1  a pointer to the particle number 1
 * 
 * @param p_particle2  a pointer to the particle number 2
 * 
 * @param mode a int that offer a diffrent mode in the simulation
 *
 * @post The particle velocities are updated
 */

void v_collision_up(particle* p_particle1,particle* p_particle2, int mode);




#endif
