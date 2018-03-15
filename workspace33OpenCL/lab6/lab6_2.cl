__kernel void strrepeat (__global char *str, __global char *newstr, int len)
{
	int id = get_global_id (0); 
	for (int i = 0, pos = len * id; i < len; )
		newstr [pos ++] = str [i ++]; 
}