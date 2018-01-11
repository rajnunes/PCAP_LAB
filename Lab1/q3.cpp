#include "mpi.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	MPI_Init(&argc,&argv);

	int a=25,b=10;
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	switch(rank){
		case 0:
			// add
		cout<<"Add "<<a+b<<endl;
		break;
		
		case 1:
			// sub
		cout<<"Sub "<<a-b<<endl;
		break;

		case 2:
		// mul
		cout<<"Mul "<<a*b<<endl;
		break;

		case 3:
		//  div
		cout<<"Div "<<a/b<<endl;
		break;

		default:

		cout<<"LOL\n";

	}
	MPI_Finalize();

	return 0;
}