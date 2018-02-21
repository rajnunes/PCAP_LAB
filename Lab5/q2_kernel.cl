__kernel void oneCompliment(__global unsigned int *A, __global unsigned int *B)
{
	// Get the index of the current work item
	int idx = get_global_id(0);
	// Do the operation
	int n=A[idx];

	

	B[idx]=(unsigned int)~A[idx];
}