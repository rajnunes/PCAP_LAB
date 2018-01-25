#include "mpi.h"
#include <iostream>
#include "string.h"

using namespace std;

int main(int argc, char *argv[])
{
	MPI_Init(&argc,&argv);
	int rank, size,N , temp;
	char A[100],c[10];
	int  B[10]={0};
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	// char buff[100];
	int n;
	string str;
	if(rank==0){
		cout<<"Enter String :";
		cin>>str;

		N=str.length();
	}
	MPI_Bcast(&N,1,MPI_INT,0,MPI_COMM_WORLD);
	// MPI_Scatter(B,1,MPI_INT,&temp,1,MPI_INT,0,MPI_COMM_WORLD);
	
	strcpy(A,str.c_str());
	MPI_Scatter(A,N/size,MPI_CHAR,c,N/size,MPI_CHAR,0,MPI_COMM_WORLD);
	int num=0;

	for(int i=0;i<N/size;i++){
		if(c[i]=='a' || c[i]=='e' || c[i]=='i' || c[i]=='o' || c[i]=='u'){
			continue;	
		}
		num++;
	}
	
	MPI_Gather(&num,1,MPI_INT,B,1,MPI_INT,0,MPI_COMM_WORLD);
	if(rank==0)
	{
		int fans=0;
		cout<<"The Result gathered in the root \n";
		for(int i=0;i<size;i++){
			cout<<B[i]<<" \t";
			fans+=B[i];
		}
		fans;

		cout<<endl<<endl<<fans<<endl;
	}
	MPI_Finalize();
}
