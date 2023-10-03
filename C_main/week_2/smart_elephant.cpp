#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 10000
#define MAX_ELEPHANT 1000

typedef struct _elephant {
    int order;
    int weight;
    int IQ;
} elephant;

void elephant_swap(elephant*, elephant*);
void sort(elephant*, int);
void smart(elephant*, int);

int main() {
    int n = 0;
    elephant elephants[MAX_ELEPHANT] = {0, };
    int weight, IQ;

    while (scanf("%d %d", &weight, &IQ) != EOF) {
        if (n >= MAX_ELEPHANT) break;

        elephants[n].weight = weight;
        elephants[n].IQ = IQ;
        elephants[n].order = n + 1;
        n++;
    }

    sort(elephants, n);
    smart(elephants, n);

    return 0;
}


void elephant_swap(elephant *i, elephant *index) {
    int temp_order = i->order;
    int temp_weight = i->weight;
    int temp_IQ = i->IQ;

    i->order = index->order;
    i->weight = index->weight;
    i->IQ = index->IQ;

    index->order = temp_order;
    index->weight = temp_weight;
    index->IQ = temp_IQ;
}

void sort(elephant *elephants, int n) {
    int min = 0, index = 0;
    for (int i = 0; i < n; i++) {
        min = elephants[i].weight;
        index = i;
        for (int j = i + 1; j < n; j++) {
            if (elephants[j].weight < min) {
                min = elephants[j].weight;
                index = j;
            }
        }
        elephant_swap(&elephants[i], &elephants[index]);
    }
}

void smart(elephant *elephants, int n) {
    int count = 0, iq = 0;
    int* result = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        if (i == 0) {
            result[count] = elephants[i].order;
            iq = elephants[i].IQ;
            count++;
            continue;
        }

        if (elephants[i].IQ > iq) {
            if (count < 2) {
                count = 0;
                result[count] = elephants[i].order;
                iq = elephants[i].IQ;
                count++;
            }
        } else {
            result[count] = elephants[i].order;
            iq = elephants[i].IQ;
            count++;
            continue;
        }
    }

    printf("%d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d\n", result[i]);
    }
}