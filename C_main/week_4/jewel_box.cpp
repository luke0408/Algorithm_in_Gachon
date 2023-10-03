#include <stdio.h>

int main(){
    int jew = 0;
    int c[2], n[2];

    for(;;) {
        scanf("%d", &jew);
        if (jew == 0) break;

        for (int i = 0; i < 2; i++)
            scanf("%d %d", &c[i], &n[i]);

        int max = 0, big_n = 0, small_n = 0;
        int flag = 0;
        if (n[0] / c[0] < n[1] / c[1]) flag = 1;

        max = jew / n[flag];
        big_n = n[flag];
        small_n = n[(flag + 1) % 2];

        int i;
        for (i = 0; i < max; i++) {
            if (jew % big_n < small_n * i) max--;

            if ((max * big_n) + (i * small_n) == jew) {
                if (flag) {
                    printf("%d %d\n", i, max);
                    break;
                } else {
                    printf("%d %d\n", max, i);
                    break;
                }
            }
        }

        if ((max * big_n) + (i * small_n) != jew) printf("failed\n");
    }

    return 0;
}
