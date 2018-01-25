#include <iostream>
#include "mpi.h"
int main(int argc, char* argv[])
{
	int rank,size,fact=1, factsum, i;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	
	MPI_Errhandler_set(MPI_COMM_WORLD, MPI_ERRORS_RETURN);

	int err=MPI_Bcast(&err,1,MPI_INT,size,MPI_COMM_WORLD);

	if(err != MPI_SUCCESS){
		std::cout<<"error\t";
	}
	// MPI_Scan (&fact,&factsum, 1, MPI_INT, MPI_SUM,MPI_COMM_WORLD);
	/*if(rank==(size-1))
		printf("Sum of all the factorial=%d\n",factsum);
	*/MPI_Finalize();
}