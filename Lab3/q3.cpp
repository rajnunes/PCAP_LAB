#include "mpi.h"
#include <iostream>
// #include "string.h"

using namespace std;

int main(int argc, char *argv[])
{
	MPI_Init(&argc,&argv);
	int rank, size,N, c[10]={0}, A[100],temp;
	float  B[10]={0};
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	// char buff[100];
	int n;
	if(rank==0)
	{	
		cout<<"Enter Val N: ";
		cin>>N;
		// N=size;
		cout<<"Enter "<<N*size<<" values :";
		// fflush(stdout);
		for(int i=0;i<N*size;i++){
			cin>>A[i];
			if(i<N)
				B[i]=N;
		}

	}
	MPI_Bcast(&N,1,MPI_INT,0,MPI_COMM_WORLD);
	// MPI_Scatter(B,1,MPI_INT,&temp,1,MPI_INT,0,MPI_COMM_WORLD);

	MPI_Scatter(A,N,MPI_INT,c,N,MPI_INT,0,MPI_COMM_WORLD);
	float avg=0;;
	for(int i=0;i<N;i++){
		avg=avg+c[i];
	}
	avg=avg/N;
	MPI_Gather(&avg,1,MPI_FLOAT,B,1,MPI_FLOAT,0,MPI_COMM_WORLD);
	if(rank==0)
	{
		float fans=0;
		cout<<"The Result gathered in the root \n";
		for(int i=0;i<size;i++){
			cout<<B[i]<<" \t";
			fans+=B[i];
		}
		fans/=size;

		cout<<endl<<endl<<fans<<endl;
	}
	MPI_Finalize();
}
