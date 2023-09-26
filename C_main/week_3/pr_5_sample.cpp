#include <stdio.h>
#include <string.h>
#define BASE 1000000000
#define GAP 9

typedef struct bignum_t
{
  int len;
  int val[100];
} bignum_t;

void init(bignum_t *p)
{
  p->len = 1;
  p->val[0] = 0;
}

bignum_t add(bignum_t *a, bignum_t *b)
{
  bignum_t ret = {0};
  int i, j;

  if (a->len > b->len)
  {
    bignum_t *t = a;
    a = b;
    b = t;
  }

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

// 프린트용
void print_bignum(bignum_t *a)
{
  int i;

  i = a->len - 1;
  printf("result: %d", a->val[i]);
  for (i = a->len - 2; i >= 0; --i)
    printf("%0*d", GAP, a->val[i]);
  putchar('\n');
}


// 데이터 배열
char a[10001], b[101];
bignum_t f[10001][101];
int n;

// 입력용
void str_init(char* s, char* z)
{
  scanf("%s", s);
  scanf("%s", z);
}

int main()
{
  int i, j;
  bignum_t zero, one;
  init(&zero);
  one.val[0] = 1, one.len = 1;

  for (i = 0; i < 10001; ++i)
    for (j = 0; j < 101; ++j)
      init(&f[i][j]);

  scanf("%d", &n);
  while (n-- > 0)
  {
    str_init(a, b);

    for (i = 0; a[i]; ++i)
    {
      f[i + 1][1] = f[i][1];
      if (a[i] == b[0])
        f[i + 1][1] = add(&f[i + 1][1], &one);
    }

    for (j = 1; b[j]; ++j)
    {
      for (i = j; a[i]; ++i)
      {
        f[i + 1][j + 1] = f[i][j + 1];
        if (a[i] == b[j])
          f[i + 1][j + 1] = add(&f[i + 1][j + 1], &f[i][j]);
      }
    }
    print_bignum(&f[strlen(a)][strlen(b)]);
  }
  return 0;
}