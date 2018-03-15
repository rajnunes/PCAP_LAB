__kernel void row_powers(__global int* A, __global int* B, int width)
{
	int row = get_global_id(1);
	int col = get_global_id(0);
	
	B[row * width + col] = 1;
	for(int i=0;i<=row;i++)
		B[row * width + col] *= A[row * width + col];
	
}