__kernel void octal_val(__global int *A, __global int *B)
{
	// Get the index of the current work item
	int idx = get_global_id(0);
	// Do the operation
	int n=A[idx];

	int rem=0,q=0;
	while(n!=0){
		q=n%8;
		n=n/8;
		rem=rem*10+q;
	}
	// rem is the ans

	B[idx]=rem;
}
