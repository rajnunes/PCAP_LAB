__kernel void search(__global char* A, __global char* B, __global int* C, int n, int m)
{
	int x = get_global_id(0);
	if(x <= n - m)
	{
		int ptr = 0;
		for(int i=x;ptr<m;i++,ptr++)
			if(A[i] != B[ptr])
				break;
		C[x] = (ptr == m);
	}
} 