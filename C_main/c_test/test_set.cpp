//
// Created by chltj on 2023-10-25.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE 10

struct database {
    char name[20];
    int rain;
    int dust;
    int degree;
    int rankRain;
    const char *dustCondition;
};

void fileRead(struct database *data[]);
void fileWrite(struct database *data[]);
void dataSorting(struct database *data[]);
void dataGenerating(struct database *data[]);
void printConsole(struct database *data[]);

int main(void) {
    struct database *data[SIZE];

    fileRead(data);
    dataGenerating(data);
    dataSorting(data);
    fileWrite(data);
    printConsole(data);
}

void fileRead(struct database *data[]) {
    FILE *ifp = fopen("weatherInput.txt", "r");
    if(ifp == NULL) {
        printf("FILE_READ_ERROR\n");
        exit(-1);
    }

    int i=0;
    char str[20];
    while(!feof(ifp)) {
        fscanf(ifp, "%s", str);
        printf("%s\n", str);
        strcpy(data[i]->name, str);
    }

    fclose(ifp);

    printf("File_Read_Successful\n");
}

void dataGenerating(struct database *data[]) {
    srand(time(NULL));

    for(int i=0; i<SIZE; i++) {
        data[i]->rain = rand() % 101;
        data[i]->dust = rand() % 301;
        data[i]->degree = rand() % 51-10;
    }
}

void dataSorting(struct database *data[]) {
    for(int i=0; i<SIZE; i++) {
        data[i]->rankRain = 1;
        for(int j=0; j<SIZE; j++) {
            if(data[i]->rain < data[j]->rain) {
                data[i]->rankRain++;
            }
        }
    }

    for(int i=0; i<SIZE; i++) {
        if(data[i]->dust < 50) {
            data[i]->dustCondition = "좋음";
        }
        else if(data[i]->dust < 150) {
            data[i]->dustCondition = "보통";
        }
        else {
            data[i]->dustCondition = "나쁨";
        }
    }
}

void fileWrite(struct database *data[]) {
    FILE *ofp = fopen("weatherOutput.txt", "w");
    if(ofp == NULL) {
        printf("FILE_WRITE_ERROR\n");
        exit(-1);
    }

    fprintf(ofp, "========== Weather Data Sheet ==========\n");
    for(int i=0; i<SIZE; i++) {
        fprintf(ofp, "%s %d %d %s %d %d\n", data[i]->name, data[i]->rain, data[i]->dust, data[i]->dustCondition, data[i]->degree, data[i]->rankRain);
    }
    fprintf(ofp, "========================================\n");

    fclose(ofp);

    printf("File_Write_Successful\n");
}

void printConsole(struct database *data[]) {

    printf("========== Weather Data Sheet ==========\n");
    for(int i=0; i<SIZE; i++) {
        printf("%s %d %d %s %d %d\n", data[i]->name, data[i]->rain, data[i]->dust, data[i]->dustCondition, data[i]->degree, data[i]->rankRain);
    }
    printf("========================================\n");
}