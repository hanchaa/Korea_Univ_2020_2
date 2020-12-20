#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>

#define MAX_2GRAM_INDEX 676
#define MAX_1GRAM_INDEX 26

typedef struct
{
    int *array;
    int cnt;
    int capacity;
} BIGRAM_INDEX;

BIGRAM_INDEX *CreateIndexArray(void)
{
    BIGRAM_INDEX *temp = (BIGRAM_INDEX *)malloc(sizeof(BIGRAM_INDEX) * (MAX_2GRAM_INDEX + MAX_1GRAM_INDEX));
    if (temp == NULL)
    {
        printf("No available memory!\n");
        assert(100);
    }

    for (int i = 0; i < MAX_2GRAM_INDEX + MAX_1GRAM_INDEX; i++)
    {
        temp[i].cnt = 0;
        temp[i].capacity = 100;
        temp[i].array = (int *)malloc(sizeof(int) * temp[i].capacity);

        if (temp[i].array == NULL) {
            printf("No available memory!\n");
            assert(100);
        }
    }

    return temp;
}

void DestroyIndexArray(BIGRAM_INDEX *bigram)
{
    for (int i = 0; i < MAX_2GRAM_INDEX + MAX_1GRAM_INDEX; i++)
        free(bigram[i].array);

    free(bigram);
}

void DestroyWords(char **words, int *words_cnt)
{
    for (int i = 0; i < *words_cnt; i++)
        free(words[i]);

    free(words);
}

void CheckCapacity(BIGRAM_INDEX *bigram, int idx)
{
    if (bigram[idx].cnt == bigram[idx].capacity)
    {
        bigram[idx].capacity += 100;
        bigram[idx].array = (int *)realloc(bigram[idx].array, sizeof(int) * bigram[idx].capacity);

        if (bigram[idx].array == NULL)
        {
            printf("No available memory!\n");
            assert(100);
        }
    }
}

void BigramIndexing(FILE *fp, char ***words, int *words_cnt, int *words_capacity, BIGRAM_INDEX *bigram)
{
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

        if (strlen(buffer) == 2)
        {
            CheckCapacity(bigram, MAX_2GRAM_INDEX + *buffer - 'a');

            bigram[MAX_2GRAM_INDEX + *buffer - 'a'].array[bigram[MAX_2GRAM_INDEX + *buffer - 'a'].cnt++] = *words_cnt;

            (*words_cnt)++;
            continue;
        }

        if (strlen(buffer) == 3)
        {
            int idx = (buffer[0] - 'a') * 26 + (buffer[1] - 'a'), first_alphabet_idx = MAX_2GRAM_INDEX + buffer[0] - 'a', second_alphabet_idx = MAX_2GRAM_INDEX + buffer[1] - 'a';

            CheckCapacity(bigram, first_alphabet_idx);
            bigram[first_alphabet_idx].array[bigram[first_alphabet_idx].cnt++] = (*words_cnt);

            if (first_alphabet_idx != second_alphabet_idx)
            {
                CheckCapacity(bigram, second_alphabet_idx);
                bigram[second_alphabet_idx].array[bigram[second_alphabet_idx].cnt++] = (*words_cnt);
            }

            CheckCapacity(bigram, idx);
            bigram[idx].array[bigram[idx].cnt++] = (*words_cnt);

            (*words_cnt)++;
            continue;
        }

        int check[MAX_2GRAM_INDEX] = {0};
        for (int i = 0; i < strlen(buffer) - 2; i++)
        {
            int idx = (buffer[i] - 'a') * 26 + (buffer[i + 1] - 'a');
            if (check[idx])
                continue;
            check[idx] = 1;

            CheckCapacity(bigram, idx);
            bigram[idx].array[bigram[idx].cnt++] = (*words_cnt);
        }

        (*words_cnt)++;
    }
}

void WriteFile(char **words, BIGRAM_INDEX *bigram)
{
    for (int i = 0; i < MAX_2GRAM_INDEX + MAX_1GRAM_INDEX; i++)
    {
        char filename[20] = "";

        if (i < MAX_2GRAM_INDEX)
            sprintf(filename, "./index/%c%c.txt", i / 26 + 'a', i % 26 + 'a');

        else
            sprintf(filename, "./index/%c.txt", i - MAX_2GRAM_INDEX + 'a');

        FILE *fp = fopen(filename, "w");

        for (int j = 0; j < bigram[i].cnt; j++)
            fprintf(fp, "%s", words[bigram[i].array[j]]);

        fclose(fp);
        printf("%s saved\n", filename);
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

    BIGRAM_INDEX *bigram = CreateIndexArray();

    printf("Start 2-gram indexing\n");
    BigramIndexing(fp, &words, &words_cnt, &words_capacity, bigram);
    printf("2-gram indexing done\n");

    fclose(fp);

    WriteFile(words, bigram);

    DestroyIndexArray(bigram);
    DestroyWords(words, &words_cnt);

    return 0;
}