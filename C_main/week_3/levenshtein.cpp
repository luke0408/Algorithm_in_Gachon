#include <stdio.h>
#include <string.h>

#define BASE        1000000000
#define MAX_COLUMN  10000
#define MAX_ROW     100

typedef struct _cell
{
  int len;
  int val[MAX_ROW];
} cell;

char s[MAX_COLUMN], z[MAX_ROW]; // intput set
cell m[MAX_COLUMN][MAX_ROW];    // for DP
int n;                          // number of intput data set 

// init
void str_init(char*, char*);
void init(cell*);

// operation
cell add(cell*, cell*);
void cell_swap(cell*, cell*);
cell get_cost(cell*, cell*);

// print
void print_result(cell*);

int main() {
  int i, j;
  cell zero, one;
  init(&zero);
  one.val[0] = 1, one.len = 1;

  for (i = 0; i < MAX_COLUMN + 1; ++i)
    for (j = 0; j < MAX_ROW; ++j)
      init(&m[i][j]);

  scanf("%d", &n);
  while (n-- > 0)
  {
    str_init(s, z);

    for (i = 0; s[i]; ++i)
    {
      m[i + 1][1] = m[i][1];
      if (s[i] == z[0])
        m[i + 1][1] = add(&m[i + 1][1], &one);
    }
    
    for (j = 1; z[j]; ++j)
    {
      for (i = j; s[i]; ++i)
      {
        m[i + 1][j + 1] = m[i][j + 1];
        if (s[i] == z[j])
          m[i + 1][j + 1] = add(&m[i + 1][j + 1], &m[i][j]);
      }
    }
    print_result(&m[strlen(s)][strlen(z)]);
  }
  return 0;
}

// init 
void str_init(char* s, char* z)
{
  scanf("%s", s);
  scanf("%s", z);
}

void init(cell* p) {
  p->len = 1;
  p->val[0] = 0;
}

// operation
cell add(cell* a, cell* b) {
  if (a->len > b->len) cell_swap(a, b);
  return get_cost(a, b);
}

void cell_swap(cell* a, cell* b) {
  cell* t = a;
  a = b;
  b = t;
}

cell get_cost(cell* a, cell* b) {
  cell ret = {0};
  int i, j;

  for (i = 0; i < a->len; ++i)
  {
    ret.val[i] += a->val[i] + b->val[i];
    ret.val[i + 1] = (ret.val[i] / BASE);
    ret.val[i] %= BASE;
  }

  while (i < b->len)
  {
    ret.val[i] += b->val[i];
    ret.val[i + 1] += (ret.val[i] / BASE);
    ret.val[i] %= BASE;
    ++i;
  }

  j = i + (ret.val[i] != 0);
  ret.len = j;
  return ret;
}

// print
void print_result(cell* a) {
  int i = a->len - 1;

  printf("result: %d", a->val[i]);
  for (i = a->len - 2; i >= 0; --i)
    printf(" %d", a->val[i]);
  putchar('\n');
}