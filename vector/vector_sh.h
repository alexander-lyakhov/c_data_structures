/********************************************************************************
	Simple generic Vector implementation for C language.
	STB-style single-header-file width hidden meta-data.
	Inspired by stb_ds.h: https://github.com/nothings/stb/blob/master/stb_ds.h
********************************************************************************

PUBLIC API
	
	Method              Signature                                                 Description
	-----------------------------------------------------------------------------------------------------------------------------
	Vector_init         void* Vector_init(short type_size, size_t _capacity);     Create and init vector
	Vector_get          Vector* Vector_get(T*);                                   Get the pointer to the vector header (metadata)
	Vector_front        T* Vector_front(T*);                                      Get the pointer to the first element of the vector or NULL if the vector is empty
	Vector_back         T* Vector_back(T*);                                       Get the pointer last element of the vector or NULL if the vector is empty
	Vector_size         size_t Vector_size(T*);                                   Get the vector elements count
	Vector_capacity     size_t Vector_capacity(T*);                               Get the vector capacity
	Vector_push_back    void Vector_push_back(T*);                                Append new element to the end of the vector
	Vector_pop_back     void Vector_pop_back(T*);                                 Remove the last element from the vector
	Vector_push         void Vector_push(T*);                                     Alias for 'Vector_push_back'
	Vector_pop          void Vector_pop(T*);                                      Alias for 'Vector_pop_back'
	Vector_clear        void Vector_clear(T*);                                    Clear the vector
	Vector_destroy      void Vector_destroy(T*);                                  Destroy the vector


HOW TO USE

// **************************************************************************************************
//  Primitive data types example
// **************************************************************************************************

	// Create and init vector. 2nd parameter is desired vector capacity. If 0 then capacity set to default value.
	int *arr = Vector_init(sizeof(int), 0);

	// Append elements to the end of the vector
	Vector_push(arr, 10);
	Vector_push(arr, 20);
	Vector_push(arr, 30);
	Vector_push(arr, 40);
	Vector_push(arr, 50);
	Vector_push(arr, 60);

	// Remove last element from the vector
	Vector_pop(arr);

	// Replace specific element (by index) in the vector
	if (Vector_size(arr))
		arr[0] = 11;

	// Iterate through the vector and print it's values
	for (int i = 0; i < Vector_size(arr); i++)
		printf("data: 0x%p -> %d, capacity: %4zu\n",
			&arr[i],
			arr[i],
			Vector_capacity(arr)
		);

	// Clear the vector (make it empty)
	Vector_clear(arr);

	// Check size of the vector and print it's first and last elements
	if (Vector_size(arr))
	{
		printf("Vector_front: %4d\n", arr[0]);
		printf("Vector_back:  %4d\n", arr[Vector_size(arr) - 1]);

		printf("Vector_front: %4d\n", *Vector_front(arr));
		printf("Vector_back:  %4d\n", *Vector_back(arr));
	}

	// Destroy the vector
	Vector_destroy(arr);


// **************************************************************************************************
//  Pointers eexample
// **************************************************************************************************

	typedef struct {
		int x, y;
	} Point;

	Point p1 = {1, 2};
	Point p2 = {3, 4};
	Point p3 = {5, 6};
	Point p4 = {7, 8};

	// Init vector
	Point **p = Vector_init(sizeof(Point), 0);

	// Append elements to the end of the vector
	Vector_push(p, &p1);
	Vector_push(p, &p2);
	Vector_push(p, &p3);

	// Replace specific element (by index) in the vector
	p[0] = &p4;

	// Iterate through the vector and print it's values
	for (int i = 0; i < Vector_size(p); i++)
		printf("data: 0x%p -> x = %d, y = %d, capacity: %4zu\n",
			&p[i],
			p[i]->x,
			p[i]->y,
			Vector_capacity(p)
		);

	// Destroy the vector
	Vector_destroy(p);


// **************************************************************************************************
//  String example (char*)
// **************************************************************************************************

	// Init vector
	char **str = Vector_init(sizeof(char*), 0);

	// Append elements to the end of the vector
	Vector_push(str, "one");
	Vector_push(str, "two");
	Vector_push(str, "three");
	Vector_push(str, "four");
	Vector_push(str, "five");

	// Replace specific element (by index) in the vector
	str[0] = "Hello";

	// Iterate through the vector and print it's values
	for (int i = 0; i < Vector_size(str); i++)
		printf("data: 0x%p -> %-8s, capacity: %4zu\n",
			&str[i],
			str[i],
			Vector_capacity(str)
		);

	// Destroy the vector	
	Vector_destroy(str);
*/
#ifndef _VECTOR_SH_H_
#define _VECTOR_SH_H_

#include "stdio.h"
#include "stdlib.h"

#define VECTOR_DEFAULT_CAPACITY 256
#define VECTOR_CAPACITY_FACTOR 1.5

typedef struct {
	short type_size;
	size_t count;
	size_t capacity;

} Vector;

void* Vector_init(short type_size, size_t _capacity);

#define Vector_get(arr)      (Vector*)(arr) - 1
#define Vector_front(arr)    ((Vector_get(arr))->count ? &((arr)[0]) : NULL)
#define Vector_back(arr)     ((Vector_get(arr))->count ? &((arr)[(Vector_get(arr))->count - 1]) : NULL)
#define Vector_size(arr)     (Vector_get(arr))->count
#define Vector_capacity(arr) (Vector_get(arr))->capacity
#define Vector_clear(arr)    (Vector_get(arr))->count = 0
#define Vector_destroy(arr)  free(Vector_get(arr))

#define Vector_push_back(arr, value) { \
	Vector *vector = (Vector*)Vector_check_capacity(Vector_get(arr)); \
	arr = (void*)(vector + 1); \
	arr[vector->count++] = (value); \
} \

#define Vector_pop_back(arr) { \
	Vector *vector = Vector_get(arr); \
	if (vector->count) vector->count--; \
} \


// Aliases
#define Vector_push Vector_push_back
#define Vector_pop  Vector_pop_back

// #define VECTOR_IMPLEMENTATION // debug
#ifdef VECTOR_IMPLEMENTATION

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
		printf("Vector meta address: 0x%p\n", vector);
		printf("Vector data address: 0x%p\n", vector + 1);
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
			printf("Vector meta address: 0x%p\n", vector);
			printf("Vector data address: 0x%p\n", vector + 1);
		#endif
	}
	return vector;
}

#endif // end of VECTOR_IMPLEMENTATION
#endif
