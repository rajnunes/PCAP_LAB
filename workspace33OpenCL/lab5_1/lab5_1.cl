__kernel void octal_value(__global int* A, __global int* B)
{
	int x = get_global_id(0);
	int ans = 0;
	int cur = A[x];
	int ret[100];
	int ptr = 0;
	B[x] = 0;
	for(	;cur != 0;cur /= 8)
		ret[ptr++] = cur % 8;
	for(int i=--ptr;i>=0;i--)
		B[x] = B[x] * 10 + ret[i];
}

