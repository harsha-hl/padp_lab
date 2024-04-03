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

#define SEED 123456

int main(){

	int th;
	cout<<"Enter number of threads\n";
	cin>>th;
	omp_set_num_threads(th);
	
	double t = omp_get_wtime();
	int n = 100000;
	int count = 0;
	srand(SEED);
	
	#pragma omp parallel for reduction(+:count)
	for(int i=0; i<n; i++){
		double x = (double)rand() / RAND_MAX;
		double y = (double)rand() / RAND_MAX;
		double z = x*x + y*y;
		if(z <= 1.0) count++;
	}
	
	double pi = (double)count / n * 4;
	t = omp_get_wtime() - t;
	cout<<"Number of threads : "<<th<<"\n";
	cout<<"Time taken : "<<t<<"seconds\n";
	cout<<"Pi value : "<<pi<<"\n";
	return 0;
}
