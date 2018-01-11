#include "mpi.h"
#include <iostream>
// #include <bits/stdc++.h>

using namespace std;

int main(int argc, char  ** argv)
{
	MPI_Init(&argc,&argv);
	cout<<"Enter Dimensions M x N : ";
	int m,n,p;
	cin>>m>>n;

	int mn[m][n];
	for (int i = 0; i < m; ++i){
		for (int j = 0; j < n; ++j){
			cin>>mn[i][j];		
		}
	}
	
	cout<<"Enter Dimensions " <<n<<" x P : ";
	cin>>p;

	int np[n][p];


	for (int i = 0; i < n; ++i){
		for (int j = 0; j < p; ++j){
			cin>>np[i][j];		
		}
	}

	int fin[m][p]={0};


	for (int i = 0; i < m; ++i){
		for (int j = 0; j < n; ++j){
			for (int k = 0; k < p; ++k){
				fin[i][k]+=mn[i][j]*np[j][k];
			}
		}
		
	}

	cout<<"\n\n";

	for (int i = 0; i < n; ++i){
		for (int j = 0; j < p; ++j){
			cout<<fin[i][j]<<" ";		
		}
		cout<<endl;
	}
	MPI_Finalize();
	return 0;
}