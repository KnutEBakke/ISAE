#include "binary-heap.h"
#include <time.h>
#include <stdio.h>
#include <math.h>

int main(void) {
	FILE* fp = fopen("scripts/data_complexity_heap.csv", "w");
	if (fp == NULL) {
		fprintf(stderr, "Cannot write to file fact.txt!\n");
		exit(EXIT_FAILURE);
	}
	heap_event* heap = malloc(sizeof(heap_event));
	*heap = nil_heap();
	int n = 20;
	while (n < 12000000){  //Function that calculates the time of n inserts and n extracts
		clock_t start1 = clock(); //from an event heap
		for (int k = 0.0; k< n;k++){
			event* p_e = malloc(sizeof(event));
			p_e->time = n - k;
			insert(heap, p_e);
			}
		clock_t end1 = clock();
		double elapsed_time1 = ((end1 - start1) / (1.0*CLOCKS_PER_SEC)) ;
		clock_t start2 = clock();
		for (int k = 0; k< n;k++){
			heap_event_node* p_e_node = extract_min(heap);
			free(p_e_node->p_event);
			free(p_e_node);
		}
		clock_t end2 = clock();
		double elapsed_time2 = ((end2 - start2) / (1.0*CLOCKS_PER_SEC)) ;
		fprintf(fp,"%d,%lf,%lf\n" ,n,elapsed_time1,elapsed_time2);
		n = 2 * n;
	}
	fclose(fp);
	free(heap);
	return 0;
}
