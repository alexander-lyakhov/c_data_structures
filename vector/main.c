#include <stdio.h>
#include <conio.h>
#include <assert.h>
// #include <string.h>
#include <windows.h>

#define VECTOR_IMPLEMENTATION
#include "vector_sh.h"

#define LINE puts("----------------------------------------------");

int main()
{
	system("cls");

	char *arr = Vector_init(sizeof(char), 0);

	Vector_push_back_c(&arr, 'a');
	Vector_push_back_c(&arr, 'b');
	Vector_push_back_c(&arr, 'c');
	Vector_push_back_c(&arr, 'd');
	Vector_push_back_c(&arr, 'e');
	Vector_push_back_c(&arr, 'f');

	Vector_pop(arr);

	/*if (Vector_size(arr))
		arr[0] = 11;*/

	/*for (int i = 0; i < 20; i++)
		Vector_push(&arr, i * 10);*/

	puts("");

	for (int i = 0; i < Vector_size(arr); i++)
		printf("data: 0x%p -> %c, capacity: %4zu\n",
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

	char **str = Vector_init(sizeof(char*), 0);

	Vector_push_back_str(&str, "one");
	Vector_push_back_str(&str, "two");
	Vector_push_back_str(&str, "three");
	Vector_push_back_str(&str, "four");
	Vector_push_back_str(&str, "five");

	puts("");

	for (int i = 0; i < Vector_size(str); i++)
		printf("data: 0x%p -> %s, capacity: %4zu\n",
			&str[i],
			str[i],
			Vector_capacity(str)
		);

	Vector_destroy(str);

	_getch();

	return 0;
}
