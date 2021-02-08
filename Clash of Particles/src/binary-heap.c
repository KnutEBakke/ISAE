#include "binary-heap.h"
#include "libs.h"
#include <assert.h>

//As seen in class, only difference is that the heaps now carry event
//instead of int values, and therefore compares the times of the events

// auxiliary functions
void print_level(heap_event_node *p_node, int level) {
    for (int i = 0; i < level - 1; i++) {
        printf("   ");
    }

    if (p_node == NULL) {
        printf("%snil\n", level == 0 ? "" : " +-");
        return;
    }

    printf("%s(%lf)\n", level == 0 ? "" : " +-", (p_node->p_event)->time);
    print_level(p_node->left, level + 1);
    print_level(p_node->right, level + 1);
}

bool is_not_empty(heap_event *p_heap) {
	if (is_empty(p_heap)){
		return false;
	}
	else {
		return true;
	}
}

// gives a pointer to the heap node pointer representing the father
// of node number n in the heap


heap_event_node* go_to_father_node(heap_event *p_heap, int n) {
    int carray[8*sizeof(int)+1];
	int i = 0;
    while (n >0) {
		carray[i] = (n & 1) == 1 ? 1 : 0;
		i++;
		n = n>>1;
	}
    heap_event_node *p_node = p_heap->root;
    for (int k = i-2; k > 0; k--) {
		if (carray[k]) {
			p_node = p_node->right;
		}
		else {
			p_node = p_node->left;
		}
	}
	return p_node;
}


heap_event nil_heap(void) {
	heap_event heap;
	heap.size = 0;
	heap.root = NULL;
	return heap;
}

heap_event_node* nil_node() {
	heap_event_node* node = malloc(sizeof(heap_event_node));
	return node;
}

bool is_empty(heap_event *p_heap){
	return ((p_heap->size) == 0);
}



void insert(heap_event *p, event* p_e) {
	int size = p->size;
	heap_event_node * p_f_node = nil_node();
	p_f_node->p_event = p_e;
	p_f_node->left = NULL;
	p_f_node->right = NULL;
	p_f_node->father = NULL;
	
	if (size==0) {
		p->root = p_f_node;
		p->size = size +1;
	}
	else {	
		heap_event_node * p_pere_node = go_to_father_node(p,size+1);
		if (p_pere_node->left == NULL) {
			p_pere_node->left = p_f_node;
		}
		else {
			p_pere_node->right = p_f_node;
		}
		p_f_node->father = p_pere_node;
		while (p_f_node->father->p_event->time > p_e->time) {
			p_f_node->p_event = (p_f_node->father)->p_event;
			(p_f_node->father)->p_event = p_e;
			if (p_f_node->father == p->root) {
				break;
			}
			p_f_node = p_f_node->father;
		}
	p->size = size +1;
	}
}
	
	
	
heap_event_node* extract_min(heap_event *p_heap) {
	//assert(p_heap->size == 0);
	
	heap_event_node* p_e_node = p_heap->root;
	if (p_heap->size ==1) {
		p_heap->size = 0;
		p_heap->root = NULL;
		return p_e_node;
		
	}
	heap_event_node* p_pere = go_to_father_node(p_heap, p_heap->size);
	heap_event_node* p_dernier;
	if (p_pere->right == NULL) {
		p_dernier = p_pere->left;
		p_pere->left = NULL;
	}
	else {
		p_dernier = p_pere->right;
		p_pere->right= NULL;
	}
	p_heap->root=p_dernier;
	p_dernier->father =NULL;
	if(p_e_node->left != NULL) { 
		p_e_node->left->father = p_dernier;
	}
	if(p_e_node->right != NULL) { 
		p_e_node->right->father = p_dernier;
	}
	p_dernier->left = p_e_node->left;
	p_dernier->right = p_e_node->right;
	heap_event_node* p_left = p_dernier->left;
	heap_event_node* p_right = p_dernier->right;
	event* aux = p_dernier->p_event;
	while (p_right != NULL || p_left != NULL)  {
		if (p_right !=NULL) {
			if (((p_right->p_event)->time < (p_left->p_event)->time) && ((p_right->p_event)->time < aux->time) ) {
				p_dernier->p_event = p_right->p_event;
				p_right->p_event = aux;
				p_left = p_right->left;
				p_right = p_right->right;
				p_dernier = p_dernier->right;
			}
			else { if (aux->time > (p_left->p_event)->time) {
					p_dernier->p_event = p_left->p_event;
					p_left->p_event = aux;
					p_right = p_left->right;
					p_left = p_left->left;
					p_dernier = p_dernier->left;
				}
				else {
					break;
				}
			}
		}
		else {if (aux->time > (p_left->p_event)->time) {
				p_dernier->p_event = p_left->p_event;
				p_left->p_event = aux;
				p_right = p_left->right;
				p_left = p_left->left;
				p_dernier = p_dernier->left;
			}
			else {
				break;
			}
		}
	}
	p_heap->size = p_heap->size -1;
	return p_e_node;
}

void print_heap(heap_event *p_heap) {
	print_level(p_heap->root, 0);
}

void deallocate_heap(heap_event* p_heap) {
	heap_event_node* aux;
	for (int k = p_heap->size; k > 1; k = k - 2) {
		aux = go_to_father_node(p_heap, k);
		free((aux->right)->p_event);
		free((aux->right)->p_event);
		free(aux->right);
		free(aux->left);
	}
	free(p_heap->root);
}

	
