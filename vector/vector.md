# STB-style single-header-file Vector implementation for C

***The std::vector from the STL library was used as a reference.***

### Methods

|Method|Descrition|
|-|-|
|`Vector* Vector_init(Vector *vector, short type_size, size_t capacity`)|Init vector|
|`void Vector_push_back_c(Vector *v, char value)`|Push a character to the end of the vector|
|`void Vector_push_back_s(Vector *v, short value)`|Push a short type value to the end of the vector|
|`void Vector_push_back_i(Vector *v, int value)`|Push an integer type value to the end of the vector|
|`void Vector_push_back_l(Vector *v, long value)`|Push a long type value to the end of the vector|
|`void Vector_push_back_ll(Vector *v, long long value)`|Push a long long type value to the end of the vector|
|`void Vector_push_back_f(Vector *v, float value)`|Push a float type value to the end of the vector|
|`void Vector_push_back_d(Vector *v, double value)`|Push a double type value to the end of the vector|
|`void Vector_push_back_ld(Vector *v, long double value)`|Push a long double type value to the end of the vector|
|`void Vector_push_back_str(Vector *v, char* value)`|Push a string (char*) to the end of the vector|
|`void Vector_push_back_ptr(Vector *v, void* value)`|Push a pointer to the end of the vector|
|`void Vector_pop_back(Vector *v)`|Remove last element from vector|
|`void* Vector_front(Vector *v)`|Get pointer to the first element in vector. If vector is empty the function returns NULL pointer|
|`void* Vector_back(Vector *v)`|Get pointer to the last element in vector. If vector is empty the function returns NULL pointer|
|`void Vector_clear(Vector *v)`|Clear vector|
|`void Vector_destroy(Vector *v)`|Destroy vector|


### Code examples

#### Primitive data types

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

#### Pointers eexample

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

#### String example (char*)

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
