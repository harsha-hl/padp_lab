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

#define SIZE 5

string words[SIZE] = {"is", "an", "the", "on", "in"};
int counts[SIZE] = {};

void lower(string &str){
	for(int i=0;i<str.length();i++)
		str[i] = tolower(str[i]);
}

int getCount(string fileName, string key){
	int count = 0;
	lower(key);
	ifstream file(fileName);
	string word;
	while(file >> word){
		lower(word);
		if(word == key)count++;
	}
	return count;
}

int main(){
	double t = omp_get_wtime();
	#pragma omp parallel for num_threads(16)
	for(int i=0;i<SIZE;i++)
		counts[i] = getCount("file.txt", words[i]);
	t = omp_get_wtime() - t;
	cout<<"Time taken: "<<t<<" seconds\n";
	for(int i=0;i<SIZE;i++)
		cout<<words[i]<<" : "<<counts[i]<<endl;
	return 0;
}
