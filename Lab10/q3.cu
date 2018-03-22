
#include <stdio.h>
__global__ void add(char *A,int len) {
		int idx=threadIdx.x;
		// int ctr=0;
		int temp=(int)A[idx];
		temp=~temp;
		printf("%d\n",temp );
		// A[idx]=(char)
}
int main(void) {
	char c[100];
	char sub[100];
	int *o;
	// host copies of variables a, b & c
	char *A;
	char *d_sub;
	int *d_o;
	int d_sub_len; // device copies of variables a, b & c
	// int size = sizeof(int);
	printf("Enter String\n");
	fgets (c, 100, stdin);
		printf("%s\n",c);
	int size=strlen(c)-1;
	// printf("MAINS TIRGN %d\n",size );

	// printf("Enter Sub String\n");
	// fgets (sub, 100, stdin);
		printf("%s\n",sub);
	// int size_sub=strlen(sub)-1;
	// d_sub_len=size_sub;

	// int size_o=size-size_sub+1;
	// Allocate space for device copies of a, b, c
	cudaMalloc((void **)&A, size*sizeof(char));
	// cudaMalloc((void **)&d_sub, size_sub*sizeof(char));
	// cudaMalloc((void **)&d_o, size_o*sizeof(int));
	// o=(int*)calloc(size_o,sizeof(int));
	// o={0};
	// cudaMalloc((void **)&o, sizeof(int));
	// cudaMalloc((void **)d_sub_len, sizeof(int));
	
	// Setup input values
	// Copy inputs to device
	cudaMemcpy(A, c, size*sizeof(char), cudaMemcpyHostToDevice);

	// cudaMemcpy(d_sub, sub, size_sub*sizeof(char), cudaMemcpyHostToDevice);
	// cudaMemcpy(d_b, &b, size, cudaMemcpyHostToDevice);
	// Launch add() kernel on GPU
	int rel_size=size;
	if(size%2!=0)
		rel_size++;
	add<<<1,size>>>(A, size);
	// Copy result back to host
	// cudaMemcpy(c, A, size*sizeof(char), cudaMemcpyDeviceToHost);
		
	printf("%s\n",c );
	int temp=0;
	// printf("LOLOL %d\n",size_o);
	/*for (int i = 0; i < size_o; ++i)
	{
		if(o[i]!=0){
			temp=i;
			break;
		}
		else
			temp=0;
	}
	
	printf("LOLOL\n");
	
	if(temp!=0){
		int pos;
		if(temp==-1)
			pos=0;
		else
			pos=temp;
		printf("found at %d\n",pos);
	}else{
		printf("Not found\n");
	}*/

	// printf("%d\n",c );
	// Cleanup
	// cudaFree(d_o);

	cudaFree(A);
	// cudaFree(d_c);
	return 0;
}