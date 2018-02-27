 #include <iostream>
#include "mpi.h"

using namespace std;
int main(int argc, char* argv[])
{
	int rank,size,fact=1, total=0, i;
	MPI_Init(&argc,&argv);
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int matrix[9]={0};
	int temp[3]={0};
	int ele;
	if(rank==0){
		cout<<"Enter a 3x3 Matrix :\n";
		// for(int i=0;i<3;i++)
			for(int j=0;j<9;j++)
				cin>>matrix[j];

		std::cout<<"Enter element to be searched : ";
		cin>>ele;

		// for(int i=0;i<3;i++)
			// MPI_Ssend(matrix[i],3,MPI_INT,i,1,MPI_COMM_WORLD);
		// cout<<"FINS";

	}
	// MPI_Recv(temp,3,MPI_INT,0,1,MPI_COMM_WORLD,&status);
	MPI_Scatter(matrix,3,MPI_INT,temp,3,MPI_INT,0,MPI_COMM_WORLD);
	MPI_Bcast(&ele,1,MPI_INT,0,MPI_COMM_WORLD);

	// if(rank==1)
		// cout<<"ELE1"<<ele;
	for(int i=0;i<3;i++)
		if(temp[i]==ele)
			total++;

		int sum;
	// MPI_Scan (&fact,&factsum, 1, MPI_INT, MPI_SUM,MPI_COMM_WORLD);
		MPI_Reduce (&total,&sum, 1, MPI_INT, MPI_SUM, 0,	MPI_COMM_WORLD);

	if(rank==0){
		cout<<"Number of occurances: ";
		cout<<sum;
	}
	MPI_Finalize();
}