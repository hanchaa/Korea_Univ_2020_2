#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>

typedef struct
{
    int *array;
    int cnt;
    int capacity;
} BIGRAM_INDEX;

BIGRAM_INDEX *create_index_array()
{
    BIGRAM_INDEX *temp = (BIGRAM_INDEX *)malloc(sizeof(BIGRAM_INDEX) * 676);
    if (temp == NULL)
    {
        printf("No available memory!\n");
        assert(100);
    }

    for (int i = 0; i < 676; i++)
    {
        temp[i].cnt = 0;
        temp[i].capacity = 100;
        temp[i].array = (int *)malloc(sizeof(int) * temp[i].capacity);
    }

    return temp;
}

void destroy_index_array(BIGRAM_INDEX *index) {
    for (int i = 0; i < 676; i++)
        free(index[i].array);

    free(index);
}

void destroy_words(char **words, int *words_cnt) {
    for (int i = 0; i < *words_cnt; i++)
        free(words[i]);

    free(words);
}

void bigram_indexing(FILE *fp, char ***words, int *words_cnt, int *words_capacity, BIGRAM_INDEX *index) {
    char buffer[100] = "";

    while (fgets(buffer, sizeof(buffer), fp))
    {
        if (strlen(buffer) == 2)
            continue;

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

        int check[676] = {0};
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

        (*words)[(*words_cnt)++] = strdup(buffer);
    }
}

void write_file(char **words, BIGRAM_INDEX *index) {
    for (int i = 0; i < 676; i++) {
        char filename[20] = "";
        sprintf(filename, "./index/%c%c.txt", i / 26 + 'a', i % 26 + 'a');

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

    BIGRAM_INDEX *index = create_index_array();

    bigram_indexing(fp, &words, &words_cnt, &words_capacity, index);

    fclose(fp);

    write_file(words, index);

    destroy_index_array(index);
    destroy_words(words, &words_cnt);

    return 0;
}