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
	int matrix[16]={0};
	int temp[4]={0};
	int fin[4]={0};
	int ele;
	if(rank==0){
		cout<<"Enter a 4x4 Matrix :\n";
		// for(int i=0;i<3;i++)
			for(int j=0;j<16;j++)
				cin>>matrix[j];

		cout<<"\n\n";
		// for(int i=0;i<3;i++)
			// MPI_Ssend(matrix[i],3,MPI_INT,i,1,MPI_COMM_WORLD);
		// cout<<"FINS";

	}
	// MPI_Recv(temp,3,MPI_INT,0,1,MPI_COMM_WORLD,&status);
	MPI_Scatter(matrix,4,MPI_INT,temp,4,MPI_INT,0,MPI_COMM_WORLD);
	// MPI_Bcast(&ele,1,MPI_INT,0,MPI_COMM_WORLD);

	// if(rank==1)
		// cout<<"ELE1"<<ele;
	/*for(int i=0;i<3;i++)
		if(temp[i]==ele)
			total++;
*/
		int sum;
	MPI_Scan (&temp,&fin, 4, MPI_INT, MPI_SUM,MPI_COMM_WORLD);


		// MPI_Reduce (&temp,&sum, 1, MPI_INT, MPI_SUM, 0,	MPI_COMM_WORLD);
	for(int j=0;j<4;j++)
		cout<<fin[j]<<" ";
	cout<<endl;
	
	MPI_Finalize();
}