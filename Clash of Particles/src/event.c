#include "event.h"
#include <assert.h>


bool refreshing_event(event* p_e) {
	
	return ((p_e->p_particle_a == NULL) && (p_e->p_particle_b == NULL));
	
}

bool vertical_event(event* p_e) {
	return ((p_e->p_particle_a == NULL) && (p_e->p_particle_b != NULL));
}

bool horizontal_event(event* p_e) {
	return ((p_e->p_particle_a != NULL) && (p_e->p_particle_b == NULL));
}

bool collision_event(event* p_e) {
	return ((p_e->p_particle_a != NULL) && (p_e->p_particle_b != NULL));
}

event * create_event(double temps, particle* p_a, particle* p_b, int nb_a, int nb_b){
	event* p_e = malloc(sizeof(event));
	p_e->time = temps;
	p_e->p_particle_a = p_a;
	p_e->p_particle_b = p_b;
	p_e->collision_nb_a = nb_a;
	p_e->collision_nb_b = nb_b;
	return p_e;
}


bool is_valid(event* e) { //As defined in the subject
	assert(e->time < INFINITY);
	if (e->p_particle_a != NULL) {
		if (e->p_particle_b != NULL) {
			return (e->collision_nb_a == (e->p_particle_a)->collision_nb && e->collision_nb_b == (e->p_particle_b)->collision_nb);
		}
		else {
			return (e->collision_nb_a == (e->p_particle_a)->collision_nb);
		}
	}
	else {
		if (e->p_particle_b != NULL) {
			return (e->collision_nb_b == (e->p_particle_b)->collision_nb);
		}
		else {
			return true; //All refresh events are valid
		}
	}
}
