__kernel void sort_vector(__global int* A, __global int* B) 
{
	int x = get_global_id(0);
	int data = A[x];
	
	int n = get_global_size(0);
	int pos = 0;
	for(int i=0;i<n;i++)
		if(A[i] < data || A[i] == data && i < x)
			pos++;
	B[pos] = data;
}