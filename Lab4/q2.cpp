#include <stdio.h>
#include "mpi.h"
// #include <cmath>

float fxn(float x){
	return 4.0/(1.0+x*x);
}
int main(int argc, char* argv[])
{
	int rank,size,  i;
	float fact,factsum;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	float val=1.0/(float)size;
	float range=val*float(rank);
	fact = val*fxn(range+(val/2));
	
	MPI_Reduce (&fact,&factsum, 1, MPI_FLOAT, MPI_SUM, 0,	MPI_COMM_WORLD);

	if(rank==0)
		printf("Sum of all the PI=%f\n",factsum);
	MPI_Finalize();
}