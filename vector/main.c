#include <stdio.h>
#include <conio.h>
#include <assert.h>
// #include <windows.h>


#define VECTOR_IMPLEMENTATION
#include "vector.h"

// TODO
// void* front()
// void* back()
// clear()

#define LINE puts("----------------------------------------------");

int main()
{
	// system("cls");

	LINE;
	
	Vector vectorc;
	Vector_init(&vectorc, sizeof(char));

	LINE;

	Vector_push_backc(&vectorc, 'a');
	Vector_push_backc(&vectorc, 'b');
	Vector_push_backc(&vectorc, 'c');

	puts("");

	char *datac = vectorc.data;

	for (int i = 0; i < Vector_size(&vectorc); i++) {
		printf("data: %c\n", datac[i]);
	}

	Vector_destroy(&vectorc);

	// ==============================================
	
	LINE;
	
	Vector vectori;
	Vector_init(&vectori, sizeof(int));

	LINE;

	Vector_push_backi(&vectori, -10);
	Vector_push_backi(&vectori, -20);
	Vector_push_backi(&vectori, -30);

	puts("");

	int *datai = vectori.data;

	for (int i = 0; i < Vector_size(&vectori); i++) {
		printf("data: %d\n", datai[i]);
	}

	Vector_pop_back(&vectori);
	Vector_push_backi(&vectori, 50);

	puts("");

	for (int i = 0; i < vectori.count; i++) {
		printf("data: %d\n", ((int*)vectori.data)[i]);
	}

	Vector_destroy(&vectori);
	
	// ==============================================

	LINE;

	Vector vectorf;
	Vector_init(&vectorf, sizeof(float));

	LINE;

	Vector_push_backf(&vectorf, 10.1);
	Vector_push_backf(&vectorf, 20.2);
	Vector_push_backf(&vectorf, 30.3);
	
	puts("");

	float *dataf = vectorf.data;

	for (int i = 0; i < Vector_size(&vectorf); i++) {
		printf("data: %f\n", dataf[i]);
	}

	Vector_destroy(&vectorf);

	// ==============================================

	LINE;

	Vector vectord;
	Vector_init(&vectord, sizeof(double));

	LINE;

	Vector_push_backd(&vectord, 10.1);
	Vector_push_backd(&vectord, 20.2);
	Vector_push_backd(&vectord, 30.3);
	
	puts("");

	double *datad = vectord.data;

	for (int i = 0; i < Vector_size(&vectord); i++) {
		printf("data: %.2f\n", dataf[i]);
	}

	Vector_destroy(&vectord);

	// ==============================================

	LINE;

	Vector vectorstr;
	Vector_init(&vectorstr, sizeof(char*));

	LINE;

	Vector_push_backstr(&vectorstr, "one");
	Vector_push_backstr(&vectorstr, "two");
	Vector_push_backstr(&vectorstr, "three");
	Vector_push_backstr(&vectorstr, "four");
	Vector_push_backstr(&vectorstr, "five");
	Vector_push_backstr(&vectorstr, "six");
	Vector_push_backstr(&vectorstr, "seven");
	Vector_push_backstr(&vectorstr, "eight");
	Vector_push_backstr(&vectorstr, "nine");
	
	puts("");

	char **datastr = vectorstr.data;

	for (int i = 0; i < Vector_size(&vectorstr); i++) {
		printf("data: %s\n", datastr[i]);
	}

	Vector_destroy(&vectorstr);

	// ==============================================

	_getch();

	return 0;
}
