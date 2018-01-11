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
	int arry[100];
	int num;
	if(rank==0){
		cout<<"Enter no of Elements : ";
		cin>>num;
		int t;
		arry[0]=num;
		for (int i = 1; i <= num; i++){
			cin>>t;
			arry[i]=t;
		}
		int sum=0;
		for (int i = rank+1; i <= arry[0]; i+=size){
			sum+=arry[i];	
		}

// MPI_Recv(&no,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
		

		MPI_Ssend(&arry,100,MPI_INT,1,0,MPI_COMM_WORLD);
		MPI_Recv(&num,1,MPI_INT,1,0,MPI_COMM_WORLD,&status);
		cout<<"Num "<<num<<endl;
		sum=sum+num;
		cout<<"Sum "<<sum;
	}
	else{
		MPI_Recv(&arry,100,MPI_INT,0,0,MPI_COMM_WORLD,&status);
		num=0;
		for (int i = rank+1; i <= arry[0]; i+=size){
			num+=arry[i];	
		}
		MPI_Ssend(&num,1,MPI_INT,0,0,MPI_COMM_WORLD);


	}

	MPI_Finalize();
}