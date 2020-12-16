#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_FILE_NUM 677
#define GetIndex(x) (x - 'a')
#define INSERT_COST 1
#define DELETE_COST 1
#define SUBSTITUTE_COST 1
#define TRANSPOSE_COST 1

typedef struct trieNode
{
    int flag;
    struct trieNode *subtree[26];
} TRIE;

typedef struct
{
    char *word;
    int edit_dist;
} WORD;

typedef struct
{
    int last;
    int capacity;
    WORD **array;
} HEAP;

TRIE *CreateTrieNode(void)
{
    TRIE *temp = (TRIE *)malloc(sizeof(TRIE));

    if (temp == NULL)
    {
        printf("No available memory!\n");
        assert(100);
    }

    temp->flag = 0;
    memset(temp->subtree, 0, sizeof(temp->subtree));

    return temp;
}

int TraverseTrie(TRIE *root, char *query)
{
    if (*query == '\0')
    {
        if (root->flag)
            return 1;

        root->flag = 1;
        return 0;
    }

    int index = GetIndex(*query);
    if (root->subtree[index] == NULL)
        root->subtree[index] = CreateTrieNode();

    return TraverseTrie(root->subtree[index], query + 1);
}

void DestroyTrie(TRIE *root) {
    if (root == NULL)
        return;

    for (int i = 0 ; i < 26; i++)
        DestroyTrie(root->subtree[i]);
    
    free(root);
}

WORD *CreateWord(char *str, int edit_dist)
{
    WORD *temp = (WORD *)malloc(sizeof(WORD));
    if (temp == NULL)
    {
        printf("No available Memory!\n");
        assert(100);
    }

    temp->word = strdup(str);
    temp->edit_dist = edit_dist;

    return temp;
}

HEAP *CreateHeap(void)
{
    HEAP *temp = (HEAP *)malloc(sizeof(HEAP));

    if (temp == NULL)
    {
        printf("No available memory!\n");
        assert(100);
    }

    temp->last = -1;
    temp->capacity = 100;
    temp->array = (WORD **)malloc(sizeof(WORD *) * temp->capacity);

    if (temp->array == NULL)
    {
        printf("No available memory!\n");
        assert(100);
    }

    return temp;
}

void ReHeapUp(HEAP *heap)
{
    int index = heap->last;

    while (index != 0)
    {
        int parent = (index - 1) / 2;

        if (heap->array[index]->edit_dist < heap->array[parent]->edit_dist)
        {
            WORD *temp = heap->array[index];
            heap->array[index] = heap->array[parent];
            heap->array[parent] = temp;

            index = parent;
        }

        else
            break;
    }
}

void InsertHeap(HEAP *heap, WORD *word)
{
    (heap->last)++;
    if (heap->last == heap->capacity)
    {
        heap->capacity += 100;
        heap->array = (WORD **)realloc(heap->array, sizeof(WORD *) * heap->capacity);

        if (heap->array == NULL)
        {
            printf("No available memory!\n");
            assert(100);
        }
    }

    heap->array[heap->last] = word;
    ReHeapUp(heap);
}

void ReHeapDown(HEAP *heap) {
    int index = 0;

    while (index * 2 + 1 <= heap->last) {
        WORD *left = heap->array[index * 2 + 1], *right = NULL;
        int smallIndex = index * 2 + 1;

        if (index * 2 + 2 <= heap->last)
            right = heap->array[index * 2 + 2];

        if (right != NULL && right->edit_dist < left->edit_dist)
            smallIndex = index * 2 + 2;

        if (heap->array[index]->edit_dist > heap->array[smallIndex]->edit_dist) {
            WORD *temp = heap->array[index];
            heap->array[index] = heap->array[smallIndex];
            heap->array[smallIndex] = temp;

            index = smallIndex;
        }

        else
            return;
        
    }
}

WORD *DeleteHeap(HEAP *heap) {
    if (heap->last == -1)
        return NULL;

    WORD *temp = heap->array[0];
    heap->array[0] = heap->array[heap->last];

    (heap->last)--;

    ReHeapDown(heap);

    return temp;
}

