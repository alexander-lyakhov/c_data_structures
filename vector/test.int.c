#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

#define VECTOR_DEBUG
#define VECTOR_IMPLEMENTATION
#include "vector.h"

#define LINE(size) for (int i = 0; i < (size) + 6; i++) printf("-"); puts("");

typedef struct {
	int x;
	int y;

} Point;

void title(const char *text)
{
	int len = strlen(text);

	puts("");

	LINE(len);
		printf(">> %s <<\n", text);
	LINE(len);
}

int main()
{
	system("cls");

	Vector ints;
	Vector_init(&ints, sizeof(int), 0);

	// *******************************************
	title("Vector setup");
	// *******************************************

	Vector_push_back_i(&ints, -10);
	Vector_push_back_i(&ints, -20);
	Vector_push_back_i(&ints, -30);
	Vector_push_back_i(&ints,  40);
	Vector_push_back_i(&ints,  50);

	// *******************************************
	title("Get first and last element");
	// *******************************************

	int *first = Vector_front(&ints);
	int *last  = Vector_back(&ints);

	printf("Vector first value: %d\n", *first);
	printf("Vector last value: %d\n", *last);

	title("Remove last elemet and replace it with new one");

	Vector_pop_back(&ints);
	Vector_push_back_i(&ints, 100);

	// *******************************************
	title("Remove all elements and add new");
	// *******************************************

	Vector_pop_back(&ints);
	Vector_pop_back(&ints);
	Vector_pop_back(&ints);
	Vector_pop_back(&ints);
	Vector_pop_back(&ints);
	Vector_pop_back(&ints);
	Vector_pop_back(&ints);
	Vector_pop_back(&ints);

	Vector_push_back_i(&ints, 11);
	Vector_push_back_i(&ints, 22);
	Vector_push_back_i(&ints, 33);
	Vector_push_back_i(&ints, 44);
	Vector_push_back_i(&ints, 55);
	Vector_push_back_i(&ints, 55);
	Vector_push_back_i(&ints, 66);
	Vector_push_back_i(&ints, 77);

	// *******************************************
	title("Iterate vector");
	// *******************************************

	int *data = ints.data;

	for (int i = 0; i < Vector_size(&ints); i++) {
		printf("data: %4d\n", data[i]);
	}

	// *******************************************
	title("Clear vector");
	// *******************************************
	Vector_clear(&ints);

	// *******************************************
	title("Iterate vector");
	// *******************************************
	
	data = ints.data;

	for (int i = 0; i < Vector_size(&ints); i++) {
		printf("data: %4d\n", data[i]);
	}

	first = Vector_front(&ints);
	last  = Vector_back(&ints);

	Vector_push_back_i(&ints, 99);


	if (first)
		printf("Vector first value: %d\n", *first);

	if (last)
		printf("Vector last value: %d\n", *last);

	((int*)ints.data)[0] = 333;

	data = ints.data;

	for (int i = 0; i < Vector_size(&ints); i++) {
		printf("data: %4d\n", data[i]);
	}

	Vector_destroy(&ints);

	// *******************************************
	title("Init ptrs");
	// *******************************************

	Vector ptrs;
	Vector_init(&ptrs, sizeof(void*), 0);

	Point p1 = {1, 2};
	Point p2 = {3, 4};

	printf("%p, x = %d\n", &p1, p1.x);
	printf("%p, x = %d\n", &p2, p2.x);

	Vector_push_back_ptr(&ptrs, &p1);
	Vector_push_back_ptr(&ptrs, &p2);
	Vector_push_back_ptr(&ptrs, &(Point){5, 6});
	Vector_push_back_ptr(&ptrs, &(Point){7, 8});

	Vector_pop_back(&ptrs);

	Vector_push_back_ptr(&ptrs, &(Point){11, 22});

	Point **pdata = ptrs.data;

	for (int i = 0; i < Vector_size(&ptrs); i++) {
		printf("data: 0x%p, x = %d, y = %d\n",
			pdata[i],
			pdata[i]->x,
			pdata[i]->y
		);
	}

	Vector_destroy(&ptrs);

	_getch();

	return 0;
}
