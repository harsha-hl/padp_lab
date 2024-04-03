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
	FILE *ifp = fopen(argv[1], "rb");
	FILE *ofp = fopen(argv[2], "wb");
	
	gdImagePtr img = gdImageCreateFromPng(ifp);
	int w = gdImageSX(img);
	int h = gdImageSY(img);
	
	double t = omp_get_wtime();
	
	#pragma omp parallel for num_threads(16) schedule(guided)
	for(int x=0;x<w;x++){
		for(int y=0;y<h;y++){
			int color = gdImageGetPixel(img, x, y);
			int avgcolor = (gdImageRed(img, color) + gdImageBlue(img, color) + gdImageGreen(img, color)) / 3;
			color = gdImageColorAllocate(img, avgcolor, avgcolor, avgcolor);
			#pragma omp critical
			gdImageSetPixel(img, x, y, color);
		}
	}
	t = omp_get_wtime() - t;
	cout<<"Time taken: "<<t<<" seconds\n";
	gdImagePng(img,ofp);
	gdImageDestroy(img);
	fclose(ifp);
	fclose(ofp);
	return 0;
}
