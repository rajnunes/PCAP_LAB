
#include <stdio.h>
__global__ void add(char *c, char *sub, int *o,int sub_len) {
		int idx=threadIdx.x;
		int ctr=0;

		for (int i = 0; i < sub_len; ++i)
		{
			if(c[idx+i]==sub[i])
				ctr++;

		}
		o[idx]=0;
		
		if(idx==0 && ctr==sub_len)
			o[idx]=-1;
		else if(ctr==sub_len)
			o[idx]=1;
		
}
int main(void) {
	char c[100];
	char sub[100];
	int *o;
	// host copies of variables a, b & c
	char *d_c;
	char *d_sub;
	int *d_o;
	int d_sub_len; // device copies of variables a, b & c
	// int size = sizeof(int);
	printf("Enter String\n");
	fgets (c, 100, stdin);
		printf("%s\n",c);
	int size=strlen(c)-1;
	// printf("MAINS TIRGN %d\n",size );

	printf("Enter Sub String\n");
	fgets (sub, 100, stdin);
		printf("%s\n",sub);
	int size_sub=strlen(sub)-1;
	d_sub_len=size_sub;

	int size_o=size-size_sub+1;
	// Allocate space for device copies of a, b, c
	cudaMalloc((void **)&d_c, size*sizeof(char));
	cudaMalloc((void **)&d_sub, size_sub*sizeof(char));
	cudaMalloc((void **)&d_o, size_o*sizeof(int));
	o=(int*)calloc(size_o,sizeof(int));
	// o={0};
	// cudaMalloc((void **)&o, sizeof(int));
	// cudaMalloc((void **)d_sub_len, sizeof(int));
	
	// Setup input values
	// Copy inputs to device
	cudaMemcpy(d_c, c, size*sizeof(char), cudaMemcpyHostToDevice);

	cudaMemcpy(d_sub, sub, size_sub*sizeof(char), cudaMemcpyHostToDevice);
	// cudaMemcpy(d_b, &b, size, cudaMemcpyHostToDevice);
	// Launch add() kernel on GPU

	add<<<1,size_o>>>(d_c, d_sub, d_o,d_sub_len);
	// Copy result back to host
	cudaMemcpy(o, d_o, size_o*sizeof(int), cudaMemcpyDeviceToHost);
	
	int temp=0;
	// printf("LOLOL %d\n",size_o);
	for (int i = 0; i < size_o; ++i)
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
	}

	// printf("%d\n",c );
	// Cleanup
	cudaFree(d_o);

	cudaFree(d_sub);
	cudaFree(d_c);
	return 0;
}