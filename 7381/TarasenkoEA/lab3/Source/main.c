#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define N 100

int min(int x, int y) {
	if(x <= y)
        	return x;
    	else
        	return y;
}

int max(int x, int y) {
    	if(x >= y)
        	return x;
    	else
        	return y;
}

void push(int element, int* stack, int size) {
    	stack[size] = element;
    	printf("\x1b[33mpush: %d\x1b[0m\n", element);
}

int pop(int* stack, int size) {
    	int element = stack[size];
    	printf("\x1b[33mpop: %d\x1b[0m\n", element);
    	return element;
}

int main() {
    	// initialization stuff;
    	int* stack = (int*)malloc(N * sizeof(int));
    	int stack_size = -1;
    	char str[N];
	printf("Please, enter the data line:\n");
    	fgets(str, N, stdin);
    	int i = strlen(str);
    	int count_of_brackets = 0;
    	printf("\n");
    
    	// working with the stack;
    	while(i >= 1){
        	i--;
        	if(str[i] == '('){
            		count_of_brackets++; // looking for an available error (operation name);
            		if(((i - 1) < 0) || (((i - 1) < 0) && ((str[i - 1] != 'm') || (str[i - 1] != 'M')))){
                		fprintf(stderr, "\x1b[31mERROR: Expected a name of operation before '('!\x1b[0m\n");
                		free(stack);
                		return 0;
            		}
            		continue;
        	}
        	if(str[i] == ')'){
            		count_of_brackets--;
            		continue;
        	}
        	if((str[i] == ' ') || (str[i] == ',') || (str[i] == '\t') || (str[i] == '\n') || (str[i] == '\0'))
            		continue;
        
        	if(isdigit(str[i])){ // pushing an element to the stack;
            		push((int)(str[i] - '0'), stack, ++stack_size);
            		continue;
        	}
        	if((str[i] == 'm') || (str[i] == 'M')){ // calling a min or max function;
			if(stack_size < 1){ // looking for an available error (the count of args);
				fprintf(stderr, "\x1b[31mERROR: There are 2 args should be in a function!\x1b[0m\n");
        			free(stack);
        			return 0;
			}

            		int x = pop(stack, stack_size--);
            		int y = pop(stack, stack_size--);
            		if(str[i] == 'm')
				push(min(x, y), stack, ++stack_size);
			if(str[i] == 'M')
				push(max(x, y), stack, ++stack_size);
            		continue;
        	}
        
        	fprintf(stderr, "\x1b[31mERROR: Unexpected symbol %c!\x1b[0m\n", str[i]);
        	free(stack);
        	return 0;
    	}
    
    	// construction error;
    	if(count_of_brackets != 0){
        	fprintf(stderr, "\x1b[31mERROR: Counts of symbols '(' and ')' aren't equal!\x1b[0m\n");
        	free(stack);
        	return 0;
    	}

	if(stack_size != 0){ // looking for an available error (the count of args);
		fprintf(stderr, "\x1b[31mERROR: There are 2 args should be in a function!\x1b[0m\n");
        	free(stack);
        	return 0;
	}
    
    	// print a result;
    	printf("\n\x1b[32mResult: %d\x1b[0m\n", pop(stack, stack_size--));
    	free(stack);
    	return 0;
}
