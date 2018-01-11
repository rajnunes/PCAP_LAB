#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	MPI_Init(&argc,&argv);
	int a=1,b=100;
	int mid=a+b/2;

	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	switch(rank){
		case 0:
			for (int i = a; i <= mid; ++i){
				int ctr=0;
				for (int j = 1; j < i; ++j){
					if(i%j==0)
						ctr++;
				}
				if(ctr==1)
					cout<<i<<" ";
			}
		break;
		case 1:
			for (int i = mid; i <= b; ++i){
				int ctr=0;
				for (int j = 1; j < i; ++j){
					if(i%j==0)
						ctr++;
				}
				if(ctr==1)
					cout<<i<<" ";
			}
		break;
	}
	MPI_Finalize();
	return 0;
}