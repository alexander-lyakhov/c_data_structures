#include <stdio.h>
#include <conio.h>
#include <assert.h>
// #include <string.h>
#include <windows.h>

#define VECTOR_IMPLEMENTATION
#define VECTOR_DEBUG
#include "vector_sh.h"

#define LINE puts("----------------------------------------------");

int main()
{
	system("cls");

	int *arr = Vector_init(sizeof(int), 0);

	Vector_push(arr, 10);
	Vector_push(arr, 20);
	Vector_push(arr, 30);
	Vector_push(arr, 40);
	Vector_push(arr, 50);
	Vector_push(arr, 60);

	Vector_pop(arr);

	if (Vector_size(arr))
		arr[0] = 11;

	/*for (int i = 0; i < 20; i++)
		Vector_push(&arr, i * 10);*/

	puts("");

	for (int i = 0; i < Vector_size(arr); i++)
		printf("data: 0x%p -> %d, capacity: %4zu\n",
			&arr[i],
			arr[i],
			Vector_capacity(arr)
		);

	Vector_clear(arr);

	if (Vector_size(arr))
	{
		printf("Vector_front: %4d\n", arr[0]);
		printf("Vector_back:  %4d\n", arr[Vector_size(arr) - 1]);
	}
	Vector_destroy(arr);

	// ==========================================================

	puts("");

	char **str = Vector_init(sizeof(char*), 0);

	Vector_push(str, "one");
	Vector_push(str, "two");
	Vector_push(str, "three");
	Vector_push(str, "four");
	Vector_push(str, "five");

	str[0] = "Hello";

	puts("");

	for (int i = 0; i < Vector_size(str); i++)
		printf("data: 0x%p -> %-8s, capacity: %4zu\n",
			&str[i],
			str[i],
			Vector_capacity(str)
		);

	Vector_destroy(str);

	// ==========================================================

	puts("");

	typedef struct {
		int x, y;
	} Point;

	Point p1 = {1, 2};
	Point p2 = {3, 4};
	Point p3 = {5, 6};
	Point p4 = {7, 8};

	Point **p = Vector_init(sizeof(Point), 2);

	Vector_push(p, &p1);
	Vector_push(p, &p2);
	Vector_push(p, &p3);

	p[0] = &p4;

	puts("");

	for (int i = 0; i < Vector_size(p); i++)
		printf("data: 0x%p -> x = %u, y = %u, capacity: %4zu\n",
			&p[i],
			p[i]->x,
			p[i]->y,
			Vector_capacity(p)
		);

	Vector_destroy(p);

	_getch();

	return 0;
}
