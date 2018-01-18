#include "mpi.h"
#include <iostream>
// #include "string.h"

using namespace std;

int factorial(int c){
	int ans=1;
	for(int i=1;i<=c;i++){
		ans*=i;
	}
	return ans;
}

int main(int argc, char *argv[])
{
	MPI_Init(&argc,&argv);
	int rank, size, N,c, A[10], B[10];
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	// char buff[100];
	int n;
	if(rank==0)
	{
		N=size;
		cout<<"Enter "<<N<<" values :";
		// fflush(stdout);
		for(int i=0;i<N;i++)
			cin>>A[i];
	}

	MPI_Scatter(A,1,MPI_INT,&c,1,MPI_INT,0,MPI_COMM_WORLD);
	cout<<"I have received "<<c<<" in process "<<rank<<endl;

	c=factorial(c);
	MPI_Gather(&c,1,MPI_INT,B,1,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0)
	{
		cout<<"The Result gathered in the root \n";
		for(int i=0;i<N;i++)
			cout<<B[i]<<" \t";
	}
	MPI_Finalize();
}
