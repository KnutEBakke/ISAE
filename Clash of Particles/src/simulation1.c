#include "simulation1.h"
#include "particles.h"	
#include "libs.h"
#include <time.h>
#include "binary-heap.h"
#include "event.h"


void draw_particles(int particle_nb, particle** p_list, int SIZE){ //Adapted function from the snow.c file
    EmptySpace();
    for (int i=0; i<particle_nb; i++){
        DrawDISC(SIZE*((p_list[i])->position)[0], SIZE*((p_list[i])->position)[1], SIZE*(p_list[i])->radius, (p_list[i])->color );
	}
    UpdateScreen();
}   


particle** create_particles(int particle_nb) { 
	srand(time(NULL));
	particle** p_list = malloc(particle_nb*sizeof(particle*));
	for(int k = 0; k<particle_nb; k++) {
		particle* p_particle = nil_particle();
		(p_particle->velocity)[0] = (rand() * 10.0  - RAND_MAX*5.0)/(RAND_MAX*10000.0);
		(p_particle->velocity)[1] = (rand() * 10.0  - RAND_MAX*5.0)/(RAND_MAX*10000.0);
		p_particle->radius = (0.004 + (rand() * 7.6)/(RAND_MAX*1000.0));
		p_particle->mass = 0.4 + (rand() * 4.0)/(RAND_MAX*10.0);
		(p_particle->position)[0] = (rand()) /(RAND_MAX*1.0);
		(p_particle->position)[1] = (rand()*1.0) /(RAND_MAX*1.0);
		p_particle->color = 1 + rand()%7;
		p_particle->collision_nb = 0;
		p_list[k] = p_particle;
	}
	return p_list;
}

void deallocate_list(particle** p_list, int particle_nb) {
	for (int k = 0; k < particle_nb; k++){
		deallocate_particle(p_list[k]);
	}
	free(p_list);
}
 

void list_pos_up(particle ** p_list, int particle_nb, double t, int mode) {
	for (int k = 0; k<particle_nb; k++){
		pos_up(p_list[k], t, mode);
	}
}
void add_v_collision(particle* p_particle, double t_event, heap_event* Q, double t_max) {
	double t = t_event + t_v_wall_collision(p_particle);
	if (t < t_max) {
		insert(Q, create_event(t, NULL, p_particle, 0,p_particle->collision_nb));
	}
}
void add_h_collision(particle* p_particle, double t_event, heap_event* Q, double t_max, int mode) {
	double t = t_event + t_h_wall_collision(p_particle, mode);
	if (t < t_max) {
		insert(Q, create_event(t,p_particle,NULL,p_particle->collision_nb,0));
	}
}


void add_collisions(particle* p_particle, double t_event, particle** p_list, heap_event* Q, double t_max, int start, int finish, int mode) {
	add_v_collision(p_particle, t_event, Q, t_max);
	add_h_collision(p_particle, t_event, Q, t_max, mode);
	double t;
	for (int i = start; i<finish;i++){
		if (p_particle != p_list[i]){
			t = t_event + t_particle_collision(p_particle, p_list[i]);
		}
		else {
			t = INFINITY;
		}
		if (t < t_max){
			insert(Q, create_event(t, p_particle, p_list[i], p_particle->collision_nb,p_list[i]->collision_nb));
		}
	}
}


void simulation(double t_max,double refresh_rate, int particle_nb, int SIZE, particle ** p_list, int mode) {
	heap_event *Q = malloc(sizeof(heap_event));
	*Q = nil_heap();
	double old_t= 0.0; //As defined in the subject
	for(int k = 0; k < particle_nb; k++){
		particle * p_particle = p_list[k];
		add_collisions(p_particle, 0, p_list, Q, t_max, k+1, particle_nb, mode);
	}
	insert(Q, create_event(0,NULL,NULL,0,0));
	while( is_not_empty(Q)) {
		 heap_event_node* p_node = extract_min(Q);
		 event* p_e = p_node->p_event;
		 free(p_node);
		 if (is_valid(p_e)) {
			 list_pos_up(p_list, particle_nb, p_e->time - old_t, mode);
			 if (refreshing_event(p_e)){
				draw_particles(particle_nb, p_list,SIZE);
				if (p_e->time + refresh_rate < t_max){
					insert(Q, create_event((p_e->time + refresh_rate), NULL, NULL, 0, 0));
				}
			 }
			 if (vertical_event(p_e)){
				 v_v_wall_collision_up(p_e->p_particle_b);
				 add_collisions(p_e->p_particle_b,p_e->time, p_list, Q, t_max, 0, particle_nb,mode);
			 }
			 if (horizontal_event(p_e)){
				 v_h_wall_collision_up(p_e->p_particle_a);
				 add_collisions(p_e->p_particle_a,p_e->time, p_list, Q, t_max, 0, particle_nb, mode);
			 }
			 if (collision_event(p_e)){
				 v_collision_up(p_e->p_particle_a, p_e->p_particle_b, mode);
				 add_collisions(p_e->p_particle_a,p_e->time, p_list, Q, t_max, 0, particle_nb, mode);
				 add_collisions(p_e->p_particle_b, p_e->time, p_list, Q, t_max,0,particle_nb, mode);				 
			 }
			 old_t = p_e->time;
		 }
		 free(p_e);
	 }
	 free(Q);
	 deallocate_list(p_list, particle_nb);
}
