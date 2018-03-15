__kernel void transpose(__global int* A, __global int* B, int n, int m)
{
	int i = get_global_id(0);
	int j = get_global_id(1);
	
	B[j * n + i] = A[i * m + j];	
}
