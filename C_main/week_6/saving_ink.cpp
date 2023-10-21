#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _Dot
{
  double x;
  double y;
} Dot;

void input_data(Dot *dot, int time)
{
  double x, y;
  for (int i = 0; i < time; i++){
    scanf("%lf %lf", &x, &y);
    (dot+i)->x = x; (dot+i)->y = y;
  }
}

int contains(int* flag, int index, int i, int j) {
  int a = 0, b = 0;
  for (int k = 0; k < index; k++){
    if (a == 0 && flag[k] == i)
      a = 1;
    else if (b == 0 && flag[k] == j)
      b = 1;
  }

  if (a == 1 && b == 1) return 1;
  else return 0;
}

void find_minimum(Dot *dot, int time)
{
  double sum = 0;
  int* flag = (int*)malloc(sizeof(int) * time * 2);
  int count = 0, index = 0;

  while (count != time-1) {
    int flag_i = 0, flag_j = 0;
    double min = 1000000;

    for (int i = 0; i < time; i++){
      for (int j = 0; j < time; j++){
        if (i == j || contains(flag, index, i, j)) 
          continue;

        double dis = sqrt(pow(dot[i].x - dot[j].x, 2.0) + pow(dot[i].y - dot[j].y, 2.0));
        if (dis < min) {
          min = dis;
          flag_i = i;
          flag_j = j;
        }
      }
    }

    flag[index++] = flag_i;
    flag[index++] = flag_j;
    count++;

    sum += min;
  }

  printf("%.2lf", round(sum*100) / 100.0);
  free(flag);
}

int main()
{
  int time = 0;
  scanf("%d", &time);
  Dot *dot = (Dot *)malloc(sizeof(Dot) * time);

  input_data(dot, time);
  find_minimum(dot, time);

  free(dot);
}