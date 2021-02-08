#include "binary-heap.h"
#include <assert.h>
#include <math.h>

int main(void) {
	heap_event* p_heap = malloc(sizeof(heap_event));
	*p_heap = nil_heap();
	for (int i = 0; i<50;i++){
		event* p_e = malloc(sizeof(event));
		p_e->time = (double) (rand() % 10); //Random numbers are best suited for testing the functions
		insert(p_heap, p_e);
	}
	double last_t = 0.0;
	for (int i = 0; i<50;i++){
		heap_event_node* p_e_node = extract_min(p_heap);
		printf(" %lf \n", (p_e_node->p_event)->time); //Visual proof
		assert(p_e_node->p_event->time >= last_t); //Machine proof
		last_t = p_e_node->p_event->time;
		free(p_e_node->p_event);
		free(p_e_node);
	}	
	free(p_heap);
	return 0;
}