void DestroyHeap(HEAP *heap) {
    while (1) {
        WORD *temp = DeleteHeap(heap);
        if (temp == NULL)
            break;
        
        free(temp->word);
        free(temp);
    }
    free(heap->array);
    free(heap);
}

int GetEditDist(char *query, char *candidate)
{
    int query_len = strlen(query), candidate_len = strlen(candidate);
    int dist[query_len + 1][candidate_len + 1];

    dist[0][0] = 0;
    for (int i = 1; i <= query_len; i++)
        dist[i][0] = i;

    for (int i = 1; i <= candidate_len; i++)
        dist[0][i] = i;

    for (int i = 1; i <= query_len; i++)
    {
        for (int j = 1; j <= candidate_len; j++)
        {
            dist[i][j] = dist[i][j - 1] + INSERT_COST;

            if (dist[i][j] > dist[i - 1][j] + DELETE_COST)
                dist[i][j] = dist[i - 1][j] + DELETE_COST;

            if (dist[i][j] > dist[i - 1][j - 1] + SUBSTITUTE_COST)
                dist[i][j] = dist[i - 1][j - 1] + SUBSTITUTE_COST;

            if (i > 1 && j > 1 && query[i - 1] == candidate[j - 2] && query[i - 2] == candidate[j - 1] && dist[i][j] > dist[i - 2][j - 2] + TRANSPOSE_COST)
                dist[i][j] = dist[i - 2][j - 2] + TRANSPOSE_COST;

            if (query[i - 1] == candidate[j - 1] && dist[i][j] > dist[i - 1][j - 1])
                dist[i][j] = dist[i - 1][j - 1];
        }
    }

    return dist[query_len][candidate_len];
}

int ReadIndexFile(TRIE *trie, HEAP *heap, char *filename, char *query)
{
    char buffer[1024] = "";
    FILE *fp;

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("No %s file!", filename);
        return -1;
    }

    while (fgets(buffer, sizeof(buffer), fp))
    {
        buffer[strlen(buffer) - 1] = '\0';

        if (TraverseTrie(trie, buffer))
            continue;

        int edit_distance = GetEditDist(query, buffer);

        WORD *newWord = CreateWord(buffer, edit_distance);

        InsertHeap(heap, newWord);
    }

    fclose(fp);
}

int BigramIndexing(TRIE *trie, HEAP *heap, char *query)
{
    int len = strlen(query), check[MAX_FILE_NUM] = {0};

    for (int i = 0; i < len - 1; i++)
    {
        if ((query[i] < 'a' || query[i] > 'z') || (query[i + 1] < 'a' || query[i] + 1 > 'z'))
        {
            printf("Word should contain only small alphabet!\n");
            return 0;
        }

        int numIndex = (query[i] - 'a') * 26 + (query[i + 1] - 'a');
        if (check[numIndex])
            continue;

        char filename[20] = "";
        sprintf(filename, "./index/%c%c.txt", query[i], query[i + 1]);

        if (ReadIndexFile(trie, heap, filename, query) == -1)
            return 0;
    }

    if (strlen(query) == 1) {
        if ((*query < 'a' || *query > 'z'))
        {
            printf("Word should contain only small alphabet!\n");
            return 0;
        }

        char filename[20] = "./index/a_z.txt";

        if (ReadIndexFile(trie, heap, filename, query) == -1)
            return 0;
    }

    return 1;
}

void PrintResult(HEAP *heap) {
    printf("Did you mean?\t\t(Edit distance)\n");

    for (int i = 0; i < 10; i++) {
        WORD *word = DeleteHeap(heap);
        printf("%-30s(%d)\n", word->word, word->edit_dist);

        free(word->word);
        free(word);
    }
}

int main()
{
    char query[1024];
    TRIE *trie = CreateTrieNode();
    HEAP *heap = CreateHeap();

    printf("Enter your word: ");
    scanf("%s", query);

    if (BigramIndexing(trie, heap, query))
        PrintResult(heap);

    DestroyHeap(heap);
    DestroyTrie(trie);

    return 0;
}