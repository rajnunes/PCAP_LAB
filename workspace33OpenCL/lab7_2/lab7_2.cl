__kernel void inner_compliment(__global int* A, __global int* B, int n, int m)
{
	int i = get_global_id(0);
	int j = get_global_id(1);
	
	int x = i * m + j;
	if(i == 0 || j == 0 || i == n - 1 || j == m - 1)
		B[x] = A[x];
	else
	{
		int temp = A[x];
		B[x] = 0;
		int d = 1;
		while(temp != 0)
		{
			B[x] += d * (1 - temp % 2);
			temp /= 2;
			d *= 10;
		}
	}
}