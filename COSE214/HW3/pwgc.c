#include <stdio.h>
#include <stdlib.h>

#define PEASANT 8
#define WOLF 4
#define GOAT 2
#define CABBAGE 1

// 주어진 상태 state의 이름(마지막 4비트)을 화면에 출력
// 예) state가 7(0111)일 때, "<0111>"을 출력
static void print_statename(FILE *fp, int state) {
    int num[4] = {0};

    for (int i = 0; i < 4; i++) {
        num[i] = state % 2;
        state /= 2;
    }

    fprintf(fp, "<%d%d%d%d>", num[3], num[2], num[1], num[0]);
}

// 주어진 상태 state에서 농부, 늑대, 염소, 양배추의 상태를 각각 추출하여 p, w, g, c에 저장
// 예) state가 7(0111)일 때, p = 0, w = 1, g = 1, c = 1
static void get_pwgc(int state, int *p, int *w, int *g, int *c) {
    *c = state % 2;
    state /= 2;

    *g = state % 2;
    state /= 2;

    *w = state % 2;
    state /= 2;

    *p = state % 2;
}

// 허용되지 않는 상태인지 검사
// 예) 농부없이 늑대와 염소가 같이 있는 경우 / 농부없이 염소와 양배추가 같이 있는 경우
// return value: 1 허용되지 않는 상태인 경우, 0 허용되는 상태인 경우
static int is_dead_end(int state) {
    if (state == 3 || state == 6 || state == 7 || state == 8 || state == 9 || state == 12)
        return 1;

    return 0;
}

// state1 상태에서 state2 상태로의 전이 가능성 점검
// 농부 또는 농부와 다른 하나의 아이템이 강 반대편으로 이동할 수 있는 상태만 허용
// 허용되지 않는 상태(dead-end)로의 전이인지 검사
// return value: 1 전이 가능한 경우, 0 전이 불이가능한 경우
static int is_possible_transition(int state1, int state2) {
    if (is_dead_end(state1) || is_dead_end(state2))
        return 0;

    int transition = state1 ^state2;

    if (!(transition & PEASANT))
        return 0;

    int cnt = 0, object_state[4];
    get_pwgc(state1, &object_state[0], &object_state[1], &object_state[2], &object_state[3]);

    if (transition & WOLF) {
        if (object_state[0] != object_state[1])
            return 0;

        cnt++;
    }

    if (transition & GOAT) {
        if (object_state[0] != object_state[2])
            return 0;

        cnt++;
    }

    if (transition & CABBAGE) {
        if (object_state[0] != object_state[3])
            return 0;

        cnt++;
    }

    if (cnt > 1)
        return 0;

    return 1;
}

// 상태 변경: 농부 이동
// return value : 새로운 상태
static int changeP(int state) {
    int next_state = state ^ PEASANT;

    if (is_dead_end(next_state)) {
        printf("\tnext state ");
        print_statename(stdout, next_state);
        printf(" is dead-end\n");
        return -1;
    }

    return next_state;
}

// 상태 변경: 농부, 늑대 이동
// return value : 새로운 상태, 상태 변경이 불가능한 경우: -1
static int changePW(int state) {
    int object_state[4];
    get_pwgc(state, &object_state[0], &object_state[1], &object_state[2], &object_state[3]);

    if (object_state[0] != object_state[1])
        return -1;

    int next_state = state ^(PEASANT | WOLF);

    if (is_dead_end(next_state)) {
        printf("\tnext state ");
        print_statename(stdout, next_state);
        printf(" is dead-end\n");
        return -1;
    }

    return next_state;
}

// 상태 변경: 농부, 염소 이동
// return value : 새로운 상태, 상태 변경이 불가능한 경우: -1
static int changePG(int state) {
    int object_state[4];
    get_pwgc(state, &object_state[0], &object_state[1], &object_state[2], &object_state[3]);

    if (object_state[0] != object_state[2])
        return -1;

    int next_state = state ^(PEASANT | GOAT);

    if (is_dead_end(next_state)) {
        printf("\tnext state ");
        print_statename(stdout, next_state);
        printf(" is dead-end\n");
        return -1;
    }

    return next_state;
}

