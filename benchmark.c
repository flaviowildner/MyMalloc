#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mymalloc.c"


void teste_MyMalloc(){
	int **a;
	int i, j;

	struct timeval start, end;
	int tmili;

	int x = 32768000;
	int y = 8;

	gettimeofday(&start, NULL);

	a = (int**)MyMalloc(x * sizeof(int*));
	for(i=0;i<x;i++){
		a[i] = (int*)MyMalloc(y * sizeof(int));
	}
    	for(i=0;i<x;i++){
		for(j=0;j<y;j++){
		    a[i][j] = i+j;
		}
	}
	
	for(i=0;i<x;i=i+2){
		MyMallocFree(a[i]);
	}

	for(i=0;i<x;i=i+2){
		a[i] = MyMalloc(y * sizeof(int));
	}

	gettimeofday(&end, NULL);

	tmili = (int) (1000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000);
	printf("Myalloc - Tempo de alocacao e realocacao: %dms\n", tmili);
}

void teste_MyMalloc2(){
	int **a;
	int i, j;

	struct timeval start, end;
	int tmili;

	int x = 16384000;
	int y = 8;

	gettimeofday(&start, NULL);

	a = (int**)MyMalloc(x * sizeof(int*));
	for(i=0;i<x;i++){
		a[i] = (int*)MyMalloc(y * sizeof(int));
	}
	for(i=0;i<x;i++){
		for(j=0;j<y;j++){
		    a[i][j] = i+j;
		}
	}
	
	for(i=0;i<x;i=i+2){
		MyMallocFree(a[i]);
	}

	for(i=0;i<x;i=i+2){
		a[i] = MyMalloc((y + 20)  * sizeof(int));
	}

	gettimeofday(&end, NULL);

	tmili = (int) (1000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000);
	printf("Myalloc - Tempo de alocacao e realocacao com fragmentacao: %dms\n", tmili);
}

void teste_malloc(){
	int **a;
	int i, j;

	struct timeval start, end;
	int tmili;

	int x = 32768000; //500MB
	int y = 8;

	gettimeofday(&start, NULL);

	a = (int**)malloc(x * sizeof(int*));
	for(i=0;i<x;i++){
		a[i] = (int*)malloc(y * sizeof(int));
	}
	for(i=0;i<x;i++){
	        for(j=0;j<y;j++){
			a[i][j] = i+j;
		}
	}
	
	for(i=0;i<x;i=i+2){
		free(a[i]);
	}

	for(i=0;i<x;i=i+2){
		a[i] = malloc(y * sizeof(int));
	}

	gettimeofday(&end, NULL);

	tmili = (int) (1000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000);
	printf("malloc - Tempo de alocacao e realocacao : %dms\n", tmili);
}

void teste_malloc2(){
	int **a;
	int i, j;

	struct timeval start, end;
	int tmili;

	int x = 16384000; //500MB
	int y = 8;

	gettimeofday(&start, NULL);

	a = (int**)malloc(x * sizeof(int*));
	for(i=0;i<x;i++){
		a[i] = (int*)malloc(y * sizeof(int));
	}
	for(i=0;i<x;i++){
        	for(j=0;j<y;j++){
			a[i][j] = i+j;
        	}
	}
	
	for(i=0;i<x;i=i+2){
		free(a[i]);
	}

	for(i=0;i<x;i=i+2){
		a[i] = malloc((y + 20) * sizeof(int));
	}

	gettimeofday(&end, NULL);

	tmili = (int) (1000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000);
	printf("malloc2 - Tempo de alocacao e realocacao com fragmentacao: %dms\n", tmili);
}

void teste_Myfree(){
	int **a;
	int i, j;

	struct timeval start, end;
	int tmili;

	int x = 32768000; //500MB
	int y = 8;

	

	a = (int**)MyMalloc(x * sizeof(int*));
    for(i=0;i<x;i++){
        a[i] = (int*)MyMalloc(y * sizeof(int));
    }
    for(i=0;i<x;i++){
        for(j=0;j<y;j++){
            a[i][j] = i+j;
        }
	}

	gettimeofday(&start, NULL);
	
	for(i=0;i<x;i++){
		MyMallocFree(a[i]);
	}

	gettimeofday(&end, NULL);


	
	tmili = (int) (1000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000);
	printf("Myfree - Tempo de desalocacao: %dms\n", tmili);
}

void teste_free(){
	int **a;
	int i, j;

	struct timeval start, end;
	int tmili;

	int x = 32768000; //500MB
	int y = 8;

	

	a = (int**)malloc(x * sizeof(int*));
	for(i=0;i<x;i++){
		a[i] = (int*)malloc(y * sizeof(int));
	}
	for(i=0;i<x;i++){
        	for(j=0;j<y;j++){
			a[i][j] = i+j;
		}
	}

	gettimeofday(&start, NULL);
	
	for(i=0;i<x;i++){
		free(a[i]);
	}

	gettimeofday(&end, NULL);


	
	tmili = (int) (1000 * (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000);
	printf("free - Tempo de desalocacao: %dms\n", tmili);
}


/*
3276800 100MB
6553600 200MB
16384000 500MB
32768000 1GB
*/

int main()
{
	
	teste_MyMalloc();
	//teste_MyMalloc2();

	//teste_malloc();
	//teste_malloc2();

	//teste_Myfree();
	//teste_free();

	return 0;
}
