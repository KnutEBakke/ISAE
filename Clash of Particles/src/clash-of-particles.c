#include "simulation1.h"
#include "loader.h"

int main(void){
	int mode;
	printf("Please chose one of the following numbers to launch the corresponding simulation \n 0: Simulate Random Particles (Valgrind Version)\n 1: Simulate Random Particles \n 2: Simulate Newton \n 3: Simulate Disco \n 4: Simulate Billard \n 5: Simulate Gravity \n");
	scanf("%d", &mode);
	if (mode == 0) { //t_max = 10 to allow valgrind to finish the program
		char file[] = "data/random.txt"; 
		int SIZE = 900;
		double refresh_rate = 2;
		double t_max = 1E1;
		 FILE *p_file = fopen(file, "r");
	    if (p_file == NULL) {
	        fprintf(stderr, "Cannot read file %s!\n", file);
	        exit(EXIT_FAILURE);
	    }
	    int particle_nb;
	    char header_buffer[1024];
	    fgets(header_buffer, 1024, p_file);
		fscanf(p_file, "%d\n",&particle_nb);
		fclose(p_file);
		particle** p_list = loader(file);
	    CreateWindow("Valgrind Test", SIZE, SIZE);
	    simulation(t_max, refresh_rate, particle_nb, SIZE, p_list, 0);
	    CloseWindow();
	}
	if (mode == 1) { //Basic function
		char file[] = "data/random.txt";
		int SIZE = 900;
		double refresh_rate = 2;
		double t_max = 1E4;
		 FILE *p_file = fopen(file, "r");
	    if (p_file == NULL) {
	        fprintf(stderr, "Cannot read file %s!\n", file);
	        exit(EXIT_FAILURE);
	    }
	    int particle_nb;
	    char header_buffer[1024];
	    fgets(header_buffer, 1024, p_file);
		fscanf(p_file, "%d\n",&particle_nb);
		fclose(p_file);
		particle** p_list = loader(file);
	    CreateWindow("Random Particles", SIZE, SIZE);
	    simulation(t_max, refresh_rate, particle_nb, SIZE, p_list, mode);
	    CloseWindow();
	}
	if (mode == 2) { //Newton test integrated
		char file[] = "data/newton-simple.txt";
		int SIZE = 900;
		double refresh_rate = 2;
		double t_max = 1E4;
		 FILE *p_file = fopen(file, "r");
	    if (p_file == NULL) {
	        fprintf(stderr, "Cannot read file %s!\n", file);
	        exit(EXIT_FAILURE);
	    }
	    int particle_nb;
	    char header_buffer[1024];
	    fgets(header_buffer, 1024, p_file);
		fscanf(p_file, "%d\n",&particle_nb);
		fclose(p_file);
		particle** p_list = loader(file);
	    CreateWindow("Newton's Crib", SIZE, SIZE);
	    simulation(t_max, refresh_rate, particle_nb, SIZE, p_list, mode);
	    CloseWindow();
	}
	if (mode == 3) { //Disco mode make particles change color on collision
		char file[] = "data/random.txt";
		int SIZE = 900;
		double refresh_rate = 2;
		double t_max = 1E4;
		 FILE *p_file = fopen(file, "r");
	    if (p_file == NULL) {
	        fprintf(stderr, "Cannot read file %s!\n", file);
	        exit(EXIT_FAILURE);
	    }
	    int particle_nb;
	    char header_buffer[1024];
	    fgets(header_buffer, 1024, p_file);
		fscanf(p_file, "%d\n",&particle_nb);
		fclose(p_file);
		particle** p_list = loader(file);
	    CreateWindow("Disco", SIZE, SIZE);
	    simulation(t_max, refresh_rate, particle_nb, SIZE, p_list, mode);
	    CloseWindow();
	}
	if (mode == 4) { //Illustration a queue ball
		char file[] = "data/billard.txt";
		int SIZE = 900;
		double refresh_rate = 2;
		double t_max = 5E3;
		 FILE *p_file = fopen(file, "r");
	    if (p_file == NULL) {
	        fprintf(stderr, "Cannot read file %s!\n", file);
	        exit(EXIT_FAILURE);
	    }
	    int particle_nb;
	    char header_buffer[1024];
	    fgets(header_buffer, 1024, p_file);
		fscanf(p_file, "%d\n",&particle_nb);
		fclose(p_file);
		particle** p_list = loader(file);
	    CreateWindow("Billiard", SIZE, SIZE);
	    simulation(t_max, refresh_rate, particle_nb, SIZE, p_list, mode);
	    CloseWindow();
	}
	if (mode == 5) { // Gravity option added to 100 particles
		char file[] = "data/random-gravity.txt";
		int SIZE = 900;
		double refresh_rate = 0.0002;
		double t_max = 1E1;
		 FILE *p_file = fopen(file, "r");
	    if (p_file == NULL) {
	        fprintf(stderr, "Cannot read file %s!\n", file);
	        exit(EXIT_FAILURE);
	    }
	    int particle_nb;
	    char header_buffer[1024];
	    fgets(header_buffer, 1024, p_file);
		fscanf(p_file, "%d\n",&particle_nb);
		fclose(p_file);
		particle** p_list = loader(file);
	    CreateWindow("Gravity", SIZE, SIZE);
	    simulation(t_max, refresh_rate, particle_nb, SIZE, p_list, mode);
	    CloseWindow();
	}
	
    return 0;
}
