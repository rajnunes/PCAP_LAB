#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc, char  *argv[])
{
	// cout<<"hello";
	MPI_Init(&argc,&argv);

	int rank;
		MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if(rank%2==0)
		cout<<"Helo\n";
	else
		cout<<"World\n";
	MPI_Finalize();
	return 0;
}