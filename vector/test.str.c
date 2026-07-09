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

	Vector vstr;
	Vector_init(&vstr, sizeof(char*), 0);

	Vector_push_back_ptr(&vstr, "one");
	Vector_push_back_ptr(&vstr, "two");
	Vector_push_back_ptr(&vstr, "three");
	Vector_push_back_ptr(&vstr, "four");

	Vector_pop_back(&vstr);

	Vector_push_back_ptr(&vstr, "five");

	((char**)vstr.data)[0] = "one and half";

	// *******************************************
	title("Iterate vector");
	// *******************************************
	char **data = vstr.data;

	for (int i = 0; i < Vector_size(&vstr); i++) {
		printf("data: 0x%p, %s\n", data[i], data[i]);
	}

	Vector_destroy(&vstr);

	_getch();

	return 0;
}
