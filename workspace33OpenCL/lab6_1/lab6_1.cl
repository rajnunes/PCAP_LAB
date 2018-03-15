__kernel void asciirev(__global char *str, __global char *rev)
{
	int i = get_global_id (0), n = (int) str [i]; rev [i] = 0; 
	while ( n > 0 )
	{
		rev [i] = rev [i] * 10 + n % 10; 
		n /= 10;
	}
}