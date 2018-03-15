__kernel void swap(__global int* A)
{
	int x = get_global_id(0);
	if(x & 1) 
	{
		A[x] ^= A[x^1];
		A[x^1] ^= A[x];
		A[x] ^= A[x^1];
	}	
}

