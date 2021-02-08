#include <time.h>
#include <stdio.h>
#include <math.h>
#include "particles.h"
#include "simulation1.h"

int main(void) { //Writes a file with particles generated at random
	char file[100];
	printf("File path? (Remember to add data/ before entering the file name) \n");
	scanf("%s", file);
	int particle_nb;
	printf("Nombre de particules: \n");
	scanf("%d", &particle_nb);
	FILE* fp = fopen(file, "w");
	fprintf(fp,"%s\n",file);
	fprintf(fp,"%d\n",particle_nb);
	particle** p_list = create_particles(particle_nb);
	for (int k = 0; k<particle_nb; k++){
		fprintf(fp,"%lf,%lf,%lf,%lf,%lf,%lf\n", (p_list[k]->position[0]),(p_list[k]->position[1]),(p_list[k]->velocity[0]),(p_list[k]->velocity[1]),(p_list[k]->mass),(p_list[k])->radius);
	}
	fclose(fp);
}
		
