#ifndef _VECTOR_SH_H_
#define _VECTOR_SH_H_

#include "stdio.h"
#include "stdlib.h"

#define VECTOR_DEFAULT_CAPACITY 256
#define VECTOR_CAPACITY_FACTOR 1.5
#define VECTOR_DEBUG

typedef struct {
	short type_size;
	size_t count;
	size_t capacity;

} Vector;

// #define VECTOR_IMPLEMENTATION // debug

#ifdef VECTOR_IMPLEMENTATION

#define Vector_get(arr)      (Vector*)(arr) - 1
#define Vector_size(arr)     (Vector_get(arr))->count
#define Vector_capacity(arr) (Vector_get(arr))->capacity
#define Vector_clear(arr)    (Vector_get(arr))->count = 0
#define Vector_destroy(arr)  free(Vector_get(arr))

#define Vector_pop(arr) { \
	Vector *vector = Vector_get(arr); \
	if (vector->count) vector->count--; \
} \

#define Vector_push_(arr, value) { \
	Vector *vector = (Vector*)Vector_check_capacity(Vector_get(*arr)); \
	*arr = (void*)(vector + 1); \
	(*arr)[vector->count++] = value; \
} \

void* Vector_init(short type_size, size_t _capacity);
void  Vector_pushi(int **data, int value);
void  Vector_pushstr(char ***data, char *value);

#define Vector_push_backc   Vector_push_back_c
#define Vector_push_backs   Vector_push_back_s
#define Vector_push_backi   Vector_push_back_i
#define Vector_push_backl   Vector_push_back_l
#define Vector_push_backll  Vector_push_back_ll
#define Vector_push_backf   Vector_push_back_f
#define Vector_push_backd   Vector_push_back_d
#define Vector_push_backld  Vector_push_back_ld
#define Vector_push_backstr Vector_push_back_str
#define Vector_push_backptr Vector_push_back_ptr

// =============================================================================
// @@@ + Vector_init
// =============================================================================
void* Vector_init(short type_size, size_t _capacity)
{
	size_t capacity = _capacity ? _capacity : VECTOR_DEFAULT_CAPACITY;

	Vector *vector = (Vector*)malloc(sizeof(Vector) + type_size * capacity);
	vector->capacity = capacity;
	vector->count = 0;
	vector->type_size = type_size;

	#ifdef VECTOR_DEBUG
		printf("Vector_alloc: 0x%p\n", vector);
	#endif

	return vector + 1;
}

// =============================================================================
// @@@ + Vector_check_capacity
// =============================================================================
static void* Vector_check_capacity(Vector *vector)
{
	if (vector->count >= vector->capacity)
	{
		vector->capacity *= VECTOR_CAPACITY_FACTOR;
		vector = (Vector*)realloc(vector, sizeof(Vector) + vector->type_size * vector->capacity);
	
		#ifdef VECTOR_DEBUG
			printf("Vector_alloc: 0x%p\n", vector);
		#endif
	}
	return vector;
}

// =============================================================================
// @@@ + Vector_push_backc
// =============================================================================
void Vector_push_backc(char **data, char value)
{
	Vector_push_(data, value);
	
	#ifdef VECTOR_DEBUG
		Vector *vector = Vector_get(*data);
		printf("Vector_push_backc:  0x%p, 0x%p -> %c, capacity: %4zu\n", vector, &(*data)[vector->count - 1], (*data)[vector->count - 1], vector->capacity);
	#endif
}

// =============================================================================
// @@@ + Vector_push_backs
// =============================================================================
void Vector_push_backs(short **data, short value)
{
	Vector_push_(data, value);
	
	#ifdef VECTOR_DEBUG
		Vector *vector = Vector_get(*data);
		printf("Vector_push_backs:  0x%p, 0x%p -> %4d, capacity: %4zu\n", vector, &(*data)[vector->count - 1], (*data)[vector->count - 1], vector->capacity);
	#endif
}

// =============================================================================
// @@@ + Vector_pushi
// =============================================================================
void Vector_push_backi(int **data, int value)
{
	Vector_push_(data, value);
	
	#ifdef VECTOR_DEBUG
		Vector *vector = Vector_get(*data);
		printf("Vector_push_backi:  0x%p, 0x%p -> %4d, capacity: %4zu\n", vector, &(*data)[vector->count - 1], (*data)[vector->count - 1], vector->capacity);
	#endif
}

// =============================================================================
// @@@ + Vector_push_backl
// =============================================================================
void Vector_push_backl(long **data, long value)
{
	Vector_push_(data, value);
	
	#ifdef VECTOR_DEBUG
		Vector *vector = Vector_get(*data);
		printf("Vector_push_backl:  0x%p, 0x%p -> %l, capacity: %4zu\n", vector, &(*data)[vector->count - 1], (*data)[vector->count - 1], vector->capacity);
	#endif
}

// =============================================================================
// @@@ + Vector_pushstr
// =============================================================================
void Vector_push_backstr(char ***data, char *value)
{
	Vector_push_(data, value);
	
	#ifdef VECTOR_DEBUG
		Vector *vector = Vector_get(*data);
		printf("Vector_push_backstr:  0x%p, 0x%p -> %s, capacity: %4zu\n", vector, &(*data)[vector->count - 1], (*data)[vector->count - 1], vector->capacity);
	#endif
}

#endif // end of VECTOR_IMPLEMENTATION
#endif
