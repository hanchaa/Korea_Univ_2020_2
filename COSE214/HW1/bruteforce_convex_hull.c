#include <stdlib.h> // atoi, rand, malloc, realloc
#include <stdio.h>
#include <time.h> //time

#define RANGE 10000

typedef struct {
    int x;
    int y;
} t_point;

typedef struct {
    t_point from;
    t_point to;
} t_line;

////////////////////////////////////////////////////////////////////////////////
void print_header(char *filename) {
    printf("#! /usr/bin/env Rscript\n");
    printf("png(\"%s\", width=700, height=700)\n", filename);

    printf("plot(1:%d, 1:%d, type=\"n\")\n", RANGE, RANGE);
}

////////////////////////////////////////////////////////////////////////////////
void print_footer(void) {
    printf("dev.off()\n");
}

////////////////////////////////////////////////////////////////////////////////
/*
#points
points(2247,7459)
points(616,2904)
points(5976,6539)
points(1246,8191)
*/
void print_points(t_point *points, int num_point) {
    if (points == NULL)
        return;

    for (int i = 0; i < num_point; i++)
        printf("points(%d,%d)\n", points[i].x, points[i].y);
}

/*
#line segments
segments(7107,2909,7107,2909)
segments(43,8,5,38)
segments(43,8,329,2)
segments(5047,8014,5047,8014)
*/
void print_line_segments(t_line *lines, int num_line) {
    if (lines == NULL)
        return;
    for (int i = 0; i < num_line; i++)
        printf("segments(%d,%d,%d,%d)\n", lines[i].from.x, lines[i].from.y, lines[i].to.x, lines[i].to.y);
}

// [input] points : set of points
// [input] num_point : number of points
// [output] num_line : number of line segments that forms the convex hull
// return value : set of line segments that forms the convex hull
t_line *convex_hull(t_point *points, int num_point, int *num_line) {
    if (points == NULL)
        return NULL;

    int line_size = 10;
    t_line *lines = (t_line *) malloc(line_size * sizeof(t_line));

    if (lines == NULL)
        return NULL;

    *num_line = 0;

    for (int i = 0; i < num_point; i++) {
        for (int j = i + 1; j < num_point; j++) {
            int v1 = points[j].x - points[i].x, v2 = points[j].y - points[i].y, k = 0;
            float flag = 0;

            for (k = 0; k < num_point; k++) {
                if (k == i || k == j)
                    continue;

                float temp = (float)(points[k].x - points[i].x) / v1 - (float)(points[k].y - points[i].y) / v2;

                if (flag == 0)
                    flag = temp;

                if (flag * temp < 0)
                    break;
            }

            if (k < num_point)
                continue;

            if (*num_line == line_size) {
                line_size *= 2;
                lines = (t_line *) realloc(lines, line_size * sizeof(t_line));

                if (lines == NULL)
                    return NULL;

                fprintf(stderr, "realloc(%d)\n", line_size);
            }

            lines[*num_line].from.x = points[i].x;
            lines[*num_line].from.y = points[i].y;
            lines[*num_line].to.x = points[j].x;
            lines[*num_line].to.y = points[j].y;

            (*num_line)++;
        }
    }

    return lines;
}

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
    int x, y;
    int num_point; // number of points
    int num_line;  // number of lines

    if (argc != 2) {
        printf("%s number_of_points\n", argv[0]);
        return 0;
    }

    num_point = atoi(argv[1]);
    if (num_point <= 0) {
        printf("The number of points should be a positive integer!\n");
        return 0;
    }

    t_point *points = (t_point *) malloc(num_point * sizeof(t_point));

    t_line *lines;

    // making n points
    srand(time(NULL));
    for (int i = 0; i < num_point; i++) {
        x = rand() % RANGE + 1; // 1 ~ RANGE random number
        y = rand() % RANGE + 1;

        points[i].x = x;
        points[i].y = y;
    }

    fprintf(stderr, "%d points created!\n", num_point);

    print_header("convex.png");

    print_points(points, num_point);

    lines = convex_hull(points, num_point, &num_line);

    fprintf(stderr, "%d lines created!\n", num_line);

    print_line_segments(lines, num_line);

    print_footer();

    free(points);
    free(lines);

    return 0;
}