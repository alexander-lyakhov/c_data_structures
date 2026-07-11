#include <stdio.h>
#include <conio.h>
#include <assert.h>
#include <string.h>
#include <windows.h>

#define LINE puts("----------------------------------------------");

#define VECTOR_DEFAULT_CAPACITY 256
#define VECTOR_CAPACITY_FACTOR 1.5
#define VECTOR_DEBUG

typedef struct {
	short type_size;
	size_t count;
	size_t capacity;

} Vector;

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
	Vector *vector = Vector_check_capacity(Vector_get(*arr)); \
	*arr = (void*)(vector + 1); \
	(*arr)[vector->count++] = value; \
} \


// =============================================================================
// @@@ + Vector_init
// =============================================================================
void* Vector_init(short type_size)
{
	Vector *vector = malloc(sizeof(Vector) + type_size * VECTOR_DEFAULT_CAPACITY);
	vector->count = 0;
	vector->capacity = VECTOR_DEFAULT_CAPACITY;
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
		vector = realloc(vector, sizeof(Vector) + vector->type_size * vector->capacity);
	
		#ifdef VECTOR_DEBUG
			printf("Vector_alloc: 0x%p\n", vector);
		#endif
	}
	return vector;
}

// =============================================================================
// @@@ + Vector_push
// =============================================================================
void Vector_push(int **data, int value)
{
	Vector_push_(data, value);
	
	#ifdef VECTOR_DEBUG
		Vector *vector = Vector_get(*data);
		printf("Vector_push:  0x%p, 0x%p -> %4d, capacity: %4d\n", vector, &(*data)[vector->count - 1], (*data)[vector->count - 1], vector->capacity);
	#endif
}

// =============================================================================
// @@@ + Vector_push_str
// =============================================================================
void Vector_push_str(char ***data, char *value)
{
	Vector_push_(data, value);
	
	#ifdef VECTOR_DEBUG
		Vector *vector = Vector_get(*data);
		printf("Vector_push:  0x%p, 0x%p -> %s, capacity: %4d\n", vector, &(*data)[vector->count - 1], (*data)[vector->count - 1], vector->capacity);
	#endif
}

int main()
{
	system("cls");

	int *arr = Vector_init(sizeof(int));

	Vector_push(&arr, 10);
	Vector_push(&arr, 20);
	Vector_push(&arr, 30);
	Vector_push(&arr, 40);
	Vector_push(&arr, 50);
	Vector_push(&arr, 60);

	Vector_pop(arr);

	if (Vector_size(arr))
		arr[0] = 11;

	/*for (int i = 0; i < 20; i++)
		Vector_push(&arr, i * 10);*/

	puts("");

	for (int i = 0; i < Vector_size(arr); i++)
		printf("data: 0x%p -> %4d, capacity: %4d\n",
			&arr[i],
			arr[i],
			Vector_capacity(arr)
		);

	// Vector_clear(arr);

	if (Vector_size(arr))
	{
		printf("Vector_front: %4d\n", arr[0]);
		printf("Vector_back:  %4d\n", arr[Vector_size(arr) - 1]);
	}

	puts("");

	Vector_destroy(arr);

	char **str = Vector_init(sizeof(char*));

	Vector_push_str(&str, "one");
	Vector_push_str(&str, "two");
	Vector_push_str(&str, "three");
	Vector_push_str(&str, "four");
	Vector_push_str(&str, "five");

	puts("");

	for (int i = 0; i < Vector_size(str); i++)
		printf("data: 0x%p -> %s, capacity: %4d\n",
			&str[i],
			str[i],
			Vector_capacity(str)
		);

	Vector_destroy(str);

	_getch();

	return 0;
}
