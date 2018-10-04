#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define N 100

// recursive function;
void function(int* vector, int* result, int count, int n)
{
	for(int i = 0; i < n; i++) printf("\t");
	printf("%d step of the recursion: ", n);
	if(count == 1){
		result[0] = vector[0];
	    	printf("%d\n", result[0]);
	}
	if(count >= 2){
		if(vector[1] >= vector[0]){
	        	result[0] = vector[0];
	        	result[1] = vector[1];
		}
		else{
	        	result[0] = vector[1];
	        	result[1] = vector[0];
		}
	    	printf("%d %d\n", result[0], result[1]);
	    	// recursion;
	    	if(count > 2) function(vector+2, result+2, count-2, n+1);
	}
	for(int i = 0; i < n; i++) printf("\t");
	printf("end of %d rec. step.\n", n);
}

int main()
{
	int* vector = (int*)malloc(sizeof(int)); // start vect.;
	int* result; // result vector;
	int i = 1;
	char s[N];
	int n = 1; // rec. step;
  
	// Entering the data;
	printf("Please, enter start vector coordinates: ");
	scanf("%s", s);
    	if(atoi(s)) vector[i-1] = atoi(s);
    	else{
        	printf("\x1b[31mWrong coordinate (%s)!\n\x1b[0m", s);
		free(vector);
		return 0;
    	}
	while(getchar() != '\n')
	{
		i++;
		vector = realloc(vector, i*sizeof(int));
		s[0] = '\0';
		scanf("%s", s);
		if(atoi(s)) vector[i-1] = atoi(s);
        	else{
            		printf("\x1b[31mWrong coordinate (%s)!\n\x1b[0m", s);
			free(vector);
		    	return 0;
        	}
	}

 	// Proccessing program;
	result = (int*)malloc(i*sizeof(int));
	printf("\n");
	function(vector, result, i, n);
	printf("\n");
    
	// Print result and free memory;
	printf("Result vector: ");
	for(int j = 0; j < i; j++) printf("%d ", result[j]);
	printf("\n");
	free(vector);
	free(result);
	return 0;
}