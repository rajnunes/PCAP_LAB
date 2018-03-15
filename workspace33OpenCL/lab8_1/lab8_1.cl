__kernel void sort_vector(__global char* A, __global char* B) 
{
	int x = get_global_id(0);
	char data = A[x];
	
	int n = get_global_size(0);
	int pos = 0;
	for(int i=0;i<n;i++)
		if(A[i] < data || A[i] == data && i < x)
			pos++;
	B[pos] = data;
}