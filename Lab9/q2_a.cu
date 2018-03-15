#include "malloc.h"
#include <stdio.h>

__global__ void add(int *a, int *b, int *c,int *col) {
	// *c = *a + *b
	int id=blockIdx.x;
	int start=id*col[0];
	for(int i=0;i<col[0];i++){
		c[start+i]=a[start+i]+b[start+i];
	}

}
int main(void) {
	int *a, *b, *c;
	int numR,numC;
	printf("Enter number of rows and columns :\n");
	scanf("%d",&numR);
	scanf("%d",&numC);
	int size = sizeof(int);

	// a=(int*)malloc(numC*numR*size);
	// b=(int*)malloc(numC*numR*size);
	// c=(int*)malloc(numC*numR*size);
	cudaMalloc((void **)&b, numC*numR*size);
	cudaMalloc((void **)&a, numC*numR*size);
	cudaMalloc((void **)&c, numC*numR*size);


	printf("Enter A\n");
	int temp;
	for (int i = 0; i < numC*numR; ++i)
	{	
		scanf("%d",&temp);
		a[i]=temp;
	}
	printf("Enter B\n");
	for (int i = 0; i < numC*numR; ++i)
	{	
		scanf("%d",&temp);
		b[i]=temp;
	}	
	// host copies of variables a, b & c
	int *d_a, *d_b, *d_c,*col; // device copies of variables a, b & c
	// Allocate space for device copies of a, b, c
	cudaMalloc((void **)&d_a, numC*numR*size);
	cudaMalloc((void **)&d_b, numC*numR*size);
	cudaMalloc((void **)&d_c, numC*numR*size);
	cudaMalloc((void **)&col, size);
	
	// Setup input values
	
	// Copy inputs to device
	cudaMemcpy(d_a, &a, numC*numR*size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, &b, numC*numR*size, cudaMemcpyHostToDevice);
	cudaMemcpy(col,&numC,size,cudaMemcpyHostToDevice);
	// Launch add() kernel on GPU
	printf("LOOOL\n");
	add<<<numR,1>>>(d_a, d_b, d_c,col);
	// Copy result back to host
	cudaMemcpy(&c, d_c,numC*numR*size, cudaMemcpyDeviceToHost);
	printf("LOOOL\n");
	
	for (int i = 0; i < numC*numR; ++i)
	{	
		if(i%numC==0)
			printf("wot\n");
		printf("%d ",c[i]);
	}	
	printf("LOOOL\n");
	// printf("ANS	%d\t%d\n",c[0],c[1] );

	// Cleanup
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	return 0;
}