#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<string.h>

#define ROOT 0
#define TAG 0
#define SIZE 2
#define BUFFSIZE 32

char *m[SIZE] = {"", "Hello"};
char msg[BUFFSIZE];

int main(int argc, char *argv[]){
	MPI_Init(&argc, &argv);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if(rank != ROOT){
		strcpy(msg, m[rank]);
		MPI_Send(&msg, BUFFSIZE, MPI_CHAR, ROOT, TAG, MPI_COMM_WORLD);
	}
	else{
		for(int i=0;i<size;i++){
			if(i==ROOT)continue;
			MPI_Recv(&msg, BUFFSIZE, MPI_CHAR, i, TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("Received %s in process %d from process %d\n", msg, ROOT, i);
		}
	}
	MPI_Finalize();
	return 0;
}
