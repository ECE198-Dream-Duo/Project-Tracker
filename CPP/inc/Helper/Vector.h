#include <stddef.h>

typedef struct {
  void* Innerarr;
  size_t size;
  size_t used;
  size_t dataSize;
} vector;

void Construct(vector* arr, size_t size, size_t datatypesize); // Construct a dynamic array of void* type
void PushBack(vector* arr, const void* element); // Push back one element of void* type
void PushArr(vector* arr, void* Input, size_t Isize); // Pushes back a whole array of void* type
double GetDoubleIndex(vector* arr, size_t index);
int GetIntIndex(vector* arr, size_t index);
void Destruct(vector* arr); // Destructs Array after usage
void IntSort(vector* arr, size_t size); // Sorts the Array using integer cast