#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/**
 * [Data Structure]
 */

typedef struct
{
    double x;
    double y;
} Point;

/**
 * [Global Variables]
 */

static Point first_point;

/**
 * [Functions]
 */

void read_point(Point*, int);
void print_point(Point*);
int point_size(Point*);
void sort(Point*, Point*, bool (*compare)(const Point*, const Point*));

double compute_distance(const Point*, const Point*);
double ccw(const Point*, const Point*, const Point*);

bool compare_points_by_yx(const Point*, const Point*);
bool compare_points_by_angle(const Point*, const Point*);

void compute_hull(Point*);
void analyze_hull(Point*);
double compute_hull_size(Point*);

int main() {
    int n, k;
    Point* points;

    scanf("%d", &n);
    printf("\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &k);

        k++;
        points = (Point*)malloc(sizeof(Point) * k);
        points[0].x = 0;
        points[0].y = 0;

        read_point(points, k);
        compute_hull(points);
        analyze_hull(points);

        printf("%.2lf\n", compute_hull_size(points));

        free(points);
    }

    return 0;
}

void read_point(Point* points, int k) {
    for (int i = 1; i < k; i++) {
        scanf("%lf %lf", &points[i].x, &points[i].y);
    }
}

void print_point(Point* points) {
    for (int i = 0; i < 10; i++) {
        printf("%.2lf %.2lf\n", points[i].x, points[i].y);
    }
}

int point_size(Point* points) {
    int i = 1;
    while (points[i].x != 0 && points[i].y != 0) {
        i++;
    }
    return i;
}

void sort(Point* begin, Point* end, bool (*compare)(const Point*, const Point*)) {
    int size = end - begin;
    Point temp;

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (!compare(&begin[j], &begin[j + 1])) {
                temp = begin[j];
                begin[j] = begin[j + 1];
                begin[j + 1] = temp;
            }
        }
    }
}

double compute_distance(const Point* p1, const Point* p2) {
    return sqrt(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2));
}

double ccw(const Point* p1, const Point* p2, const Point* p3) {
    return (p1->x * p2->y + p2->x * p3->y + p3->x * p1->y) - (p1->y * p2->x + p2->y * p3->x + p3->y * p1->x);
}

bool compare_points_by_yx(const Point* p1, const Point* p2) {
    if (p1->y == p2->y) {
        return p1->x < p2->x;
    }
    return p1->y < p2->y;
}

bool compare_points_by_angle(const Point* p1, const Point* p2) {
    double ccw_value = ccw(&first_point, p1, p2);
    if (ccw_value == 0) {
        return compute_distance(&first_point, p1) < compute_distance(&first_point, p2);
    }
    return ccw_value > 0;
}

void compute_hull(Point* points) {
    int size = point_size(points);
    int min_index = 0;

    for (int i = 1; i < size; i++) {
        if (compare_points_by_yx(&points[min_index], &points[i])) {
            min_index = i;
        }
    }

    sort(points, points + size, compare_points_by_angle);
    first_point = points[0];
    sort(points + 1, points + size, compare_points_by_angle);

    int m = 1;
    for (int i = 2; i < point_size(points); i++) {
      while (m > 0 && ccw(&points[m - 1], &points[m], &points[i]) <= 0) {
        m--;
      }

      m++;
      points[m].x = points[i].x;
      points[m].y = points[i].y;
    }
}

void analyze_hull(Point* points) {
    int size = point_size(points);
    int count = 0;
    int index = 0;
    int i = 0;

    while (i < size) {
        if (ccw(&points[index], &points[i], &points[i + 1]) == 0) {
            count++;
        }
        else {
            index = i + 1;
        }
        i++;
    }

    printf("%d\n", count);
}

double compute_hull_size(Point* points) {
    int size = point_size(points);
    double sum = 0;

    for (int i = 0; i < size - 1; i++) {
        sum += compute_distance(&points[i], &points[i + 1]);
    }

    return sum;
}