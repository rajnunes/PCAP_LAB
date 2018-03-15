__kernel void mat_mul(__global int* As, __global int* Bs, __global int* Cs, int widthA, int widthB)
{
	int row = get_global_id(1);
	int col = get_global_id(0);
	int sum = 0;
	
	for(int i=0;i<widthA;i++)
		sum += As[row * widthA + i] * Bs[col + widthB * i];
	
	Cs[row * widthB + col] = sum;
}