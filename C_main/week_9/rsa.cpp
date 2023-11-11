#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

/**
 * [Data Description]
 * e[100] : Encryption Key
 * d[100] : Decryption Key
 * temp[100] : Temporary Key
 * m[100] : Message
 * en[100] : Encrypted Message
 * 
 * [Variables]
 * p, q : Prime Number 
 * n : p * q
 * t : (p - 1) * (q - 1)
 * flag : Flag
 */
long int p, q, n, t, flag, e[100], d[100], temp[100], j, m[100], en[100], i;
char msg[100];

/**
 * [Methods]
 */
int prime(long int);
void get_ek();
long int get_dk(long int);
void encrypt();
void decrypt();

int main() {
  printf("\nENTER FIRST PRIME NUMBER: ");
  scanf("%ld", &p);

  if (!prime(p)) {
    printf("\nIS NOT PRIME\n");
    getchar();
    exit(1);
  }

  printf("\nENTER ANOTHER PRIME NUMBER: ");
  scanf("%ld", &q);

  if (!prime(q)) {
    printf("\nIS NOT PRIME\n");
    getchar();
    exit(1);
  } else if (p == q) {
    printf("\nBOTH PRIME NUMBERS ARE SAME\n");
    getchar();
    exit(1);
  }
  
  printf("\nENTER MESSAGE: ");
  fflush(stdin);
  scanf("%s", msg);
  for (i = 0; msg[i] != '\0'; i++) m[i] = msg[i];

  n = p * q;
  t = (p - 1) * (q - 1);
  get_ek();


  printf("\nPOSSIBLE VALUES OF e AND d List\n");
  for (i = 0; i < j - 1; i++) printf("\n[%d]\t%ld\t%ld", i, e[i], d[i]);

  // print encryption message
  encrypt();

  // print decryption message
  decrypt();

  return 0;
}

/**
 * [Prime Number Check]
 * @param a [long int]
 * @return  [1 : Prime Number, 0 : Not Prime Number]
 */
int prime(long int a) {
  int k;
  j = sqrt(a);
  for (k = 2; k <= j; k++) {
    if (a % k == 0) return 0;
  }
    return 1;
}

/**
 * [Encryption Key]
 * @param   [void]
 * @return  [void]
 */
void get_ek() {
  int k;
  k = 0;
  for (i = 2; i < t; i++) {
    if (t % i == 0) continue;
    
    flag = prime(i);
    
    if (flag == 1 && i != p && i != q) {
      e[k] = i;
      flag = get_dk(e[k]);
      if (flag > 0) {
        d[k] = flag;
        k++;
      }
      if (k == 99) break;
    }
  }
}

/**
 * [Decryption Key]
 * @param x [long int]
 * @return  [long int]
 */
long int get_dk(long int x) {
  long int k = 1;
  while (1) {
    k = k + t;
    if (k % x == 0) return (k / x);
  }
}

/**
 * [Encryption]
 * @param   [void]
 * @return  [void]
 */
void encrypt() {
  long int pt, ct, key = e[0], k, len;
  i = 0;
  len = strlen(msg);
  while (i != len) {
    pt = m[i];
    pt = pt - 96;
    k = 1;
    for (j = 0; j < key; j++) {
      k = k * pt;
      k = k % n;
    }
    temp[i] = k;
    ct = k + 96;
    en[i] = ct;
    i++;
  }
  en[i] = -1;
  printf("\n\nTHE ENCRYPTED MESSAGE: ");
  for (i = 0; en[i] != -1; i++) printf("%c", en[i]);
}

/**
 * [Decryption]
 * @param   [void]
 * @return  [void]
 */
void decrypt() {
  long int pt, ct, key = d[0], k;
  i = 0;
  while (en[i] != -1) {
    ct = temp[i];
    k = 1;
    for (j = 0; j < key; j++) {
      k = k * ct;
      k = k % n;
    }
    pt = k + 96;
    m[i] = pt;
    i++;
  }
  m[i] = -1;
  printf("\n\nTHE DECRYPTED MESSAGE: ");
  for (i = 0; m[i] != -1; i++) printf("%c", m[i]);
}