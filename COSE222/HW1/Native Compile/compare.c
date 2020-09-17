#define min(x,y) ((x) < (y) ? (x) : (y))

int compare (int b, int c) {
	int a;
	a = min(b, c);
	return a;
}
