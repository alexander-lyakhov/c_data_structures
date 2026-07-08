#ifndef VECTOR_H_
#define VECTOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_VECTOR_CAPACITY 256

#define Vector_append(vector, value)                                                \
{                                                                                   \
	Vector_check_capacity(vector);                                                  \
	void *target = (char*)(vector)->data + (vector)->count * (vector)->type_size;   \
	memcpy(target, &(value), (vector)->type_size);                                  \
	(vector)->count++;                                                              \
}                                                                                   \

#define Vector_size(vector) (vector)->count
#define Vector_data(vector) (vector)->data

typedef struct {
	void *data;
	size_t capacity;
	size_t count;
	short type_size;

} Vector;

static void Vector_check_capacity(Vector *vector);
Vector* Vector_init(Vector *vector, short type_size, size_t capacity);
void    Vector_push_backc(Vector *vector, char value);
void    Vector_push_backs(Vector *vector, short value);
void    Vector_push_backi(Vector *vector, int value);
void    Vector_push_backl(Vector *vector, long value);
void    Vector_push_backll(Vector *vector, long long value);
void    Vector_push_backf(Vector *vector, float value);
void    Vector_push_backd(Vector *vector, double value);
void    Vector_push_backld(Vector *vector, long double value);
void    Vector_push_backstr(Vector *vector, char* value);
void    Vector_pop_back(Vector *vector);
void*   Vector_front(Vector *vector);
void*   Vector_back(Vector *vector);
void    Vector_clear(Vector *vector);
void    Vector_destroy(Vector *vector);

#define Vector_push_backc   Vector_push_back_c
#define Vector_push_backs   Vector_push_back_s
#define Vector_push_backi   Vector_push_back_i
#define Vector_push_backl   Vector_push_back_l
#define Vector_push_backll  Vector_push_back_ll
#define Vector_push_backf   Vector_push_back_f
#define Vector_push_backd   Vector_push_back_d
#define Vector_push_backld  Vector_push_back_ld
#define Vector_push_backstr Vector_push_back_str

// #define VECTOR_IMPLEMENTATION

#ifdef VECTOR_IMPLEMENTATION
// =============================================================================
// @@@ + Vector_init
// =============================================================================
Vector* Vector_init(Vector *vector, short type_size, size_t capacity)
{
	printf("Vector_init. Type size: %d\n", type_size);

	vector->data = malloc(type_size * DEFAULT_VECTOR_CAPACITY);
	vector->capacity = capacity ? capacity : DEFAULT_VECTOR_CAPACITY;
	vector->count = 0;
	vector->type_size = type_size;

	return vector;
}

// =============================================================================
// @@@ - Vector_check_capacity
// =============================================================================
static void Vector_check_capacity(Vector *vector)
{
	if (vector->count >= vector->capacity)
	{
		vector->capacity *= 1.5;
		vector->data = realloc(vector->data, vector->capacity * vector->type_size);
	}
}

// =============================================================================
// @@@ + Vector_push_backc
// =============================================================================
void Vector_push_backc(Vector *vector, char value)
{
	Vector_append(vector, value);

	#ifdef VECTOR_DEBUG
		printf("Vector_push_backc: %c, %d\n", value, vector->capacity);
	#endif
}

// =============================================================================
// @@@ + Vector_push_backs
// =============================================================================
void Vector_push_backs(Vector *vector, short value)
{
	Vector_append(vector, value);

	#ifdef VECTOR_DEBUG
		printf("Vector_push_backs: %d, %d\n", value, vector->capacity);
	#endif
}

// =============================================================================
// @@@ + Vector_push_backi
// =============================================================================
void Vector_push_backi(Vector *vector, int value)
{
	Vector_append(vector, value);

	#ifdef VECTOR_DEBUG
		printf("Vector_push_backi: %d, %d\n", value, vector->capacity);
	#endif
}

// =============================================================================
// @@@ + Vector_push_backl
// =============================================================================
void Vector_push_backl(Vector *vector, long value)
{
	Vector_append(vector, value);

	#ifdef VECTOR_DEBUG
		printf("Vector_push_backl: %l, %d\n", value, vector->capacity);
	#endif
}

// =============================================================================
// @@@ + Vector_push_backll
// =============================================================================
void Vector_push_backll(Vector *vector, long long value)
{
	Vector_append(vector, value);

	#ifdef VECTOR_DEBUG
		printf("Vector_push_backll: %ll, %d\n", value, vector->capacity);
	#endif
}

// =============================================================================
// @@@ + Vector_push_backf
// =============================================================================
void Vector_push_backf(Vector *vector, float value)
{
	Vector_append(vector, value);

	#ifdef VECTOR_DEBUG
		printf("Vector_push_backf: %.3f, %d\n", value, vector->capacity);
	#endif
}

// =============================================================================
// @@@ + Vector_push_backd
// =============================================================================
void Vector_push_backd(Vector *vector, double value)
{
	Vector_append(vector, value);

	#ifdef VECTOR_DEBUG
		printf("Vector_push_backd: %.3f, %d\n", value, vector->type_size);
	#endif
}

// =============================================================================
// @@@ + Vector_push_backld
// =============================================================================
void Vector_push_backld(Vector *vector, long double value)
{
	Vector_append(vector, value);

	#ifdef VECTOR_DEBUG
		printf("Vector_push_backld: %.3Lf, %d\n", value, vector->type_size);
	#endif
}

// =============================================================================
// @@@ + Vector_push_backstr
// =============================================================================
void Vector_push_backstr(Vector *vector, char* value)
{
	Vector_append(vector, value);

	#ifdef VECTOR_DEBUG
		printf("Vector_push_backstr: %s, %d\n", value, vector->capacity);
	#endif
}

// =============================================================================
// @@@ + Vector_pop_back
// =============================================================================
void Vector_pop_back(Vector *vector)
{
	if (vector->count)
		vector->count--;
}

// =============================================================================
// @@@ + Vector_front
// =============================================================================
void* Vector_front(Vector *vector)
{
	return vector->count
		? (char*)vector->data
		: NULL;
}

// =============================================================================
// @@@ + Vector_back
// =============================================================================
void* Vector_back(Vector *vector)
{
	return vector->count
		? (char*)vector->data + (vector->count - 1) * vector->type_size
		: NULL;
}

// =============================================================================
// @@@ + clear
// =============================================================================
void Vector_clear(Vector *vector)
{
	vector->count = 0;
}

// =============================================================================
// @@@ + Vector_destroy
// =============================================================================
void Vector_destroy(Vector *vector)
{
	free(vector->data);

	vector->data      = NULL;
	vector->capacity  = 0;
	vector->count     = 0;
	vector->type_size = 0;
}

#endif // end of VECTOR_IMPLEMENTATION
#endif
