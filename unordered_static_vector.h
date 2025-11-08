#ifndef UNORDERED_STATIC_VECTOR_H
#define UNORDERED_STATIC_VECTOR_H

#include <stdint.h>

// Modified from ZGB https://github.com/Zal0/ZGB/blob/master/common/include/Vector.h#L15

#define DECLARE_UNORDERED_ST_VECTOR(NAME, NUM_ELEMS) uint8_t NAME[NUM_ELEMS + 1] = {0}

#define unordered_st_vector_get(VECTOR, IDX) VECTOR[IDX + 1]
#define unordered_st_vector_iterate(VECTOR, IDX, ELEM) for(IDX = 0, ELEM = VECTOR[1]; IDX != VECTOR[0]; IDX ++, ELEM = VECTOR[IDX + 1])

void unordered_st_vector_add(uint8_t* v, uint8_t elem);
void unordered_st_vector_remove(uint8_t* v, uint8_t elem);



#endif