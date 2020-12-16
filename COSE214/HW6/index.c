#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>

#define MAX_FILE_NUM 677

typedef struct
{
    int *array;
    int cnt;
    int capacity;
} BIGRAM_INDEX;

BIGRAM_INDEX *CreateIndexArray(void)
{
    BIGRAM_INDEX *temp = (BIGRAM_INDEX *)malloc(sizeof(BIGRAM_INDEX) * MAX_FILE_NUM);
    if (temp == NULL)
    {
        printf("No available memory!\n");
        assert(100);
    }

    for (int i = 0; i < MAX_FILE_NUM; i++)
    {
        temp[i].cnt = 0;
        temp[i].capacity = 100;
        temp[i].array = (int *)malloc(sizeof(int) * temp[i].capacity);
    }

    return temp;
}

void DestroyIndexArray(BIGRAM_INDEX *index) {
    for (int i = 0; i < MAX_FILE_NUM; i++)
        free(index[i].array);

    free(index);
}

void DestroyWords(char **words, int *words_cnt) {
    for (int i = 0; i < *words_cnt; i++)
        free(words[i]);

    free(words);
}

void BigramIndexing(FILE *fp, char ***words, int *words_cnt, int *words_capacity, BIGRAM_INDEX *index) {
    char buffer[100] = "";

    while (fgets(buffer, sizeof(buffer), fp))
    {
        if (*words_cnt == *words_capacity)
        {
            (*words_capacity) += 10000;
            *words = (char **)realloc(*words, sizeof(char *) * (*words_capacity));

            if (words == NULL)
            {
                printf("No available memory!\n");
                assert(100);
            }
        }
        (*words)[*words_cnt] = strdup(buffer);

        if (strlen(buffer) == 2) {
            if (index[MAX_FILE_NUM - 1].cnt == index[MAX_FILE_NUM - 1].capacity)
            {
                index[MAX_FILE_NUM - 1].capacity += 100;
                index[MAX_FILE_NUM - 1].array = (int *)realloc(index[MAX_FILE_NUM - 1].array, sizeof(int) * index[MAX_FILE_NUM - 1].capacity);

                if (index[MAX_FILE_NUM - 1].array == NULL)
                {
                    printf("No available memory!\n");
                    assert(100);
                }
            }

            index[MAX_FILE_NUM - 1].array[index[MAX_FILE_NUM - 1].cnt++] = (*words_cnt)++;

            continue;
        }

        int check[MAX_FILE_NUM] = {0};
        for (int i = 0; i < strlen(buffer) - 2; i++)
        {
            int j = (buffer[i] - 'a') * 26 + (buffer[i + 1] - 'a');
            if (check[j])
                continue;
            check[j] = 1;

            if (index[j].cnt == index[j].capacity)
            {
                index[j].capacity += 100;
                index[j].array = (int *)realloc(index[j].array, sizeof(int) * index[j].capacity);

                if (index[j].array == NULL)
                {
                    printf("No available memory!\n");
                    assert(100);
                }
            }

            index[j].array[index[j].cnt++] = (*words_cnt);
        }

        (*words_cnt)++;
    }
}

void WriteFile(char **words, BIGRAM_INDEX *index) {
    for (int i = 0; i < MAX_FILE_NUM; i++) {
        char filename[20] = "";

        if (i != MAX_FILE_NUM - 1)
            sprintf(filename, "./index/%c%c.txt", i / 26 + 'a', i % 26 + 'a');

        else
            sprintf(filename, "./index/a_z.txt");

        FILE *fp = fopen(filename, "w");

        for (int j = 0; j < index[i].cnt; j++)
            fprintf(fp, "%s", words[index[i].array[j]]);

        fclose(fp);
    }
}

int main(int argc, char **argv)
{
    mkdir("./index", 0755);

    if (argc != 2)
    {
        fprintf(stderr, "%s words-file\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Error: cannot open file [%s]\n", argv[1]);
        return 1;
    }

    int words_capacity = 10000, words_cnt = 0;
    char **words = (char **)malloc(sizeof(char *) * words_capacity);

    if (words == NULL)
    {
        printf("No available memory!\n");
        assert(100);
    }

    BIGRAM_INDEX *index = CreateIndexArray();

    BigramIndexing(fp, &words, &words_cnt, &words_capacity, index);

    fclose(fp);

    WriteFile(words, index);

    DestroyIndexArray(index);
    DestroyWords(words, &words_cnt);

    return 0;
}