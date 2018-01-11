#include "mpi.h"
#include <iostream>
#include "string.h"

using namespace std;

int main(int argc, char *argv[])
{
	MPI_Init(&argc,&argv);
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	string str;
	MPI_Status status;
	char temp[1000];
		
	if(rank==0){
		cout<<"Enter A string :";
		// cin>>str;
		getline(cin,str);
		// cout<<endl<<str;
		MPI_Ssend(str.c_str(),1000,MPI_CHAR,1,0,MPI_COMM_WORLD);
		MPI_Recv(temp,1000,MPI_CHAR,1,1,MPI_COMM_WORLD,&status);
		string t(temp);
		cout<<t;	
	}
	else{
		MPI_Recv(temp,1000,MPI_CHAR,0,0,MPI_COMM_WORLD,&status);
		string t(temp);
		for (int i = 0; i <t.size(); ++i){
			if(t[i]>'a')
				t[i]-=32;
			else if(t[i]==' ')
				continue;
			else
				t[i]+=32;

		}
		// cout<<t;
		MPI_Ssend(t.c_str(),1000,MPI_CHAR,0,1,MPI_COMM_WORLD);
	}
	MPI_Finalize();
}