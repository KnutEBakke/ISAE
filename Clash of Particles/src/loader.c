#include <stdio.h>
#include <stdlib.h>
#include "binary-heap.h"
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include "loader.h"

particle** loader(char* file) {//Description in Doxygen 
    FILE *p_file = fopen(file, "r");

    if (p_file == NULL) {
        fprintf(stderr, "Cannot read file %s!\n", file);
        exit(EXIT_FAILURE);
    }
    int particle_nb;
    char header_buffer[1024];
    fgets(header_buffer, 1024, p_file);
    int fscanf_result;
	fscanf_result = fscanf(p_file, "%d\n",&particle_nb);
	particle** p_list = malloc(particle_nb*sizeof(particle*));
	for (int i = 0; i< particle_nb; i++){
		assert(fscanf_result != EOF);
		particle* p_particle = nil_particle();
		fscanf_result = fscanf(p_file,"%lf,%lf,%lf,%lf,%lf,%lf\n" ,&(p_particle->position)[0],&(p_particle->position)[1],&(p_particle->velocity)[0],&(p_particle->velocity)[1],&p_particle->mass,&p_particle->radius);
		p_particle->collision_nb = 0;
		p_particle->color = 1 + rand() % 7;
		p_list[i] = p_particle;
	}
    fclose(p_file);

    p_file = NULL;

    return p_list;
}