// 상태 변경: 농부, 양배추 이동
// return value : 새로운 상태, 상태 변경이 불가능한 경우: -1
static int changePC(int state) {
    int object_state[4];
    get_pwgc(state, &object_state[0], &object_state[1], &object_state[2], &object_state[3]);

    if (object_state[0] != object_state[3])
        return -1;

    int next_state = state ^(PEASANT | CABBAGE);

    if (is_dead_end(next_state)) {
        printf("\tnext state ");
        print_statename(stdout, next_state);
        printf(" is dead-end\n");
        return -1;
    }

    return next_state;
}

// 주어진 state가 이미 방문한 상태인지 검사
// return value : 1 visited, 0 not visited
static int is_visited(int visited[], int level, int state) {
    for (int i = 0; i <= level; i++) {
        if (visited[i] == state) {
            printf("\tnext state ");
            print_statename(stdout, state);
            printf(" has been visited\n");
            return 1;
        }
    }

    return 0;
}

// 방문한 상태들을 차례로 화면에 출력
static void print_states(int visited[], int count) {
    for (int i = 0; i <= count; i++) {
        print_statename(stdout, visited[i]);
        printf("\n");
    }
    printf("\n");
}

// recursive function
static void dfs_main(int state, int goal_state, int level, int visited[]) {
    visited[level] = state;

    printf("cur state is ");
    print_statename(stdout, state);
    printf(" (level %d)\n", level);

    if (state == goal_state) {
        printf("Goal-state found!\n");
        print_states(visited, level);
        return;
    }

    int (*next_state_functions[4])(int);

    next_state_functions[0] = changeP;
    next_state_functions[1] = changePW;
    next_state_functions[2] = changePG;
    next_state_functions[3] = changePC;

    for (int i = 0; i < 4; i++) {
        int next_state = next_state_functions[i](state);

        if (next_state != -1) {
            if (is_visited(visited, level, next_state) == 0) {
                dfs_main(next_state, goal_state, level + 1, visited);
                printf("back to ");
                print_statename(stdout, state);
                printf(" (level %d)\n", level);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// 상태들의 인접 행렬을 구하여 graph에 저장
// 상태간 전이 가능성 점검
// 허용되지 않는 상태인지 점검
void make_adjacency_matrix(int graph[][16]) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if (is_possible_transition(i, j))
                graph[i][j] = 1;

            else
                graph[i][j] = 0;
        }
    }
}

// 인접행렬로 표현된 graph를 화면에 출력
void print_graph(int graph[][16], int num) {
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            printf("%d ", graph[i][j]);
        }

        printf("\n");
    }
}

// 주어진 그래프(graph)를 .net 파일로 저장
// pgwc.net 참조
void save_graph(char *filename, int graph[][16], int num) {
    FILE *f = fopen(filename, "w");

    fprintf(f, "*Vertices %d\n", num);
    for (int i = 0; i < num; i++) {
        fprintf(f, "%d \"", i + 1);
        print_statename(f, i);
        fprintf(f, "\"\n");
    }

    fprintf(f, "*Edges\n");
    for (int i = 0; i < num; i++) {
        for (int j = i; j < num; j++) {
            if (graph[i][j])
                fprintf(f, "%3d %3d\n", i + 1, j + 1);
        }
    }

    fclose(f);
}

////////////////////////////////////////////////////////////////////////////////
// 깊이 우선 탐색 (초기 상태 -> 목적 상태)
void depth_first_search(int init_state, int goal_state) {
    int level = 0;
    int visited[16] = {0,}; // 방문한 정점을 저장

    dfs_main(init_state, goal_state, level, visited);
}

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv) {
    int graph[16][16] = {0,};

    // 인접 행렬 만들기
    make_adjacency_matrix(graph);

    // 인접 행렬 출력 (only for debugging)
    // print_graph(graph, 16);

    // .net 파일 만들기
    save_graph("pwgc.net", graph, 16);

    // 깊이 우선 탐색
    depth_first_search(0, 15); // initial state, goal state

    return 0;
}
