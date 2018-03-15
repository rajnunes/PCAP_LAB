__kernel void negate(__global int* A, __global int* B)
{
	int x = get_global_id(0);
	int cur = A[x];
	int ans = 0;
	do {
		ans = ans * 10 + 1;
		cur /= 10;
	} while (cur != 0);
	B[x] = ans - A[x];
}

