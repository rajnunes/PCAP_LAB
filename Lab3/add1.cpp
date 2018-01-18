#include "mpi.h"
#include <iostream>
#include "string.h"

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
	int rank, size,N , temp;
	char A[100],c[100];
	char B[200];
	MPI_Status status;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	// char buff[100];
	int n;
	string str,str1,str2;
	if(rank==0){
		cout<<"Enter String 1:";
		cin>>str;


		N=str.length();
	}
	MPI_Bcast(&N,1,MPI_INT,0,MPI_COMM_WORLD);
	
	strcpy(A,str.c_str());
	MPI_Scatter(A,N/size,MPI_CHAR,c,(N)/size,MPI_CHAR,0,MPI_COMM_WORLD);
	
	for(int i=0;i<N/size;i++){
		if(c[i]>90)
			c[i]=(char)((int)c[i]-32);
		else 
			c[i]=(char)((int)c[i]+32);
	}

		
	MPI_Gather(c,(N)/size,MPI_CHAR,A,(N)/size,MPI_CHAR,0,MPI_COMM_WORLD);
	if(rank==0)
	{

		// int fans=0;
		// cout<<"IN"<<endl;
		// cout<<"The Result gathered in the root \n";
		for(int i=0;i<2*N;i++){
			cout<<A[i];
			// fans+=B[i];
		}
		// fans;

		// cout<<endl<<endl<<fans<<endl;
	}
	MPI_Finalize();
}
