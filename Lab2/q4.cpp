#include "mpi.h"
#include <iostream>
#include <cmath>
// #include "string.h"

using namespace std;

int main(int argc, char *argv[])
{
	MPI_Init(&argc,&argv);
	int rank,size;
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	int buff[100];
	int buff1[100];
	int n,sz=100;
	MPI_Buffer_attach(buff1,sz);
	if(rank==0){
		cout<<"Enter "<<size-1<<" Elements : ";

		for (int i = 0; i < size-1; ++i){
			int t;
			cin>>t;
			buff[i]=t;
		}
		for (int i = 1; i < size; ++i){
			MPI_Bsend(&buff[i-1],1,MPI_INT,i,0,MPI_COMM_WORLD);
		
		}

	}	
	else if(rank%2==0){
		MPI_Recv(&n,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
		cout<<"\n"<<pow(n,2)<<endl;

	}
	else{
		MPI_Recv(&n,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
				cout<<"\n"<<pow(n,3)<<endl;
		
	}
	MPI_Buffer_detach(&buff1,&sz);
	MPI_Finalize();
}
