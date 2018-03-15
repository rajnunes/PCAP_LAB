__kernel void wordrev (__global char *str, __global char *newstr, __global int * start,__global int * end)
{
	int id = get_global_id (0);
	for (int i = start [id], j = end [id]; i <=j; i ++, j --)
	{
		newstr [i] = str [j]; 
		newstr [j] = str [i];
	}
}