//#define BINARY_MODE

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct Node 
{ 
	unsigned char	data;	// 문자	
	int		freq; 			// 빈도
	struct	Node *left;		// 왼쪽 서브트리 포인터
	struct	Node *right; 	// 오른쪽 서브트리 포인터
} tNode;

////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	int	last;		// 힙에 저장된 마지막 element의 index
	int	capacity;	// heapArr의 크기
	tNode **heapArr;
} HEAP;

// 힙 생성
// 배열을 위한 메모리 할당 (capacity)
// last = -1
HEAP *heapCreate( int capacity);

// 최소힙 유지
static void _reheapUp( HEAP *heap, int index);

// 힙에 원소 삽입
// _reheapUp 함수 호출
int heapInsert( HEAP *heap, tNode *data);

// 최소힙 유지
static void _reheapDown( HEAP *heap, int index);

// 최소값 제거
// _reheapDown 함수 호출
tNode *heapDelete( HEAP *heap);

// 힙 메모리 해제
void heapDestroy( HEAP *heap);

////////////////////////////////////////////////////////////////////////////////
// 파일에 속한 각 문자(바이트)의 빈도 저장
// return value : 파일에서 읽은 바이트 수
int read_chars( FILE *fp, int *ch_freq);

// 허프만 코드에 대한 메모리 해제
void free_huffman_code( char *codes[]);

// 새로운 노드를 생성
// 좌/우 subtree가 NULL이고 문자(data)와 빈도(freq)가 저장됨
// return value : 노드의 포인터
tNode *newNode(char data, int freq);

// 허프만 트리를 생성
// 1. capacity 256 짜리 빈(empty) 힙 생성
// 2. 개별 알파벳에 대한 노드 생성
// 3. 힙에 삽입 (minheap 구성)
// 4. 2개의 최소값을 갖는 트리 추출
// 5. 두 트리를 결합 후 새 노드에 추가
// 6. 새 트리를 힙에 삽입
// 7. 힙에 한개의 노드가 남을 때까지 반복
// return value: 트리의 root 노드의 포인터
tNode *make_huffman_tree( int *ch_freq);

// 허프만 트리를 순회하며 허프만 코드를 생성하여 codes에 저장
// leaf 노드에서만 코드를 생성
// strdup 함수 사용함
void traverse_tree( tNode *root, char *code, int depth, char *codes[]);

// 허프만 트리로부터 허프만 코드를 생성
// traverse_tree 함수 호출
void make_huffman_code( tNode *root, char *codes[]);

// 트리 메모리 해제
void destroyTree( tNode *root);

// 텍스트 파일을 허프만 코드를 이용하여 바이너리 파일로 인코딩
// return value : 인코딩된 파일의 바이트 수
int encoding( char *codes[], FILE *infp, FILE *outfp);
int encoding_binary( char *codes[], FILE *infp, FILE *outfp);

// 바이너리 파일을 허프만 트리를 이용하여 텍스트 파일로 디코딩
void decoding( tNode *root, FILE *infp, FILE *outfp);
void decoding_binary( tNode *root, FILE *infp, FILE *outfp);

////////////////////////////////////////////////////////////////////////////////
// 문자별 빈도 출력 (for debugging)
void print_char_freq( int *ch_freq)
{
	int i;

	for (i = 0; i < 256; i++)
	{
		printf( "%d\t%d\n", i, ch_freq[i]); // 문자인덱스, 빈도
	}
}

////////////////////////////////////////////////////////////////////////////////
// 문자별 빈도를 이용하여 허프만 트리와 허프만 코드를 생성
// return value : 허프만 트리의 root node
tNode *run_huffman( int *ch_freq, char *codes[])
{
	tNode *root;
	//root = make_huffman_tree( ch_freq);
	
	//make_huffman_code( root, codes);
	
	return root;
}

////////////////////////////////////////////////////////////////////////////////
// 허프만 코드를 화면에 출력
void print_huffman_code( char *codes[])
{
	int i;
	
	for (i = 0; i < 256; i++)
	{
		printf( "%d\t%s\n", i, codes[i]);
	}
}

