
#include <stdio.h>
__global__ void add(int *a, int *b, int *c) {
	// *c = *a + *b
	int id=threadIdx.x;
	c[id]=a[id]+b[id];

}
int main(void) {
	int a[2], b[2], c[2];
	// host copies of variables a, b & c
	int *d_a, *d_b, *d_c; // device copies of variables a, b & c
	int size = sizeof(int);
	// Allocate space for device copies of a, b, c
	cudaMalloc((void **)&d_a, 2*size);
	cudaMalloc((void **)&d_b, 2*size);
	cudaMalloc((void **)&d_c, 2*size);
	// Setup input values
	a[0] = 3;
	a[1]=4;
	b[0] = 5;
	b[1]=5;
	// Copy inputs to device
	cudaMemcpy(d_a, &a, 2*size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, &b, 2*size, cudaMemcpyHostToDevice);
	// Launch add() kernel on GPU

	add<<<1,2>>>(d_a, d_b, d_c);
	// Copy result back to host
	cudaMemcpy(&c, d_c, 2*size, cudaMemcpyDeviceToHost);

	printf("ANS	%d\t%d\n",c[0],c[1] );
	// Cleanup
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	return 0;
}