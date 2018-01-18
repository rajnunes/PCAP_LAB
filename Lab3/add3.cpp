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
	int rank, size,N, c[100]={0}, A[100],temp;
	int  B[10]={0};
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
	float avg=0;
	// if(rank%2==0){
		for(int i=0;i<N;i++){
			c[i]=(c[i]*(c[i]+1))/2;
		}
	
	// avg=avg/N;
	MPI_Gather(c,N,MPI_INT,B,N,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0)
	{
		float fans=0;
		cout<<"The Result gathered in the root \n";
		for(int i=0;i<size*N;i++){
			cout<<B[i]<<" ";
			// fans+=B[i];
		}
		// fans/=size;

		// cout<<endl<<endl<<fans<<endl;
	}
	MPI_Finalize();
}
