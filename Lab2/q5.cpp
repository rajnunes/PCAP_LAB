#include "mpi.h"
#include <iostream>
// #include "string.h"

using namespace std;

int main(int argc, char *argv[])
{
	MPI_Init(&argc,&argv);
	int rank,size;
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	// char buff[100];
	int n;
	if(rank==0){
		cout<<"Enter No: ";
		cin>>n;
		MPI_Ssend(&n,1,MPI_INT,1,0,MPI_COMM_WORLD);
		
		MPI_Recv(&n,1,MPI_INT,size-1,0,MPI_COMM_WORLD,&status);
		n+=1;
		cout<<n;
	}	
	else{
		int pseudo_rank=(rank+1)%size;
		MPI_Recv(&n,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&status);
		n+=1;
		MPI_Ssend(&n,1,MPI_INT,pseudo_rank,0,MPI_COMM_WORLD);
		
	}
	MPI_Finalize();
}
