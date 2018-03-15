__kernel void odd(__global int* A) 
{
	int x = get_global_id(0);
	int n = get_global_size(0);
	if(x % 2 == 1 && x < n - 1 && A[x] > A[x+1])
	{
		int d = A[x];
		A[x] = A[x+1];
		A[x+1] = d;
	}
}

__kernel void even(__global int* A) 
{
	int x = get_global_id(0);
	int n = get_global_size(0);
	if(x % 2 == 0 && x < n - 1 && A[x] > A[x+1])
	{
		int d = A[x];
		A[x] = A[x+1];
		A[x+1] = d;
	}
}