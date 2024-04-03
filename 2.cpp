#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<omp.h>
//#include<mpi.h>
//#include<gd.h>
#include<string>

using namespace std;

#define DIM 1000

int main(){
	int *A = new int[DIM*DIM];
	int *B = new int[DIM*DIM];
	int *C = new int[DIM*DIM];
	
	for(int i=0;i<DIM;i++){
		for(int j=0;j<DIM;j++){
			A[i*DIM + j] = rand() % 1000;
			B[i*DIM + j] = rand() % 1000;
		}
	}
	
	cout<<"Matrix A\n";
	for(int i=0;i<DIM;i++){
		for(int j=0;j<DIM;j++)
			cout<<A[i*DIM + j]<<"\t";
		cout<<endl;
	}
	
	cout<<"Matrix B\n";
	for(int i=0;i<DIM;i++){
		for(int j=0;j<DIM;j++)
			cout<<B[i*DIM + j]<<"\t";
		cout<<endl;
	}
	
	double t = omp_get_wtime();
	#pragma omp parallel for num_threads(16)
	for(int i=0;i<DIM;i++)
		for(int j=0;j<DIM;j++)
			for(int k=0;k<DIM;k++)
				C[i*DIM + k] += A[i*DIM + j] * B[j*DIM + k];
	
	t = omp_get_wtime() - t;
	cout<<"Matrix C\n";
	for(int i=0;i<DIM;i++){
		for(int j=0;j<DIM;j++)
			cout<<C[i*DIM + j]<<"\t";
		cout<<endl;
	}
	
	cout<<"Time taken: "<<t<<" seconds\n";
	return 0;
}
