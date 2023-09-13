#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
문제: pancakes
설명:
- N개의 팬케이크가 쌓여져있을때 해당 팬케이크를 뒤집어서 정렬하고자 한다.
- flips: 정렬이 아니라 아에 뒤집는 것.
*/

#define MAX_LENGTH 30

char* get_input();
int* get_array(char*);

void flip(int[], int);
int findMax(int[], int);
int pancakeSort(int*, int);
void printArray(int[], int);

// Driver program to test above function
int main()
{
  int* arr;
  int n = get_array(get_input(), arr);

  pancakeSort(arr, n);

  puts("Sorted Array ");
  printArray(arr, n);

  return 0;
}

char* get_input() {
  char* intput_str; char input;
  int i = 0;

  while (scanf("%c", &input) != EOF) {
    intput_str[i] = input;
    i++;
  }

  intput_str[i] = '\0';

  return intput_str;
}

int get_array(char* input_str, int* arr) {
  int temp_arr[MAX_LENGTH];
  int i = 0;

  char* token = strtok(input_str, " ");
  int num;

  while (token != NULL && i < MAX_LENGTH) {
    num = atoi(token);

    if (0 < num && num < 10) {
      temp_arr[i] = num;
      i++;
    }

    token = strtok(NULL, " ");
  }

  return i;
}

/* Reverses arr[0..i] */
void flip(int arr[], int i) {
  int temp, start = 0;
  
  while (start < i) {
    temp = arr[start];
    arr[start] = arr[i];
    arr[i] = temp;
    start++;
    i--;
  }
}

int findMax(int arr[], int n)
{
  int mi, i;
  
  for (mi = 0, i = 0; i < n; ++i) {    
    if (arr[i] > arr[mi]) mi = i;
  }
  
  return mi;
}

int pancakeSort(int *arr, int n) {
  for (int curr_size = n; curr_size > 1; --curr_size) {
    int mi = findMax(arr, curr_size);

    if (mi != curr_size - 1) {
      flip(arr, mi);
      flip(arr, curr_size - 1);
    }
  }
}

void printArray(int arr[], int n)
{
  for (int i = 0; i < n; ++i)
    printf("%d ", arr[i]);
}