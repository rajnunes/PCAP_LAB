__kernel void swap(__global char *A,__global int N,__global char *T)
{
	// Get the index of the current work item
	int idx = get_global_id(0);
	// Do the operation
	int n=A[idx];
	for(int i=1;i<=N;i++){
		T[idx*i]=A[idx];
	}

}