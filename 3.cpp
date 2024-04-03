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

#define NUM 10000000

int strike(bool comp[], int start, int step, int stop){
	int i;
	for(i=start;i<=stop;i+=step)
		comp[i] = true;
	return i;
}

int unfriendly_sieve(int n){
	int m = sqrt(n);
	bool *comp = new bool[n+1];
	int count = 0;
	double t = omp_get_wtime();
	for(int i=2;i<=m;i++){
		if(!comp[i]){
			count++;
			strike(comp, 2*i, i, n); 
		}
	}
	for(int i=m+1;i<=n;i++)
		if(!comp[i])count++;
	t = omp_get_wtime() - t;
	cout<<"Count: "<<count<<", Time taken by unfriendly: "<<t<<" seconds\n";
	return count;
}

int friendly_sieve(int n){
	int m = sqrt(n);
	bool *comp = new bool[n+1];
	int *factor = new int[m];
	int *striker = new int[m];
	
	double t = omp_get_wtime();
	int count = 0;
	int fac_count = 0;
	
	for(int i=2;i<=m;i++){
		if(!comp[i]){
			count++;
			factor[fac_count] = i;
			striker[fac_count] = strike(comp, 2*i, i, m);
			fac_count++;
		}
	}
	
	for(int left=m+1;left<=n;left+=m){
		int right = min(left+m-1, n);
		
		for(int k=0;k<fac_count;k++)
			striker[k] = strike(comp, striker[k], factor[k], right);
		
		for(int k=left;k<=right;k++){
			if(!comp[k]) count++;
		}
	}
	t = omp_get_wtime() - t;
	cout<<"Count: "<<count<<", Time taken by friendly: "<<t<<" seconds\n";
	return count;
}

int parallel_friendly_sieve(int n){
	int m = sqrt(n);
	bool *comp = new bool[n+1];
	int *factor = new int[m];
	int *striker = new int[m];
	
	double t = omp_get_wtime();
	int count = 0;
	int fac_count = 0;
	
	for(int i=2;i<=m;i++){
		if(!comp[i]){
			count++;
			factor[fac_count] = i;
			striker[fac_count] = strike(comp, 2*i, i, m);
			fac_count++;
		}
	}
	
	for(int left=m+1;left<=n;left+=m){
		int right = min(left+m-1, n);
		#pragma omp parallel for num_threads(8)
		for(int k=0;k<fac_count;k++)
			striker[k] = strike(comp, striker[k], factor[k], right);
		#pragma omp parallel for reduction(+:count)
		for(int k=left;k<=right;k++){
			if(!comp[k]) count++;
		}
	}
	t = omp_get_wtime() - t;
	cout<<"Count: "<<count<<", Time taken by parallel friendly: "<<t<<" seconds\n";
	return count;
}

int main(){
	unfriendly_sieve(NUM);
	friendly_sieve(NUM);
	parallel_friendly_sieve(NUM);
	return 0;
}






























