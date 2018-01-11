// #include "mpi.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[])
{/*
	FILE* fp;
	fp=fopen("test.txt","r");	
*/
	std::map<string , int> val;

	ifstream file;
	file.open ("test.txt");

	string word;

	while (file >> word){
		val[word]++;
		cout<< word << " ";
	}
	cout<<endl;
	map<string,int>::iterator itr;

	int max=0;
	for(itr=val.begin();itr!=val.end();itr++)
		if(itr->second >max)
			max=itr->second;
	for(int i=max;i>0;i--){
		for(itr=val.begin();itr!=val.end();itr++){
			if(itr->second==i)
				cout<<itr->first<<" ";
		}
	}
/*	MPI_Init(&argc,&argv);
	MPI_Finalize();
*/
	file.close();
	return 0;
}