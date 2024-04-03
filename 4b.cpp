#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cctype>
#include<cmath>
#include<omp.h>
//#include<mpi.h>
#include<gd.h>
#include<string>

using namespace std;

int main(int argc, char *argv[]){
	FILE *ofp = fopen(argv[1], "wb");
	int w=1000, h=1000;
	gdImagePtr img = gdImageCreateTrueColor(w,h);
	double t = omp_get_wtime();
	t = omp_get_wtime() - t;
	#pragma omp parallel for num_threads(16) schedule(dynamic)
	for(int x=0;x<w;x++){
		for(int y=0;y<h;y++){
			int color = 0xFF << omp_get_thread_num() * 2;
			#pragma omp critical
			gdImageSetPixel(img,x,y,color);
		}
	}
	gdImagePng(img,ofp);
	gdImageDestroy(img);
	fclose(ofp);
	cout<<"Time taken: "<<t<<" seconds\n";
	return 0;
}