////////////////////////////////////////////////////////////////////////////////
// argv[1] : 입력 텍스트 파일
// argv[2] : 바이너리 코드 (encoding 결과) 
// argv[3] : 출력 텍스트 파일 (decoding 결과)
int main( int argc, char **argv)
{
	FILE *fp;
	FILE *infp, *outfp;
	int ch_freq[256] = {0,}; // 문자별 빈도
	char *codes[256]; // 문자별 허프만 코드 (ragged 배열)
	tNode *huffman_tree; // 허프만 트리
	
	if (argc != 4)
	{
		fprintf( stderr, "%s input-file encoded-file decoded-file\n", argv[0]);
		return 1;
	}

	////////////////////////////////////////
	// 입력 텍스트 파일
	fp = fopen( argv[1], "rt");
	if (fp == NULL)
	{
		fprintf( stderr, "Error: cannot open file [%s]\n", argv[1]);
		return 1;
	}

	// 텍스트 파일로부터 문자별 빈도 저장
	//int num_bytes = read_chars( fp, ch_freq);

	fclose( fp);

	// 문자별 빈도 출력 (for debugging)
	//print_char_freq( ch_freq);
	
	// 허프만 코드/트리 생성
	//huffman_tree = run_huffman( ch_freq, codes);
	
	// 허프만 코드 출력 (stdout)
	//print_huffman_code( codes);

	////////////////////////////////////////
	// 입력: 텍스트 파일
	infp = fopen( argv[1], "rt");
	
#ifdef BINARY_MODE
	// 출력: 바이너리 코드
	outfp = fopen( argv[2], "wb");
#else
	// 출력: 바이너리 코드
	outfp = fopen( argv[2], "wt");
#endif

	// 허프만코드를 이용하여 인코딩(압축)
	//int encoded_bytes = encoding( codes, infp, outfp);

#ifdef BINARY_MODE
	//int encoded_bytes = encoding_binary( codes, infp, outfp);
#else
	//int encoded_bytes = encoding( codes, infp, outfp);
#endif

	// 허프만 코드 메모리 해제
	//free_huffman_code( codes);
	
	fclose( infp);
	fclose( outfp);

	////////////////////////////////////////
	// 입력: 바이너리 코드
#ifdef BINARY_MODE
	infp = fopen( argv[2], "rb");
#else
	infp = fopen( argv[2], "rt");
#endif

	// 출력: 텍스트 파일
	outfp = fopen( argv[3], "wt");

	// 허프만 트리를 이용하여 디코딩
#ifdef BINARY_MODE
	//decoding_binary( huffman_tree, infp, outfp);
#else
	//decoding( huffman_tree, infp, outfp);
#endif

	// 허프만 트리 메모리 해제
	//destroyTree( huffman_tree);

	fclose( infp);
	fclose( outfp);

	////////////////////////////////////////
	//printf( "# of bytes of the original text = %d\n", num_bytes);
	//printf( "# of bytes of the compressed text = %d\n", encoded_bytes);
	//printf( "compression ratio = %.2f\n", ((float)num_bytes - encoded_bytes) / num_bytes * 100);
	
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
// 힙의 내용 출력 (for debugging)
void heapPrint( HEAP *heap)
{
	int i;
	tNode **p = heap->heapArr;
	int last = heap->last;
	
	for( i = 0; i <= last; i++)
	{
		printf("[%d]%c(%6d)\n", i, p[i]->data, p[i]->freq);
	}
	printf( "\n");
}

////////////////////////////////////////////////////////////////////////////////
// 힙 생성
// 배열을 위한 메모리 할당 (capacity)
// last = -1
HEAP *heapCreate( int capacity)
{
	HEAP *heap;
	
	heap = (HEAP *)malloc( sizeof(HEAP));
	if (!heap) return NULL;

	heap->last = -1;
	heap->capacity = capacity;
	heap->heapArr = (tNode **)malloc( sizeof(tNode *) * capacity);
	if (heap->heapArr == NULL)
	{
		fprintf( stderr, "Error : not enough memory!\n");
		free( heap);
		return NULL;
	}
	return heap;
}

////////////////////////////////////////////////////////////////////////////////
// 최소힙 유지
static void _reheapUp( HEAP *heap, int index)
{
	tNode **arr = heap->heapArr;
	int parent;
	
	while(1)
	{
		if (index == 0) return; // root node
		
		parent = (index - 1) / 2;
		
		if (arr[index]->freq < arr[parent]->freq) // exchange (for minheap)
		{
			tNode *temp = arr[index];
			arr[index] = arr[parent];
			arr[parent] = temp;
			
			index = parent;
		}
		else return;
	}
}

////////////////////////////////////////////////////////////////////////////////
// 힙에 원소 삽입
// _reheapUp 함수 호출
int heapInsert( HEAP *heap, tNode *data)
{
	if (heap->last == heap->capacity - 1)
		return 0;
	
	(heap->last)++;
	(heap->heapArr)[heap->last] = data;
	
	_reheapUp( heap, heap->last);
	
	return 1;
}

////////////////////////////////////////////////////////////////////////////////
// 최소힙 유지
static void _reheapDown( HEAP *heap, int index)
{
	tNode **arr = heap->heapArr;
	tNode *leftData;
	tNode *rightData;
	int noright = 0;
	int largeindex; // index of left or right child with large key
	
	while(1)
	{
		if ((index * 2 + 1) > heap->last) return; // leaf node (there is no left subtree)
		
		leftData = arr[index * 2 + 1];
		if (index * 2 + 2 <= heap->last) rightData = arr[index * 2 + 2];
		else noright = 1;
		
		if (noright || leftData->freq < rightData->freq) largeindex = index * 2 + 1; // left child
		else largeindex = index * 2 + 2; // right child
		
		if (arr[index]->freq > arr[largeindex]->freq) // exchange (for minheap)
		{
			tNode *temp = arr[index];
			arr[index] = arr[largeindex];
			arr[largeindex] = temp;
			
			index = largeindex;
			
			noright = 0;
		}
		else return;
	}
}

////////////////////////////////////////////////////////////////////////////////
// 최소값 제거
// _reheapDown 함수 호출
tNode *heapDelete( HEAP *heap)
{
	if (heap->last == -1) return NULL; // empty heap
	
	tNode *data = heap->heapArr[0];
	heap->heapArr[0] = heap->heapArr[heap->last];
	
	(heap->last)--;
	
	_reheapDown( heap, 0);
	
	return data;
}

////////////////////////////////////////////////////////////////////////////////
// 힙 메모리 해제
void heapDestroy( HEAP *heap)
{
	free(heap->heapArr);
	free(heap);
}

