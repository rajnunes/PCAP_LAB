#include <iostream>
#include "mpi.h"
#include <string>
using namespace std;
int main(int argc, char* argv[])
{
	MPI_Init(&argc,&argv);
	int rank,size,N,L;
	char temp[100],t,temp1[200],temp2[10][100];
	int rank_arr[4]={1,2,3,4};
	string str;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if(rank==0){
		cout<<"Enter String: ";
		cin>>str;
		N=str.length();
	}
	MPI_Bcast(&N,1,MPI_INT,0,MPI_COMM_WORLD);

	MPI_Scatter(str.c_str(),1,MPI_CHAR,&t,1,MPI_CHAR,0,MPI_COMM_WORLD);

	for(int i=0;i<=rank;i++){
		temp[i]=t;
	}
	// temp[rank+1]='\0';
	// cout<<temp;
	// MPI_Gather();
	
	MPI_Gatherv(temp,rank+1,MPI_CHAR,temp1,rank_arr,MPI_CHAR,0,MPI_COMM_WORLD);

	if(rank==0){
		temp1[2*N]='\0';
		cout<<endl<<temp1<<endl;
	}

	MPI_Finalize();
}