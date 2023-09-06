#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
문제: sweet nap
설명:
- N개의 일정과 각 일정의 시작 시간과 종료 시간이 주어진다.
- 이때 가장 길게 낮잠을 잘 수 있는 시간을 출력하라.
입력:
- 첫 줄에 일정의 개수 N이 주어진다. (1 <= N <= 100)
- 이후에 일정에 대한 정보가 주어진다. (ex. hh:mm hh:mm Lecture)
출력:
- 가장 길게 낮잠을 잘 수 있는 시작 시간과 이용가능한 시간을 출력한다.
*/

#define MAX_LENGTH 255

int get_time_gap(char*, char*);
void input(char*);

int main(){
  int n;
  scanf("%d", &n);

  int max_gap = 0;
  char result_start[MAX_LENGTH];
  char cur_end[MAX_LENGTH];  

  for (int i = 0; i < n; i++){
    char new_start[MAX_LENGTH];
    char new_end[MAX_LENGTH];
    char new_dis[MAX_LENGTH];

    scanf("%s %s", new_start, new_end);
    input(new_dis);

    char stock[MAX_LENGTH];
    strcpy(stock, cur_end);

    if (i > 0) {
      int gap = get_time_gap(cur_end, new_start);
      if (gap > max_gap) {
        max_gap = gap;
        strcpy(result_start, stock);
      }
    }

    strcpy(cur_end, new_end);
  }

  int h = max_gap / 60;
  int m = max_gap % 60;

  printf("%s %d:%d\n", result_start, h, m);

  return 0;
}

int get_time_gap(char* start, char* end){
  int start_hour = atoi(strtok(start, ":"));
  int start_min = atoi(strtok(NULL, ":"));
  int end_hour = atoi(strtok(end, ":"));
  int end_min = atoi(strtok(NULL, ":"));

  int start_time = start_hour * 60 + start_min;
  int end_time = end_hour * 60 + end_min;

  return end_time - start_time;
}

void input(char* input){
  int i = 0;

  while (i < MAX_LENGTH - 1)
  {
    char c = getchar();
    if (c == '\n') break;
    input[i++] = c;
  }
  
  input[i] = '\0';
}