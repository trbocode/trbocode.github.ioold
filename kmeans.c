#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define INT_MAX 2147483647
int main(int argc, char **argv) {
	assert(argc>1);
	double value,min;
	char c;
	int d=1,amount=0;
	int k= atoi(argv[1]);
	bool flag=false;
	int iter=1,maxiter;
	int oldassignment;
	double **vectors,**centroids,**sums;
	double *pt,*pt2,*pt3;
	if (argc==2){
		maxiter=200;
	}
	else{
		maxiter= atoi(argv[2]);
	}
	while (scanf("%lf%c",&value, &c) ==2){
		if (c==','&& !flag){
			d++;
		}
		if (c=='\n'){
			flag=true;
			amount++;
		}
	}
	rewind(stdin);
	pt = calloc(d*amount,sizeof(double));
	vectors = calloc(amount,sizeof(double *));
	for(int i=0 ; i<amount ; i++ ) vectors[i] = pt+i*d;
	int col=0,row=0;
	while (scanf("%lf%c",&value, &c) ==2){
		vectors[row][col]=value;
		col++;
		if (c=='\n'){
			col=0;
			row++;
		}
	}
	pt2 = calloc(d*k,sizeof(double));
	pt3 = calloc(d*k,sizeof(double));
	centroids = calloc(k,sizeof(double *));
	sums = calloc(k,sizeof(double *));
	for(int i=0 ; i<k ; i++ ) {
		centroids[i] = pt2+i*d;
		sums[i] = pt3+i*d;
	}
	int *assignments=calloc(amount,sizeof(int));
	int *sizes = calloc(k,sizeof(int));
	for (int i=0;i<k;i++){
		for (int j=0;j<d;j++){
			centroids[i][j]=vectors[i][j];
		}
	}
	while (flag){
		flag=false;
		for (int i=0;i<amount;i++){
			min=INT_MAX;
			oldassignment=assignments[i];
			for (int j=0;j<k;j++){
				value=0;
				for (int l=0;l<d;l++){
					value+=(vectors[i][l]-centroids[j][l])*(vectors[i][l]-centroids[j][l]);
				}
				if(value<min) {
					min=value;
					assignments[i]=j;
				}
			}
			if (assignments[i]!=oldassignment) {
				flag=true;
			}
			sizes[assignments[i]]+=1;
			for (int j=0;j<d;j++){
				sums[assignments[i]][j]+=vectors[i][j];
			}
		}
		for (int i=0;i<k;i++){
			for (int j=0;j<d;j++) {
				centroids[i][j]=(sums[i][j]/sizes[i]);
				sums[i][j]=0;
			}
			sizes[i]=0;
		}
		if (iter>=maxiter) {
			flag=false;
		}
		iter++;
	}
	for (int i=0;i<k;i++){
		for (int j=0;j<d;j++){
			printf("%.4f",centroids[i][j]);
			if(j==d-1){
				printf("\n");
			}
			else{
				printf(",");
			}
		}
	}
	free(pt);
	free(pt2);
	free(pt3);
	free(centroids);
	free(sums);
	free(vectors);
	free(sizes);
	free(assignments);
	return 0;
}
