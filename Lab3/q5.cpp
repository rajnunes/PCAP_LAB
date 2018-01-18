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


		cout<<"Enter String 1:";
		cin>>str1;

		N=str.length();
		/*for(int i=0;i<N;i++){
			str2+=str[i];
			str2+=str1[i];
		}*/

		// cout<<str2<<" lol";
	}
	MPI_Bcast(&N,1,MPI_INT,0,MPI_COMM_WORLD);
	// MPI_Scatter(B,1,MPI_INT,&temp,1,MPI_INT,0,MPI_COMM_WORLD);
	
	strcpy(A,str.c_str());
	MPI_Scatter(A,N/size,MPI_CHAR,c,(N)/size,MPI_CHAR,0,MPI_COMM_WORLD);
	for(int i=0;i<N/size;i++)
		B[2*i]=c[i];

	strcpy(A,str1.c_str());
	MPI_Scatter(A,(N)/size,MPI_CHAR,c,(N)/size,MPI_CHAR,0,MPI_COMM_WORLD);
	for(int i=0;i<N/size;i++)
		B[2*i+1]=c[i];
	
	// int num=0;

		
	MPI_Gather(B,(2*N)/size,MPI_CHAR,A,(2*N)/size,MPI_CHAR,0,MPI_COMM_WORLD);
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
