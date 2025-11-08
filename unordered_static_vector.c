#include "unordered_static_vector.h"

#include <string.h>

void unordered_st_vector_add(uint8_t* v, uint8_t elem) {
	v[++ v[0]] = elem;
}

void unordered_st_vector_remove(uint8_t* v, uint8_t elem) {
    // Replace the element at pos with the last element
	uint8_t pos = 0;
	for(pos = 1; pos <= v[0]; pos++){
		if(v[pos] == elem){
			break;
		}
	}
	v[pos] = v[v[0]];
	v[0] --;
}