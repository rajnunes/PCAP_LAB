__kernel void swap(__global int *A)
{
	// Get the index of the current work item
	int idx = get_global_id(0);
	// Do the operation
	int n=A[idx];

	if(idx%2==0){
		A[idx]=A[idx+1];
		A[idx+1]=n;
	}
}