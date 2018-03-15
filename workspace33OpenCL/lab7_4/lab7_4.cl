__kernel void row_col_sum(__global int* A, __global int* B, int n, int m)
{
	int x = get_global_id(0);
	int y = get_global_id(1);
	
	for(int i=0;i<n;i++)
		B[x * m + y] += A[i * m + y];
	for(int j=0;j<m;j++)
		B[x * m + y] += A[x * m + j];
}
