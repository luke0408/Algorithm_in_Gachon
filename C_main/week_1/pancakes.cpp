#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 30

int *getArray(int *);
int *toMalloc(int *, int);

void flip(int[], int);
int findMax(int[], int);
int pancakeSort(int *, int);
void printArray(int[], int);
void printCount();

int global_i = 0;
int count = 0;

// Driver program to test above function
int main()
{
  int *arr = getArray(arr);

  printf("%d\n", global_i);

  printf("Sorting starts...\n\n");
  printArray(arr, global_i);

  pancakeSort(arr, global_i);

  printf(" (");
  printArray(arr, global_i);
  printf(")\n");
  printCount();
  return 0;
}

int *getArray(int *arr)
{
  int tmp_arr[MAX_LENGTH];
  int i = 0, n;

  while (scanf("%d", &n) != EOF)
  {
    if (1 <= n && n <= 10)
      tmp_arr[i++] = n;
    if (char c = getchar() == '\n')
      break;
  }

  printf("i: %d\n", i);
  arr = toMalloc(tmp_arr, i);

  return arr;
}

int *toMalloc(int tmp_arr[], int i)
{
  int *arr = (int *)malloc(sizeof(int) * i);
  global_i = i;
  for (int j = 0; j < i; j++)
    arr[j] = tmp_arr[j];
  return arr;
}

/* Reverses arr[0..i] */
void flip(int *arr, int i)
{
  int temp, start = 0;

  while (start < i)
  {
    temp = arr[start];
    arr[start] = arr[i];
    arr[i] = temp;
    start++;
    i--;
  }

  if (i != 0)
    count++;
}

int find_max_index(int *arr, int n)
{
  int mi, i;

  for (mi = 0, i = 0; i < n; ++i)
  {
    if (arr[i] > arr[mi])
      mi = i;
  }

  return mi;
}

int pancakeSort(int *arr, int n)
{
  for (int curr_size = n; curr_size > 1; --curr_size)
  {
    int mi = find_max_index(arr, curr_size);

    if (mi != curr_size - 1)
    {
      flip(arr, mi);
      flip(arr, curr_size - 1);
    }
  }
}

void printArray(int *arr, int n)
{
  printf("%d ", arr[0]);

  for (int i = 1; i < n; ++i)
    printf("%d ", arr[i]);
}

void printCount()
{
  for (int i = 1; i <= count; i++)
    printf("%d ", i);

  printf("0\n");
}
