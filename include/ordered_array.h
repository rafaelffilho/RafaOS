#ifndef ORDERED_ARRAY_H
#define ORDERED_ARRAY_H

#include "common.h"

typedef void *type_t;

typedef int8_t (*lessthan_predicate_t)(type_t, type_t);
struct ordered_array_struct {
	type_t *             array;
	uint32_t             size;
	uint32_t             max_size;
	lessthan_predicate_t less_than;
};
typedef struct ordered_array_struct ordered_array_t;

int8_t standard_lessthan_predicate(type_t, type_t);

ordered_array_t create_ordered_array(uint32_t, lessthan_predicate_t);
ordered_array_t place_ordered_array(void *, uint32_t, lessthan_predicate_t);

void   destroy_ordered_array(ordered_array_t *);
void   insert_ordered_array(type_t, ordered_array_t *);
type_t lookup_ordered_array(uint32_t, ordered_array_t *);
void   remove_ordered_array(uint32_t, ordered_array_t *);

#endif    // !ORDERED_ARRAY_H
