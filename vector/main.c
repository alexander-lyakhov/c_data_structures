#include <stdio.h>
#include <conio.h>
#include <windows.h>

#define LINE puts("----------------------------------------------");

#define DEFAULT_VECTOR_CAPACITY 256

#define Vector_append(vector, value)                                                \
{                                                                                   \
	Vector_check_capacity(vector);                                                  \
	void *target = (vector)->data + (vector)->count * (vector)->type_size;          \
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

// =============================================================================
// @@@ + Vector_init
// =============================================================================
Vector* Vector_init(Vector *vector, short type_size)
{
	printf("Vector_init: %d\n", type_size);

	vector->data = malloc(type_size * DEFAULT_VECTOR_CAPACITY);
	vector->capacity = DEFAULT_VECTOR_CAPACITY;
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
// @@@ + Vector_push_backi
// =============================================================================
void Vector_push_backi(Vector *vector, int value)
{
	Vector_append(vector, value);
	printf("%d, %d\n", value, vector->capacity);
}

// =============================================================================
// @@@ + Vector_push_backf
// =============================================================================
void Vector_push_backf(Vector *vector, float value)
{
	Vector_append(vector, value);
	printf("%.3f, %d\n", value, vector->capacity);
}

// =============================================================================
// @@@ + Vector_push_backd
// =============================================================================
void Vector_push_backd(Vector *vector, double value)
{
	Vector_append(vector, value);
	printf("%.3f, %d\n", value, vector->type_size);
}

// =============================================================================
// @@@ + Vector_push_backstr
// =============================================================================
void Vector_push_backstr(Vector *vector, char* value)
{
	Vector_append(vector, value);
	printf("%s, %d\n", value, vector->capacity);
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

int main()
{
	system("cls");

	LINE;
	
	Vector vectori;
	Vector_init(&vectori, sizeof(int));

	LINE;

	Vector_push_backi(&vectori, 10);
	Vector_push_backi(&vectori, 20);
	Vector_push_backi(&vectori, 30);

	puts("");

	int *datai = vectori.data;

	for (int i = 0; i < Vector_size(&vectori); i++) {
		printf("data: %d\n", datai[i]);
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

	Vector_push_backf(&vectord, 10.1);
	Vector_push_backf(&vectord, 20.2);
	Vector_push_backf(&vectord, 30.3);
	
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
