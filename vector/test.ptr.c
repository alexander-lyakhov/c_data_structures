#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>

#define VECTOR_DEBUG
#define VECTOR_IMPLEMENTATION
#include "vector.h"

#define LINE(size) for (int i = 0; i < (size) + 6; i++) printf("-"); puts("");

typedef struct { int x, y; } Point;

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

	((Point**)ptrs.data)[0] = &((Point){12, 24});

	// *******************************************
	title("Iterate vector");
	// *******************************************
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
