#include<stdio.h>
#include<stdlib.h>
int main()
{
	FILE* ptr = fopen("test2.txt","w");
	int i,j,n=100000;
	for(i=0; i<n; i++)
		fprintf(ptr,"%d ",rand());
	fclose(ptr);	
}
