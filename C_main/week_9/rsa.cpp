#include <stdio.h>
#include <ctype.h>
#include <math.h>

int gcd(int, int);
int rsa(int, int, int);

int main()
{
  // keys
  int p = 17, q = 13;
  int n, e, d, f;

  n = p * q;
  f = (p - 1) * (q - 1);

  // find e
  for (int i = 2; i < f; i++)
  {
    if (gcd(p - 1, i) == 1 && gcd(q - 1, i) == 1)
    {
      e = i;
      break;
    }
  }

  // find d
  for (int i = 2; i < n; i++)
  {
    if ((1 + f * i) % e == 0)
    {
      d = (1 + f * i) / e;
      break;
    }
  }

  printf("p\tq\tn\te\td\tf\n");
  printf("%d\t%d\t%d\t%d\t%d\t%d\n\n", p, q, n, e, d, f);

  // encryption
  int msg = 'b';
  printf("msg : %c\n", msg);

  int c = rsa(n, msg, e);
  printf("c : %c\n", c);

  // decryption
  int msg2 = rsa(n, c, d);
  printf("msg : %c\n", msg2);

  return 0;
}

int gcd(int a, int b)
{
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

int rsa(int n, int m, int d)
{
  int bin[10] = {
      0,
  };
  int tmp, j = 1;
  unsigned long long x_tmp = 1;
  int x[10];

  x[0] = (unsigned long long)pow(m, 1) % n;
  for (int i = 1; i < 10; i++)
  {
    x[i] = (x[i - 1] * x[i - 1]) % n;
  }

  for (int i = 0; d > 0; i++)
  {
    tmp = d % 2;
    d /= 2;
    bin[i] = tmp;
  }

  for (int i = 0; i < 10; i++)
  {
    if (bin[i] == 1)
    {
      x_tmp *= x[i];
    }
  }

  return x_tmp % n;
}