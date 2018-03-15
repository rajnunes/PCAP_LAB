__kernel void strrev (__global char *str, __global char *newstr, int len)
{
	int id = get_global_id (0);
	newstr [id] = str [len - id - 1];
	newstr [len - id - 1] = str [id];
}