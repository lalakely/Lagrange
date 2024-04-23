#include <stdio.h>
#include <stdlib.h>

float * allocFloat1D(float * tab , int dim);
void getDataF(float ** x , float ** y , int dim);
void display(float * x , float * y , int dim);
void printInFile(float * x , float * y ,float alpha , int dim);
float lagrange(float * y , float * x_tab ,float x , int dim);
void gplot();

int main(){
	float alpha = 0.001;
	float * x = NULL;
	float * y = NULL;
	int dim = 7;

	getDataF(&x , &y , dim);
	display(x , y , dim);
	
	printInFile(x , y , alpha , dim);
	gplot();
	return 0;
}

void gplot(){
	FILE * gp = popen("gnuplot -persist" , "w");
        if(gp){
                fprintf(gp , "set term qt size 800,600\n");
                fprintf(gp , "set title 'point to function'\n");
                fprintf(gp , "set xlabel 'X'\n");
                fprintf(gp , "set ylabel 'F(X)'\n");
                fprintf(gp , "set loadpath './'\n");
                fprintf(gp , "plot 'file.txt' using 1:2 w linespoint , 'data.txt' using 1:2 w linespoint \n");
        }
        else{
                printf("Gnuplot not found !!!\n");
        }
}

float lagrange(float * y , float * x_tab , float x , int dim){
	float P = 0;

	for(int i = 0 ; i < dim ; i++){
		float product = 1;
		for(int j = 0 ; j < dim ; j++){
			if (i != j){
				product*= (x - x_tab[j]) / (x_tab[i] - x_tab[j]);
			}
		}
		P+= y[i] * product;
	}
	
	return P;
}

void printInFile(float * x , float * y , float alpha , int dim){
	FILE * fp = fopen("file.txt" , "w");
	for(float i = x[0] ; i < x[dim-1] ; i+=alpha ){
		fprintf(fp,"%f %f\n" , i , lagrange(y, x ,i , dim));
	}
	fclose(fp);
}

void display(float * x , float * y , int dim){
	printf("==== Voici les données ====\n");
	for(int i = 0 ; i < dim ; i++){
		printf(" x[%d] = %g \t y[%d] = %g \n " , i , x[i] , i ,y[i]);
	}
}

void getDataF(float ** x , float ** y , int dim){
	float * x_p = allocFloat1D(x_p , dim);
	float * y_p = allocFloat1D(y_p , dim);

	FILE * fp = fopen("data.txt" , "r");
	if(fp){
		for(int i = 0 ; i < dim ; i++){
			fscanf(fp , "%f %f" , &x_p[i] , &y_p[i]);
		}
	}else{
		printf("Impossible d'ouvrir le fichier !!\n");
	}

	*x = x_p;
	*y = y_p;
}

float * allocFloat1D(float * tab , int dim){
	tab = (float *)malloc(dim * sizeof(float));
	for(int i = 0 ; i < dim ; i++){
		tab[i] = 0;
	}
	return tab;
}


