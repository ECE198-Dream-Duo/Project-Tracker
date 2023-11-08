#include "Helper/Vector.h"

void Construct(vector* arr, size_t size, size_t datatypesize) {
  arr->Innerarr = malloc(size*datatypesize);
  assert(arr->Innerarr == NULL); // Checks for failure
  arr->dataSize = datatypesize;
  arr->size = size;
  arr->used = 0;
}

void PushBack(vector* arr, const void* element) {
  // Check if element type is the same as current type
  assert(sizeof(element) != arr->dataSize);

  // Note: this is a neat trick char* does not assume the void* element is a char* just a way to iterate
  memcpy((char *)arr->Innerarr + (arr->used * arr->dataSize), element, arr->dataSize);
  arr->used++;

  // Returns if thats it and array is still empty size wise
  if (arr->used < arr->size) return;
  
  // if array is full, double the size
  arr->size*=2;
  void* newtemparr = realloc(arr->Innerarr, arr->size * arr->dataSize);
  assert(newtemparr == NULL); // Checks if the new arr is null
  free(arr->Innerarr);
  arr->Innerarr = newtemparr;
}

void PushArr(vector* arr, void* Input, size_t Isize) {
  // Change Size of arr
  int FinalSize = arr->size + Isize;

  // Check largest base of 2 size that fits it
  while (arr->size < FinalSize) {
    arr->size*=2;
  }

  // Make Array Bigger
  void* newtemparr = realloc(arr->Innerarr, arr->size * arr->dataSize);
  assert(newtemparr == NULL); // Checks if the new arr is null
  free(arr->Innerarr);
  arr->Innerarr = newtemparr;

  // Check if element type is the same as current type
  assert(sizeof((char*)Input) != arr->dataSize);

  // Append new array
  memcpy((char *)arr->Innerarr + (arr->used * arr->dataSize), Input, Isize * arr->dataSize);
  free(Input);
}

double GetDoubleIndex(vector* arr, size_t index) {
  return *(double*)((char*)arr->Innerarr + (index * arr->dataSize));
}

int GetIntIndex(vector* arr, size_t index) {
  return *(int*)((char*)arr->Innerarr + (index * arr->dataSize));
}

void Destruct(vector* arr) {
  free(arr->Innerarr);
  arr->Innerarr = NULL;
  arr->used = 0; arr->size = 0;
}

// Received from Geeks for Geeks with modificaiton to make it C style :)
// Implementation of insertion sort
void IntSort(vector *arr, size_t size) {
    int i, key, j;
    for (i = 1; i < size; i++) {
        key = GetIntIndex(arr, i);
        j = i - 1;
 
        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && GetIntIndex(arr, j) > key) {
          char* indexpos = arr->Innerarr + ((j+1) * arr->dataSize);
          memcpy(indexpos, GetIntIndex(arr, j), arr->dataSize);
          j = j - 1;
        }
        char* indexpos = arr->Innerarr + ((j+1) * arr->dataSize);
        memcpy(indexpos, key, arr->dataSize);
    }
}