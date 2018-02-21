__kernel void swap(__global char *A)
{
	// Get the index of the current work item
	int idx = get_global_id(0);
	// Do the operation
	int n=A[idx];

	while(n>0){
		rem=n%10;
		n=n/10;
		ans=ans*10 + rem;
	}
	A[idx]=(char)ans;
}