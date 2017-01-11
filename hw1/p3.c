#include <stdio.h>
#include <stdlib.h>

/* https://en.wikipedia.org/wiki/Binary_heap */
void heapify(int *f, int n) {
	/* Your Code Here */
    int i, l, r, father, cur, temp;
    for(i = (n + 1) / 2; i >= 0; i --) {
        father = i;
        do {
            cur = father;
            l = 2 * cur + 1;
            r = 2 * cur + 2;
            if(l < n && f[l] > f[father]) father = l;
            if(r < n && f[r] > f[father]) father = r;
            temp = f[father];
            f[father] = f[cur];
            f[cur] = temp;
        } while(cur != father);
    }
    return;
}

int * allocate_array(int argc, char * argv[]) {
    int i;
    int *vec = malloc(sizeof(int) * (argc - 1));
	for(i = 1; i < argc; i++) vec[i - 1] = atoi(argv[i]);
    return vec;
}

int test_heap( int * f, int n) {
	int i;
	int child_A, child_B;

	for( i = 0; i < n; i++ )
	{
		child_A = ( 2 * i ) + 1;
		child_B = ( 2 * i ) + 2;

		if( child_A < n )
			if( f[i] < f[child_A] )
				return -1;
		
		if( child_B < n )
			if( f[i] < f[child_B] )
				return -1;
	}

	return 1;
}

int main(int argc, char * argv[]){
	int result;
	int i;
	int n = argc - 1;
	int * arr = allocate_array( argc, argv );

	heapify( arr, n );
	result = test_heap( arr, n );

	for( i = 0; i < n; i++ )
		printf("%d ", arr[i]);
	printf("\n");

	if( result == 1 )
		printf("Heap test success!\n");
	else
		printf("Heap test failed.\n");

	free(arr);

	return 0;
}
