//matrixKernel.cl
__kernel void mat_mul( __global int* Aelements, __global int* Belements,__global
	int* Celements,int widthA, int widthB)
{
	int row=get_global_id(1);
	int col=get_global_id(0);
	int sum=0;
	for(int i=0;i<widthA;i++)
	{
		sum+=Aelements[row*widthA+i]*Belements[i*widthB+col];
	}
	Celements[row*widthB+col] = sum;
	// Celements[row*widthB+col]=Aelements[row*widthA+col];
}