#include "mpi.h"
#include <iostream>
#include "string.h"

using namespace std;

int main(int argc, char *argv[])
{
	MPI_Init(&argc,&argv);
	int rank,size;
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int no;
	if(rank==0){
		cin>>no;
		for (int i = 1; i < size; ++i){
			MPI_Ssend(&no,1,MPI_INT,i,0,MPI_COMM_WORLD);
		}

	}
	else{
		MPI_Recv(&no,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
		cout<<"Rank "<<rank<<" value "<<(int)no<<endl;

	}
	MPI_Finalize();
}