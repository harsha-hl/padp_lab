#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<omp.h>
#include<mpi.h>
//#include<gd.h>
#include<string>

using namespace std;

#define ROOT 0
#define SEED 123456

int main(int argc, char *argv[]){
	MPI_Init(&argc, &argv);
	int rank,size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	double t;
	if(rank == ROOT){
		t = MPI_Wtime();
	}
	int n = 10000;
	int count = 0;
	int red_count;
	for(int i=0;i<n/size;i++){
		double x = (double)rand() / RAND_MAX;
		double y = (double)rand() / RAND_MAX;
		double z = x*x + y*y;
		if(z <= 1.0)count++;
	}
	MPI_Reduce(&count, &red_count, 1, MPI_INT, MPI_SUM, ROOT, MPI_COMM_WORLD);
	if(rank==ROOT){
		t = MPI_Wtime() - t;
		double pi = (double)red_count / n * 4;
		cout<<"Number of processes: "<<size<<endl;
		cout<<"Time taken: "<<t<<" seconds\n"<<endl;
		cout<<"Pi value: "<<pi<<endl;
	}
	MPI_Finalize();
	return 0;
}
