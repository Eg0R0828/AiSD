#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define N 100

// recursive function;
void function(int* vector, int* result, int count)
{
	for(int i=0; i<count; i++) printf("\t");
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
	    	if(count > 2) function(vector+2, result+2, count-2);
	}
}

int main()
{
	int* vector = (int*)malloc(sizeof(int));
	int* result;
	int i = 0;
	char s[N];
  
	// Entering the data;
	printf("Please, enter start vector coordinates: ");
	scanf("%s", s);
    	if(atoi(s)) vector[i] = atoi(s);
    	else{
        	printf("Wrong coordinate (%s)!", s);
		return 0;
    	}
	while(getchar() != '\n')
	{
		i++;
		realloc(vector, i*sizeof(int));
		scanf("%s", s);
		if(atoi(s)) vector[i] = atoi(s);
        	else{
            		printf("Wrong coordinate (%s)!", s);
		    	return 0;
        	}
	}
    	i++;

	// Proccessing program;
	result = (int*)malloc(i*sizeof(int));
	function(vector, result, i);
    
	// Print result and free memory;
	printf("Result vector: ");
	for(int j = 0; j < i; j++) printf("%d ", result[j]);
	printf("\n");
	free(vector);
	free(result);
	return 0;
}
