#include "loader.h"
#include "particles.h"
#include "simulation1.h"

int main(void){
	//char file[10];
	//scanf("%s", file);
	particle** p_list = loader("data/one-particle-simple.txt");
	for (int k = 0; k < 1; k++) {
		print_particle(p_list[k]);
	}
	deallocate_list(p_list, 1);
}
	

