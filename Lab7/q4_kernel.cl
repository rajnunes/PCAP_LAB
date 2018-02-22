__kernel void mat_pow( __global int* Aelements,__global int* Belements, int widthA)
{
	int col=get_global_id(1);
	int row=get_global_id(0);
	// int sum=0;
	// int val=Aelements[row*widthA+col];
	// Belements[row*widthA+col]=1;
	/*for(int i=0;i<=col;i++){
		Belements[row*widthA+col]*=val;
	}*/
	// Celements[row*widthB+col]=Aelements[row*widthA+col];
	
	Belements[row*widthA+col]=Aelements[col*widthA+row];
	
}