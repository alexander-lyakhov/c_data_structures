/*
-----------------------------------------------------------------
STB-style single-header-file Vector implementation for C language
The std::vector from the STL library was used as a reference.
-----------------------------------------------------------------

HOW TO USE

// **************************************************************************************************
//  Primitive data types example
// **************************************************************************************************

	// Create Vector instance
	Vector ints;

	// Init vector. 3-d parameter is desired vector capacity. If 0 then capacity set to default value.
	Vector_init(&ints, sizeof(int), 0);

	// Add elements to vector
	Vector_push_back_i(&ints, 10);
	Vector_push_back_i(&ints, 20);
	Vector_push_back_i(&ints, 30);
	Vector_push_back_i(&ints, 40);
	Vector_push_back_i(&ints, 50);

	// Get first and last elements of vector
	int *first = Vector_front(&ints);
	int *last  = Vector_back(&ints);

	// Remove last elemet from vector
	Vector_pop_back(&ints);

	// Change vector element value
	size_t index = 0;
	((int*)ints.data)[index] = 333;

	// Iterate vector
	int *data = ints.data;

	for (int i = 0; i < Vector_size(&ints); i++) {
		printf("data: %4d\n", data[i]);
	}

	// Clear vector
	Vector_clear(&ints);

	// Destroy vector
	Vector_destroy(&ints);


// **************************************************************************************************
//  Pointers eexample
// **************************************************************************************************

	typedef struct { int x, y; } Point;

	// Create Vector instance
	Vector ptrs;

	// Init vector. 3-d parameter is desired vector capacity. If 0 then capacity set to default value.
	Vector_init(&ptrs, sizeof(void*), 0);

	// Add elements to vector
	Point p1 = {1, 2};
	Point p2 = {3, 4};

	Vector_push_back_ptr(&ptrs, &p1);
	Vector_push_back_ptr(&ptrs, &p2);
	Vector_push_back_ptr(&ptrs, &(Point){5, 6});
	Vector_push_back_ptr(&ptrs, &(Point){7, 8});

	// Remove last elemet from vector
	Vector_pop_back(&ptrs);

	// Change vector element value
	size_t index = 0;
	((Point**)ptrs.data)[index] = &((Point){12, 24});

	// Iterate vector
	Point **pdata = ptrs.data;

	for (int i = 0; i < Vector_size(&ptrs); i++) {
		printf("data: 0x%p, x = %d, y = %d\n",
			pdata[i],
			pdata[i]->x,
			pdata[i]->y
		);
	}

	// Clear vector
	Vector_clear(&ptrs);

	// Destroy vector
	Vector_destroy(&ptrs);


// **************************************************************************************************
//  String example (char*)
// **************************************************************************************************

	// Create Vector instance
	Vector vstr;

	// Init vector. 3-d parameter is desired vector capacity. If 0 then capacity set to default value.
	Vector_init(&vstr, sizeof(char*), 0);

	// Add elements to vector
	Vector_push_back_ptr(&vstr, "one");
	Vector_push_back_ptr(&vstr, "two");
	Vector_push_back_ptr(&vstr, "three");
	Vector_push_back_ptr(&vstr, "four");

	// Remove last elemet from vector
	Vector_pop_back(&vstr);

	// Change vector element value
	size_t index = 0;
	((char**)vstr.data)[0] = "one and half";

	// Iterate vector
	char **data = vstr.data;

	for (int i = 0; i < Vector_size(&vstr); i++) {
		printf("data: 0x%p, %s\n", data[i], data[i]);
	}

	// Clear vector
	Vector_clear(&vstr);

	// Destroy vector
	Vector_destroy(&vstr);

************************************************************************************/

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
void    Vector_push_backptr(Vector *vector, void* value);
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
#define Vector_push_backptr Vector_push_back_ptr

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
// @@@ + Vector_push_backptr
// =============================================================================
void Vector_push_backptr(Vector *vector, void* value)
{
	Vector_append(vector, value);

	#ifdef VECTOR_DEBUG
		printf("Vector_push_backptr: %p, %d\n", value, vector->capacity);
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
